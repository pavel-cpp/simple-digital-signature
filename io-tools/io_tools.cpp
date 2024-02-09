#include "io_tools.h"

#include <fstream>

std::vector<char> ReadContents(const std::filesystem::path& path) {
    std::ifstream file_(path, std::ios::binary);
    file_.seekg(0, std::ios::end);
    std::streamsize file_size = file_.tellg();
    if (file_size <= 0) {
        throw std::runtime_error("Empty or invalid file");
    }
    file_.seekg(0, std::ios::beg);

    std::vector<char> file_content(file_size);
    if (!file_.read(file_content.data(), file_size)) {
        throw std::runtime_error("Failed to read file content");
    }

    return file_content;
}