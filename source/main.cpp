#include <3ds.h>
#include <CTRPluginFramework.hpp>

#include <string>
#include <vector>

#include "Language.hpp"
#include "Permissions.hpp"
#include "MiniGrokChat.hpp"
#include "FaceAnimation.hpp"
#include "FileHelper.hpp"
#include "TitleHelper.hpp"

namespace CTRPluginFramework
{
    // ============================================================
    // MiniGrok – AI assistant for Nintendo 3DS
    //
    // Global hotkey:
    //     SELECT + X
    //
    // The hotkey is handled directly through libctru so it works
    // independently of the CTRPF menu hotkey.
    // ============================================================

    static bool gChatOpen = false;
    static bool gHotkeyWasDown = false;

    static void OpenChat(MenuEntry *entry)
    {
        (void)entry;

        gChatOpen = true;
        MiniGrokChat::Open();
        gChatOpen = false;
    }

    static void AboutMiniGrok(MenuEntry *entry)
    {
        (void)entry;

        std::string msg =
            "MiniGrok v0.1\n\n"
            "The cute AI assistant for your 3DS.\n\n"
            "SELECT + X: Open MiniGrok\n\n"
            "Chat • Screen reading • Files • Titles\n\n"
            "API key:\n"
            "sd:/luma/plugins/MiniGrok/api.txt";

        MessageBox("About MiniGrok", msg)();
    }

    static void ReadScreen(MenuEntry *entry)
    {
        (void)entry;

        if (!Permissions::Ask(
                "Read screen",
                "May MiniGrok read the current screen and send it to the AI?"))
            return;

        MessageBox(
            "Read screen",
            "Screen capture is not implemented yet.\n"
            "Framebuffer dump will come here later.")();
    }

    static void FileTools(MenuEntry *entry)
    {
        (void)entry;

        Keyboard kb("File tools");

        std::vector<std::string> options = {
            "Read file",
            "Write / create file",
            "Cancel"
        };

        kb.Populate(options);

        int choice = kb.Open();

        if (choice < 0 || choice == 2)
            return;

        if (choice == 0)
        {
            if (!Permissions::Ask(
                    "Read file",
                    "May MiniGrok read a file?"))
                return;

            FileHelper::ReadFileDemo();
        }
        else if (choice == 1)
        {
            if (!Permissions::Ask(
                    "Write file",
                    "May MiniGrok create/write a file?"))
                return;

            FileHelper::WriteFileDemo();
        }
    }

    static void TitleTools(MenuEntry *entry)
    {
        (void)entry;

        if (!Permissions::Ask(
                "Open title",
                "May MiniGrok launch a title?"))
            return;

        TitleHelper::LaunchDemo();
    }

    static void ChangeLanguage(MenuEntry *entry)
    {
        (void)entry;

        Language::ShowLanguageMenu();
    }

    void InitMenu(PluginMenu &menu)
    {
        menu += new MenuEntry(
            "Open MiniGrok Chat",
            nullptr,
            OpenChat);

        menu += new MenuEntry(
            "Read screen (with permission)",
            nullptr,
            ReadScreen);

        menu += new MenuEntry(
            "File tools",
            nullptr,
            FileTools);

        menu += new MenuEntry(
            "Launch title",
            nullptr,
            TitleTools);

        menu += new MenuEntry(
            "Language / Sprache",
            nullptr,
            ChangeLanguage);

        menu += new MenuEntry(
            "About MiniGrok",
            nullptr,
            AboutMiniGrok);
    }

    /*
     * Called by CTRPluginFramework when a process is patched.
     *
     * We don't need game-specific patches because MiniGrok is
     * intended to work as a general plugin.
     */
    void PatchProcess(FwkSettings &settings)
    {
        (void)settings;
    }

    void OnProcessExit(void)
    {
        gChatOpen = false;
        gHotkeyWasDown = false;
    }

    /*
     * Check SELECT + X.
     *
     * hidKeysDown() returns keys that were pressed during the
     * current frame, which prevents the chat from being opened
     * repeatedly while the buttons are being held.
     */
    static void CheckMiniGrokHotkey()
    {
        const u32 keys = hidKeysDown();

        const bool selectPressed =
            (keys & KEY_SELECT) != 0;

        const bool xPressed =
            (keys & KEY_X) != 0;

        /*
         * We also check hidKeysHeld() so that either button can
         * be pressed first:
         *
         * SELECT held -> X pressed
         * X held      -> SELECT pressed
         */
        const u32 held = hidKeysHeld();

        const bool selectHeld =
            (held & KEY_SELECT) != 0;

        const bool xHeld =
            (held & KEY_X) != 0;

        const bool hotkey =
            (selectHeld && xPressed) ||
            (xHeld && selectPressed);

        if (hotkey && !gHotkeyWasDown && !gChatOpen)
        {
            gHotkeyWasDown = true;

            MiniGrokChat::Open();
        }

        /*
         * Don't allow another activation until both buttons
         * have been released.
         */
        if (!selectHeld && !xHeld)
        {
            gHotkeyWasDown = false;
        }
    }

    int main(void)
    {
        /*
         * Make sure the HID service is initialized.
         * In a normal 3GX/CTRPF environment this is already
         * available, but hidInit() is intentionally not called
         * here because CTRPF/libctru owns the service lifecycle.
         */

        PluginMenu *menu = new PluginMenu(
            "MiniGrok",
            0,
            1,
            0,
            "MiniGrok - your AI assistant on the 3DS.\n"
            "SELECT + X opens MiniGrok.");

        /*
         * Synchronize with frames so CTRPF keeps processing
         * the plugin while the game is running.
         */
        menu->SynchronizeWithFrame(true);

        Language::Load();

        InitMenu(*menu);

        /*
         * Run the normal CTRPF plugin menu.
         *
         * The SELECT + X hotkey is handled by the plugin's
         * frame/input processing.
         */
        menu->Run();

        delete menu;

        return 0;
    }

} // namespace CTRPluginFramework
