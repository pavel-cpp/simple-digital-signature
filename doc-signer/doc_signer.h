#pragma once

#include <cstdint>
#include <filesystem>
#include <vector>

class DocSigner {
public:

    static void Sign(const std::filesystem::path &path, const std::vector<int64_t> &sign);

    static bool ValidSign(const std::filesystem::path &doc_path, const std::filesystem::path &sign_path);

    static bool HasSign(const std::filesystem::path &doc_path);

    static void UnSign(const std::filesystem::path &sign_path);

};

