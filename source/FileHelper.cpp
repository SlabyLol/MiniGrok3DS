#include "FileHelper.hpp"
#include <CTRPluginFramework.hpp>
#include <vector>
#include <string>

namespace FileHelper
{
    void ReadFileDemo()
    {
        using namespace CTRPluginFramework;

        File file;
        if (File::Open(file, "sd:/luma/plugins/MiniGrok/test.txt", File::READ) == 0)
        {
            u64 size = file.GetSize();
            if (size == 0 || size > 1024 * 64)
            {
                file.Close();
                MessageBox("File read", "(file empty or too large for demo)")();
                return;
            }

            std::vector<char> buffer(static_cast<size_t>(size) + 1, 0);
            file.Read(buffer.data(), static_cast<u32>(size));
            file.Close();

            std::string content(buffer.data());
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
            file.Write(text.data(), static_cast<u32>(text.size()));
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
