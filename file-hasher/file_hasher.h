#pragma once

#include <filesystem>


class FileHasher {
public:

    static uint64_t Hash(const std::filesystem::path& path);

};
