#include "TitleHelper.hpp"
#include <CTRPluginFramework.hpp>
#include <sstream>

namespace TitleHelper
{
    void LaunchDemo()
    {
        using namespace CTRPluginFramework;

        // Show current process info (safe, no launch yet)
        u64 titleId = Process::GetTitleID();
        std::string name;
        Process::GetName(name);

        std::ostringstream oss;
        oss << "Current process\n\n";
        oss << "Name: " << (name.empty() ? "(unknown)" : name) << "\n";
        oss << "Title ID:\n";
        oss << std::hex << titleId << std::dec << "\n\n";
        oss << "Launching other titles from a\n";
        oss << "plugin needs more work and is\n";
        oss << "not enabled in this build.";

        MessageBox("Process info", oss.str())();
    }
}
