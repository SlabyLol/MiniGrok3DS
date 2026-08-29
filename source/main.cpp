#include <3ds.h>
#include <CTRPluginFramework.hpp>
#include <CTRPluginFrameworkImpl/Preferences.hpp>
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
// MiniGrok – cute AI assistant for the 3DS
// OPEN MENU: Select + X
// ============================================================

static bool g_notified = false;

static void AboutMiniGrok(MenuEntry *entry)
{
    std::string msg =
        "MiniGrok v0.1.2\n\n"
        "The cute AI assistant for your 3DS.\n\n"
        "OPEN THIS MENU:\n"
        "  Hold SELECT + X\n\n"
        "API key (later):\n"
        "sd:/luma/plugins/MiniGrok/api.txt";

    MessageBox("About MiniGrok", msg)();
}

static void OpenChat(MenuEntry *entry)
{
    MiniGrokChat::Open();
}

static void ReadScreen(MenuEntry *entry)
{
    if (!Permissions::Ask("Read screen",
        "May MiniGrok read info about the current screens?"))
        return;

    std::string info =
        "Top screen: 400x240\n"
        "Bottom screen: 320x240\n\n"
        "Full screen capture + send to AI\n"
        "is not implemented yet.\n\n"
        "This entry confirms permissions work.";

    MessageBox("Screen info", info)();
}

static void FileTools(MenuEntry *entry)
{
    Keyboard kb("File tools");
    std::vector<std::string> options = {
        "Read test file",
        "Write test file",
        "Cancel"
    };
    kb.Populate(options);
    int choice = kb.Open();

    if (choice < 0 || choice == 2) return;

    if (choice == 0)
    {
        if (!Permissions::Ask("Read file", "May MiniGrok read a file from the SD?"))
            return;
        FileHelper::ReadFileDemo();
    }
    else if (choice == 1)
    {
        if (!Permissions::Ask("Write file", "May MiniGrok create/write a file on the SD?"))
            return;
        FileHelper::WriteFileDemo();
    }
}

static void TitleTools(MenuEntry *entry)
{
    if (!Permissions::Ask("Title info",
        "May MiniGrok show info about the current process?"))
        return;

    TitleHelper::LaunchDemo();
}

static void ChangeLanguage(MenuEntry *entry)
{
    Language::ShowLanguageMenu();
}

static void HowToOpen(MenuEntry *entry)
{
    MessageBox("How to open MiniGrok",
        "Hotkey: SELECT + X\n\n"
        "1. Start a game (plugin must load)\n"
        "2. Hold SELECT and press X\n"
        "3. This menu opens\n\n"
        "If nothing happens:\n"
        "- Plugin Loader enabled in Rosalina?\n"
        "- File at sd:/luma/plugins/default.3gx ?\n"
        "- Did you see 'MiniGrok loaded' on screen?")();
}

void InitMenu(PluginMenu &menu)
{
    menu += new MenuEntry("How to open / Hilfe", nullptr, HowToOpen);
    menu += new MenuEntry("MiniGrok Chat", nullptr, OpenChat);
    menu += new MenuEntry("Screen info (permission)", nullptr, ReadScreen);
    menu += new MenuEntry("File tools", nullptr, FileTools);
    menu += new MenuEntry("Process / Title info", nullptr, TitleTools);
    menu += new MenuEntry("Language / Sprache", nullptr, ChangeLanguage);
    menu += new MenuEntry("About MiniGrok", nullptr, AboutMiniGrok);
}

void PatchProcess(FwkSettings &settings)
{
    (void)settings;
}

void OnProcessExit(void)
{
}

int main(void)
{
    // Force menu open combo: SELECT + X
    Preferences::MenuHotkeys = static_cast<u32>(Key::Select | Key::X);

    PluginMenu *menu = new PluginMenu("MiniGrok", 0, 1, 2,
        "MiniGrok – cute AI assistant.\n"
        "Open with SELECT + X.");

    menu->SynchronizeWithFrame(true);

    if (!g_notified)
    {
        OSD::Notify("MiniGrok loaded!");
        OSD::Notify("Open: SELECT + X");
        g_notified = true;
    }

    Language::Load();
    InitMenu(*menu);

    // Blocks; opens when SELECT+X is pressed
    menu->Run();

    delete menu;
    return 0;
}

} // namespace CTRPluginFramework
