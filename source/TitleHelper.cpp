#include "TitleHelper.hpp"
#include <CTRPluginFramework.hpp>

namespace TitleHelper
{
    void LaunchDemo()
    {
        using namespace CTRPluginFramework;

        // Very simplified stub.
        // Real title launching needs AM services and is
        // different depending on context (Home Menu vs In-Game).

        MessageBox("Launch Title",
            "Title launching is still a stub.\n\n"
            "Later MiniGrok will be able to start\n"
            "titles via the AM services\n"
            "(with permission of course).")();
    }
}
