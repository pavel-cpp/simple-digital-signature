#include "io_tools.h"

#include <fstream>
#include <testing/testing.h>

std::vector<char> ReadContents(const std::filesystem::path& path) {
    std::ifstream file_(path, std::ios::binary);
    file_.seekg(0, std::ios::end);
    std::streamsize file_size = file_.tellg();
    if (file_size <= 0) {
        ASSERT_HINT(false, "Empty or invalid file");
    }
    file_.seekg(0, std::ios::beg);

    std::vector<char> file_content(file_size);
    if (!file_.read(file_content.data(), file_size)) {
        ASSERT_HINT(false, "Failed to read file content");
    }

    return file_content;
}