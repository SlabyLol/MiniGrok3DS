#include "FaceAnimation.hpp"
#include <CTRPluginFramework.hpp>

namespace FaceAnimation
{
    void ShowIdle()
    {
        using namespace CTRPluginFramework;
        OSD::Notify("MiniGrok: :)");
    }

    void ShowThinking()
    {
        using namespace CTRPluginFramework;
        OSD::Notify("MiniGrok: thinking...");
    }

    void ShowTalking()
    {
        using namespace CTRPluginFramework;
        OSD::Notify("MiniGrok: ...");
    }

    void ShowHappy()
    {
        using namespace CTRPluginFramework;
        OSD::Notify("MiniGrok: :D");
    }
}
