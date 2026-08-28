#pragma once
#include <string>
#include <CTRPluginFramework.hpp>

namespace Language
{
    enum class Lang
    {
        German = 0,
        English = 1,
        // more later
    };

    void Load();
    void Save();
    void ShowLanguageMenu();

    // Simple translation function
    std::string Get(const std::string &key);

    // Current language
    extern Lang current;
}
