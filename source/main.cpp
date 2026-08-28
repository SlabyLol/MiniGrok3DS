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
// Planned hotkey: Select + X (via Rosalina / custom later)
// ============================================================

static void AboutMiniGrok(MenuEntry *entry)
{
    std::string msg =
        "MiniGrok v0.1 (Foundation)\n\n"
        "The cute AI assistant for your 3DS.\n"
        "Chat • Screen reading • Files • Titles\n\n"
        "Everything with permission prompts.\n\n"
        "Planned hotkey: Select + X\n"
        "API key: sd:/luma/plugins/MiniGrok/api.txt";

    MessageBox("About MiniGrok", msg)();
}

static void OpenChat(MenuEntry *entry)
{
    MiniGrokChat::Open();
}

static void ReadScreen(MenuEntry *entry)
{
    if (!Permissions::Ask("Read screen",
        "May MiniGrok read the current screen and send it to the AI?"))
        return;

    MessageBox("Read screen",
        "Screen capture is not implemented yet.\n"
        "Framebuffer dump will come here later.")();
}

static void FileTools(MenuEntry *entry)
{
    Keyboard kb("File tools");
    std::vector<std::string> options = {
        "Read file",
        "Write / create file",
        "Cancel"
    };
    kb.Populate(options);
    int choice = kb.Open();

    if (choice < 0 || choice == 2) return;

    if (choice == 0)
    {
        if (!Permissions::Ask("Read file", "May MiniGrok read a file?"))
            return;
        FileHelper::ReadFileDemo();
    }
    else if (choice == 1)
    {
        if (!Permissions::Ask("Write file", "May MiniGrok create/write a file?"))
            return;
        FileHelper::WriteFileDemo();
    }
}

static void TitleTools(MenuEntry *entry)
{
    if (!Permissions::Ask("Open title",
        "May MiniGrok launch a title?"))
        return;

    TitleHelper::LaunchDemo();
}

static void ChangeLanguage(MenuEntry *entry)
{
    Language::ShowLanguageMenu();
}

void InitMenu(PluginMenu &menu)
{
    menu += new MenuEntry("Open MiniGrok Chat", nullptr, OpenChat);
    menu += new MenuEntry("Read screen (with permission)", nullptr, ReadScreen);
    menu += new MenuEntry("File tools", nullptr, FileTools);
    menu += new MenuEntry("Launch title", nullptr, TitleTools);
    menu += new MenuEntry("Language / Sprache", nullptr, ChangeLanguage);
    menu += new MenuEntry("About MiniGrok", nullptr, AboutMiniGrok);
}

void PatchProcess(FwkSettings &settings)
{
}

void OnProcessExit(void)
{
}

int main(void)
{
    PluginMenu *menu = new PluginMenu("MiniGrok", 0, 1, 0,
        "MiniGrok – your cute AI assistant on the 3DS.\n"
        "Chat, screen reading, files & titles – with permission.");

    menu->SynchronizeWithFrame(true);

    Language::Load();
    InitMenu(*menu);
    menu->Run();

    delete menu;
    return 0;
}

} // namespace CTRPluginFramework

// Global entry point required by the standard 3dsx CRT.
// Real 3gx plugins are entered via CTRPF; this keeps the CI link step happy.
extern "C" int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    return CTRPluginFramework::main();
}
