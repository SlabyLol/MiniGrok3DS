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
// MiniGrok – cute AI assistant for the 3DS
// OPEN MENU: press SELECT (default CTRPF hotkey)
// ============================================================

static bool g_notified = false;

static void AboutMiniGrok(MenuEntry *entry)
{
    std::string msg =
        "MiniGrok v0.1.1\n\n"
        "The cute AI assistant for your 3DS.\n\n"
        "OPEN THIS MENU:\n"
        "  Press SELECT\n\n"
        "(You can change the hotkey in\n"
        " Tools -> Settings inside this menu.)\n\n"
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

    // Basic screen info (full framebuffer dump+upload comes later)
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
        "Default hotkey: SELECT\n\n"
        "1. Start a game (plugin must load)\n"
        "2. Press SELECT once\n"
        "3. This menu opens\n\n"
        "Change hotkey:\n"
        "Tools -> Settings -> Menu Hotkey\n\n"
        "If nothing happens:\n"
        "- Plugin Loader enabled in Rosalina?\n"
        "- File at sd:/luma/plugins/default.3gx ?\n"
        "- Screen flashed when game started?")();
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
    // Keep defaults; touchscreen force-on patch can be added later if needed
    (void)settings;
}

void OnProcessExit(void)
{
}

int main(void)
{
    PluginMenu *menu = new PluginMenu("MiniGrok", 0, 1, 1,
        "MiniGrok – cute AI assistant.\n"
        "Press SELECT to open this menu.");

    menu->SynchronizeWithFrame(true);

    // Show a one-shot hint so the user knows the plugin loaded
    if (!g_notified)
    {
        OSD::Notify("MiniGrok loaded!");
        OSD::Notify("Press SELECT to open");
        g_notified = true;
    }

    Language::Load();
    InitMenu(*menu);

    // Blocks here and opens when the menu hotkey (default: SELECT) is pressed
    menu->Run();

    delete menu;
    return 0;
}

} // namespace CTRPluginFramework
