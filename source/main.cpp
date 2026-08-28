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
    static bool gChatOpen = false;

    // ------------------------------------------------------------
    // Open MiniGrok
    // ------------------------------------------------------------

    static void OpenChat(MenuEntry *entry)
    {
        (void)entry;

        if (gChatOpen)
            return;

        gChatOpen = true;

        MiniGrokChat::Open();

        gChatOpen = false;
    }

    // ------------------------------------------------------------
    // About
    // ------------------------------------------------------------

    static void AboutMiniGrok(MenuEntry *entry)
    {
        (void)entry;

        MessageBox(
            "MiniGrok",
            "MiniGrok v0.1\n\n"
            "AI assistant for Nintendo 3DS.\n\n"
            "SELECT + X  -  Open MiniGrok"
        )();
    }

    // ------------------------------------------------------------
    // Screen
    // ------------------------------------------------------------

    static void ReadScreen(MenuEntry *entry)
    {
        (void)entry;

        if (!Permissions::Ask(
                "Read screen",
                "May MiniGrok read the current screen?"))
            return;

        MessageBox(
            "MiniGrok",
            "Screen capture is not implemented yet."
        )();
    }

    // ------------------------------------------------------------
    // Files
    // ------------------------------------------------------------

    static void FileTools(MenuEntry *entry)
    {
        (void)entry;

        Keyboard kb("File tools");

        std::vector<std::string> options =
        {
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

    // ------------------------------------------------------------
    // Titles
    // ------------------------------------------------------------

    static void TitleTools(MenuEntry *entry)
    {
        (void)entry;

        if (!Permissions::Ask(
                "Open title",
                "May MiniGrok launch a title?"))
            return;

        TitleHelper::LaunchDemo();
    }

    // ------------------------------------------------------------
    // Language
    // ------------------------------------------------------------

    static void ChangeLanguage(MenuEntry *entry)
    {
        (void)entry;

        Language::ShowLanguageMenu();
    }

    // ------------------------------------------------------------
    // Menu
    // ------------------------------------------------------------

    static void InitMenu(PluginMenu &menu)
    {
        /*
         * IMPORTANT:
         *
         * The hotkey is attached to the MenuEntry itself.
         * CTRPluginFramework checks the hotkey every frame.
         *
         * SELECT + X
         */

        MenuEntry *chat = new MenuEntry(
            "Open MiniGrok Chat",
            nullptr,
            OpenChat
        );

        chat->Hotkeys += Hotkey(
            Key::SELECT | Key::X,
            "SELECT + X"
        );

        menu += chat;

        menu += new MenuEntry(
            "Read screen",
            nullptr,
            ReadScreen
        );

        menu += new MenuEntry(
            "File tools",
            nullptr,
            FileTools
        );

        menu += new MenuEntry(
            "Launch title",
            nullptr,
            TitleTools
        );

        menu += new MenuEntry(
            "Language / Sprache",
            nullptr,
            ChangeLanguage
        );

        menu += new MenuEntry(
            "About MiniGrok",
            nullptr,
            AboutMiniGrok
        );
    }

    // ------------------------------------------------------------
    // CTRPluginFramework callbacks
    // ------------------------------------------------------------

    void PatchProcess(FwkSettings &settings)
    {
        (void)settings;
    }

    void OnProcessExit(void)
    {
        gChatOpen = false;
    }

    // ------------------------------------------------------------
    // Main
    // ------------------------------------------------------------

    int main(void)
    {
        PluginMenu *menu = new PluginMenu(
            "MiniGrok",
            0,
            1,
            0,
            "MiniGrok - AI assistant for Nintendo 3DS.\n"
            "Press SELECT + X to open MiniGrok."
        );

        /*
         * Let CTRPF process menu entries and hotkeys
         * on every frame.
         */
        menu->SynchronizeWithFrame(true);

        Language::Load();

        InitMenu(*menu);

        /*
         * Start CTRPF main loop.
         *
         * The SELECT + X hotkey is now handled by
         * MenuEntry::Hotkeys.
         */
        menu->Run();

        delete menu;

        return 0;
    }

} // namespace CTRPluginFramework
