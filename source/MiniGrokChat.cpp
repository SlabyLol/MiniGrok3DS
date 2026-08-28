#include "MiniGrokChat.hpp"
#include <CTRPluginFramework.hpp>
#include "FaceAnimation.hpp"
#include "Language.hpp"

namespace MiniGrokChat
{
    void Open()
    {
        using namespace CTRPluginFramework;

        // Currently just a stub.
        // Later: own overlay with face + chat history + input

        FaceAnimation::ShowIdle();   // show face (placeholder)

        std::string welcome =
            "Hello! I am MiniGrok\n"
            "your cute AI assistant.\n\n"
            "Currently the chat is still\n"
            "a stub.\n\n"
            "Soon I will be able to:\n"
            "- chat with you\n"
            "- read your screen\n"
            "- help with files\n"
            "- launch titles\n\n"
            "Please put your API key in:\n"
            "sd:/luma/plugins/MiniGrok/api.txt";

        MessageBox("MiniGrok Chat", welcome)();

        // TODO:
        // 1. Custom renderer for chat window
        // 2. Input field
        // 3. HTTP request to xAI API
        // 4. Show response + animate face
    }
}
