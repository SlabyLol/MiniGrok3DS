#include "FileHelper.hpp"
#include <CTRPluginFramework.hpp>

namespace FileHelper
{
    void ReadFileDemo()
    {
        using namespace CTRPluginFramework;

        // Demo: tries to read a test file
        // Later: user enters path or selects file

        File file;
        if (File::Open(file, "sd:/luma/plugins/MiniGrok/test.txt", File::READ) == 0)
        {
            std::string content;
            file.Read(content);
            file.Close();
            MessageBox("File read", content.empty() ? "(file is empty)" : content)();
        }
        else
        {
            MessageBox("Read file",
                "Could not open\n"
                "sd:/luma/plugins/MiniGrok/test.txt\n\n"
                "Create a test file to try the demo mode.")();
        }
    }

    void WriteFileDemo()
    {
        using namespace CTRPluginFramework;

        File file;
        if (File::Open(file, "sd:/luma/plugins/MiniGrok/test_write.txt",
                       File::WRITE | File::CREATE | File::TRUNCATE) == 0)
        {
            std::string text = "Hello from MiniGrok!\nThis is a test write.";
            file.Write(text);
            file.Close();
            MessageBox("File written",
                "Successfully written to:\n"
                "sd:/luma/plugins/MiniGrok/test_write.txt")();
        }
        else
        {
            MessageBox("Error", "Could not write file.")();
        }
    }
}
