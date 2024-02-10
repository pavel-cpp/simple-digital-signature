#include "io_tools.h"

#include <fstream>
#include <stdexcept>

std::vector<char> ReadContents(const std::filesystem::path &path) {
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

void WriteData(std::fstream &file, const std::vector<int64_t> &data) {
    size_t size_of_data = data.size();
    file.write(reinterpret_cast<const char *>(&size_of_data), sizeof(size_t));
    file.write(reinterpret_cast<const char *>(data.data()), data.size() * sizeof(int64_t));
}

std::vector<int64_t> ReadData(std::fstream &file) {
    std::vector<int64_t> data;
    size_t size_of_data;
    file.read(reinterpret_cast<char *>(&size_of_data), sizeof(size_t));
    data.resize(size_of_data);
    file.read(reinterpret_cast<char *>(data.data()), size_of_data * sizeof(int64_t));
    return data;
}