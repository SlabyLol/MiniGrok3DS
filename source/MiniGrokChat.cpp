#include "MiniGrokChat.hpp"
#include <CTRPluginFramework.hpp>
#include "FaceAnimation.hpp"
#include "Language.hpp"

namespace MiniGrokChat
{
    void Open()
    {
        using namespace CTRPluginFramework;

        FaceAnimation::ShowIdle();

        // Simple local "chat" UI until real API is wired
        Keyboard kb("MiniGrok – say something");
        kb.DisplayTopScreen = true;

        std::string input;
        if (kb.Open(input) < 0 || input.empty())
        {
            MessageBox("MiniGrok", "Cancelled.")();
            return;
        }

        FaceAnimation::ShowThinking();

        // Placeholder reply (no network yet)
        std::string reply =
            "You said:\n\"" + input + "\"\n\n"
            "(Online Grok replies need WiFi +\n"
            "API key in api.txt – coming next.)\n\n"
            "For now I only echo locally.\n"
            "Stay tuned! ";

        FaceAnimation::ShowHappy();
        MessageBox("MiniGrok", reply)();
    }
}
