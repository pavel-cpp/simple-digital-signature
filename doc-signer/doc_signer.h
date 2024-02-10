#pragma once

#include <filesystem>
#include <vector>
#include <cstdint>

class DocSigner {

    static void Sign(const std::filesystem::path& path, const std::vector<int64_t>& sign);

    bool ValidSign(const std::filesystem::path &doc_path, const std::filesystem::path &sign_path);

    static bool HasSign(const std::filesystem::path& path);

};

