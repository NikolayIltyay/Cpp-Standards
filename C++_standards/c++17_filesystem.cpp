#include "c++17_filesystem.h"
#include <filesystem>

void Cpp_17_Filesystem::example()
{
    const auto bigFilePath{ "bigFileToCopy" };
    if (std::filesystem::exists(bigFilePath)) {
        const auto bigFileSize{ std::filesystem::file_size(bigFilePath) };
        std::filesystem::path tmpPath{ "/tmp" };
        if (std::filesystem::space(tmpPath).available > bigFileSize) {
            std::filesystem::create_directory(tmpPath.append("example"));
            std::filesystem::copy_file(bigFilePath, tmpPath.append("newFile"));
        }
    }
}
