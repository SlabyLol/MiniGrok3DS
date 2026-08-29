#include <3ds.h>
#include "csvc.h"
#include <CTRPluginFramework.hpp>
#include <vector>

namespace CTRPluginFramework
{
    class Preferences
    {
    public:
        static u32 MenuHotkeys;
    };

    static void ForceHotkey(void)
    {
        Preferences::MenuHotkeys = static_cast<u32>(Key::Select | Key::X);
    }

    static void ToggleTouchscreenForceOn(void)
    {
        static u32 original = 0;
        static u32 *patchAddress = nullptr;

        if (patchAddress && original)
        {
            *patchAddress = original;
            return;
        }

        static const std::vector<u32> pattern =
        {
            0xE59F10C0, 0xE5840004, 0xE5841000, 0xE5DD0000,
            0xE5C40008, 0xE28DD03C, 0xE8BD80F0, 0xE5D51001,
            0xE1D400D4, 0xE3510003, 0x159F0034, 0x1A000003
        };

        Handle  processHandle;
        s64     textTotalSize = 0;
        s64     startAddress = 0;
        u32 *   found;

        if (R_FAILED(svcOpenProcess(&processHandle, 16)))
            return;

        svcGetProcessInfo(&textTotalSize, processHandle, 0x10002);
        svcGetProcessInfo(&startAddress, processHandle, 0x10005);
        if (R_FAILED(svcMapProcessMemoryEx(CUR_PROCESS_HANDLE, 0x14000000, processHandle, (u32)startAddress, textTotalSize)))
            goto exit;

        found = (u32 *)Utils::Search<u32>(0x14000000, (u32)textTotalSize, pattern);

        if (found != nullptr)
        {
            original = found[13];
            patchAddress = (u32 *)PA_FROM_VA((found + 13));
            found[13] = 0xE1A00000;
        }

        svcUnmapProcessMemoryEx(CUR_PROCESS_HANDLE, 0x14000000, textTotalSize);
exit:
        svcCloseHandle(processHandle);
    }

    void    PatchProcess(FwkSettings &settings)
    {
        (void)settings;
        ToggleTouchscreenForceOn();
        ForceHotkey();
    }

    void    OnProcessExit(void)
    {
        ToggleTouchscreenForceOn();
    }

    static void AboutMiniGrok(MenuEntry *entry)
    {
        MessageBox("About MiniGrok",
            "MiniGrok v0.2\n\n"
            "Cute AI assistant for 3DS.\n\n"
            "Open menu: SELECT + X\n\n"
            "API key later:\n"
            "sd:/luma/plugins/MiniGrok/api.txt")();
    }

    static void OpenChat(MenuEntry *entry)
    {
        Keyboard kb("MiniGrok - say something");
        std::string input;
        if (kb.Open(input) < 0 || input.empty())
            return;

        std::string reply = "You said:\n\"" + input + "\"\n\n";
        reply += "(Online Grok needs WiFi + API key later.)";
        MessageBox("MiniGrok", reply)();
    }

    static void FileDemo(MenuEntry *entry)
    {
        if (!MessageBox("Permission", "May MiniGrok write a test file?", MessageBox::YesNo)())
            return;

        File file;
        if (File::Open(file, "sd:/luma/plugins/MiniGrok/test_write.txt",
                       File::WRITE | File::CREATE | File::TRUNCATE) == 0)
        {
            std::string text = "Hello from MiniGrok!\n";
            file.Write(text.data(), text.size());
            file.Close();
            MessageBox("OK", "Wrote sd:/luma/plugins/MiniGrok/test_write.txt")();
        }
        else
            MessageBox("Error", "Could not write file.\nCreate folder MiniGrok first?")();
    }

    static void HowToOpen(MenuEntry *entry)
    {
        MessageBox("How to open",
            "Hold SELECT + press X\n\n"
            "Must be in a game (plugin loaded).\n"
            "You should see OSD on boot.")();
    }

    void    InitMenu(PluginMenu &menu)
    {
        menu += new MenuEntry("How to open", nullptr, HowToOpen);
        menu += new MenuEntry("MiniGrok Chat", nullptr, OpenChat);
        menu += new MenuEntry("File test (permission)", nullptr, FileDemo);
        menu += new MenuEntry("About MiniGrok", nullptr, AboutMiniGrok);
    }

    int     main(void)
    {
        ForceHotkey();

        PluginMenu *menu = new PluginMenu("MiniGrok", 0, 2, 0,
            "MiniGrok - cute AI assistant.\nOpen: SELECT + X");

        menu->SynchronizeWithFrame(true);
        menu->ShowWelcomeMessage(false);

        menu->OnFirstOpening = [](void)
        {
            ForceHotkey();
        };

        *menu += ForceHotkey;

        OSD::Notify("MiniGrok loaded!");
        OSD::Notify("Open: SELECT + X");

        InitMenu(*menu);

        ForceHotkey();
        menu->Run();

        delete menu;
        return 0;
    }
}
