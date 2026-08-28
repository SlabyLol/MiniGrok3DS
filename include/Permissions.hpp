#pragma once
#include <string>

namespace Permissions
{
    // Shows a Yes/No dialog
    // Returns true if the user chooses "Yes"
    bool Ask(const std::string &title, const std::string &message);
}
