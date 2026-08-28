#include "Permissions.hpp"
#include <CTRPluginFramework.hpp>
#include "Language.hpp"

namespace Permissions
{
    bool Ask(const std::string &title, const std::string &message)
    {
        using namespace CTRPluginFramework;

        std::string fullMsg = message + "\n\n" + Language::Get("yes") + " = A\n" + Language::Get("no") + " = B";

        // Simple MessageBox-style dialog
        // (later: nicer custom dialog)
        MessageBox mb(title, fullMsg, DialogType::DialogOkCancel);
        return mb();
    }
}
