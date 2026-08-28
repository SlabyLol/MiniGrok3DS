#include "Language.hpp"
#include <map>

namespace Language
{
    Lang current = Lang::English;

    static std::map<std::string, std::map<Lang, std::string>> translations = {
        {"chat_open", {
            {Lang::German, "Chat öffnen"},
            {Lang::English, "Open Chat"}
        }},
        {"permission_title", {
            {Lang::German, "Erlaubnis benötigt"},
            {Lang::English, "Permission required"}
        }},
        {"yes", {
            {Lang::German, "Ja"},
            {Lang::English, "Yes"}
        }},
        {"no", {
            {Lang::German, "Nein"},
            {Lang::English, "No"}
        }},
        {"about", {
            {Lang::German, "Über MiniGrok"},
            {Lang::English, "About MiniGrok"}
        }}
    };

    void Load()
    {
        // TODO: load from config file
        current = Lang::English;
    }

    void Save()
    {
        // TODO: write to config
    }

    std::string Get(const std::string &key)
    {
        auto it = translations.find(key);
        if (it == translations.end())
            return key;

        auto &langMap = it->second;
        auto lit = langMap.find(current);
        if (lit != langMap.end())
            return lit->second;

        // Fallback English
        lit = langMap.find(Lang::English);
        if (lit != langMap.end())
            return lit->second;

        return key;
    }

    void ShowLanguageMenu()
    {
        using namespace CTRPluginFramework;

        Keyboard kb("Language / Sprache");
        std::vector<std::string> options = {
            "English",
            "Deutsch"
        };
        kb.Populate(options);
        int choice = kb.Open();

        if (choice == 0)
            current = Lang::English;
        else if (choice == 1)
            current = Lang::German;

        Save();
        MessageBox("MiniGrok", "Language changed / Sprache geändert")();
    }
}
