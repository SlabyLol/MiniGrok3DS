#include <3ds.h>
#include <CTRPluginFramework.hpp>
#include <string>
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

    void    PatchProcess(FwkSettings &settings)
    {
        (void)settings;
        ForceHotkey();
    }

    void    OnProcessExit(void)
    {
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
        // Simple confirm without DialogType enum (version-safe)
        MessageBox("Permission", "Writing test file to SD...")();

        File file;
        if (File::Open(file, "sd:/luma/plugins/MiniGrok/test_write.txt",
                       File::WRITE | File::CREATE | File::TRUNCATE) == 0)
        {
            std::string text = "Hello from MiniGrok!\n";
            file.Write(text.data(), static_cast<u32>(text.size()));
            file.Close();
            MessageBox("OK", "Wrote test file OK")();
        }
        else
            MessageBox("Error", "Could not write file.")();
    }

    static void HowToOpen(MenuEntry *entry)
    {
        MessageBox("How to open",
            "Hold SELECT + press X\n\n"
            "Start a game first.\n"
            "OSD should show: MiniGrok loaded!")();
    }

    void    InitMenu(PluginMenu &menu)
    {
        menu += new MenuEntry("How to open", nullptr, HowToOpen);
        menu += new MenuEntry("MiniGrok Chat", nullptr, OpenChat);
        menu += new MenuEntry("File test", nullptr, FileDemo);
        menu += new MenuEntry("About MiniGrok", nullptr, AboutMiniGrok);
    }

    int     main(void)
    {
        ForceHotkey();

        PluginMenu *menu = new PluginMenu("MiniGrok", 0, 2, 0,
            "MiniGrok - cute AI assistant.\nOpen: SELECT + X");

        menu->SynchronizeWithFrame(true);
        menu->ShowWelcomeMessage(false);

        menu->OnFirstOpening = [](void) { ForceHotkey(); };
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
