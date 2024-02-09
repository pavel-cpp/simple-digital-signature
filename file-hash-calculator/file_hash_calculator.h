#pragma once

#include <cryptographic/cryptographic.h>
#include <cstdint>
#include <io-tools/io_tools.h>

class FileHashCalculator {
public:
    FileHashCalculator();
    uint64_t Calculate(const std::filesystem::path& path);
private:
    Cryptographic::Provider provider_;
    Cryptographic::Hash hash_;
};
