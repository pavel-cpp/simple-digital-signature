#pragma once

#include <file_reader.h>

class FileHashCalculator {
public:
    FileHashCalculator(const std::filesystem::path& path);
    uint64_t Calculate();
private:
    FileReader file_reader_;
    CryptographicProvider provider_;
    CryptographicHash hash_;
};
