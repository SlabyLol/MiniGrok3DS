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

// Preferences::MenuHotkeys is defined in libctrpf.
class Preferences
{
public:
    static u32 MenuHotkeys;
};

static const u32 kMenuHotkey = static_cast<u32>(Key::Select | Key::X);

static void ForceMenuHotkey(void)
{
    Preferences::MenuHotkeys = kMenuHotkey;
}

static bool g_notified = false;

static void AboutMiniGrok(MenuEntry *entry)
{
    std::string msg =
        "MiniGrok v0.1.3\n\n"
        "OPEN MENU:\n"
        "  Hold SELECT + press X\n\n"
        "If that fails, try only SELECT.\n\n"
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

    MessageBox("Screen info",
        "Top: 400x240\nBottom: 320x240\n\n"
        "Full capture + AI upload comes later.")();
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
    MessageBox("How to open",
        "1. Start any game\n"
        "2. Wait for OSD: MiniGrok loaded\n"
        "3. Hold SELECT + press X\n\n"
        "Also try SELECT alone.\n\n"
        "Check:\n"
        "- Rosalina -> Plugin Loader ON\n"
        "- sd:/luma/plugins/default.3gx\n"
        "- Delete old plugin settings if stuck")();
}

void InitMenu(PluginMenu &menu)
{
    menu += new MenuEntry("How to open / Hilfe", nullptr, HowToOpen);
    menu += new MenuEntry("MiniGrok Chat", nullptr, OpenChat);
    menu += new MenuEntry("Screen info", nullptr, ReadScreen);
    menu += new MenuEntry("File tools", nullptr, FileTools);
    menu += new MenuEntry("Process info", nullptr, TitleTools);
    menu += new MenuEntry("Language / Sprache", nullptr, ChangeLanguage);
    menu += new MenuEntry("About MiniGrok", nullptr, AboutMiniGrok);
}

void PatchProcess(FwkSettings &settings)
{
    (void)settings;
    ForceMenuHotkey();
}

void OnProcessExit(void)
{
}

int main(void)
{
    ForceMenuHotkey();

    PluginMenu *menu = new PluginMenu("MiniGrok", 0, 1, 3,
        "MiniGrok\nOpen: SELECT + X");

    menu->SynchronizeWithFrame(true);

    menu->OnFirstOpening = [](void)
    {
        ForceMenuHotkey();
        OSD::Notify("Hotkey: SELECT + X");
    };

    // Re-apply every plugin loop tick (settings cannot stick to Select only)
    *menu += ForceMenuHotkey;

    if (!g_notified)
    {
        OSD::Notify("MiniGrok loaded!");
        OSD::Notify("Open: SELECT + X");
        g_notified = true;
    }

    Language::Load();
    InitMenu(*menu);

    ForceMenuHotkey();
    menu->Run();

    delete menu;
    return 0;
}

} // namespace CTRPluginFramework
