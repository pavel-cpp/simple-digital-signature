#include "key_sign_manager.h"

#include <fstream>

#include <io-tools/io_tools.h>

using std::fstream;

KeySignManager::KeySignManager(const std::filesystem::path &path) : path_(path) {
    fstream tmp(path, std::ios::binary | std::ios::app);
}

void KeySignManager::AddData(const std::vector<int64_t> &key, const std::vector<int64_t> &sign) {
    fstream repository_file(path_, std::ios::binary | std::ios::app);
    WriteData(repository_file, key);
    WriteData(repository_file, sign);
}

std::vector<int64_t> KeySignManager::GetKey(const std::vector<int64_t> &sing) const {
    fstream repository_file(path_, std::ios::binary | std::ios::in);
    std::vector<int64_t> key;
    while (repository_file) {
        key = ReadData(repository_file);
        std::vector<int64_t> tmp_sign = ReadData(repository_file);
        if (std::equal(tmp_sign.begin(), tmp_sign.end(), sing.begin(), sing.end())) {
            return key;
        }
    }
    return {};
}

void KeySignManager::RemoveData(const std::vector<int64_t> &key) {
    fstream repository_file(path_, std::ios::binary | std::ios::in);
    std::vector<std::pair<std::vector<int64_t>, std::vector<int64_t>>> content;
    while (repository_file) {
        repository_file.get();
        if (!repository_file) {
            break;
        }
        repository_file.unget();
        std::vector<int64_t> tmp_key = ReadData(repository_file);
        std::vector<int64_t> tmp_sign = ReadData(repository_file);

        if (std::equal(tmp_key.begin(), tmp_key.end(), key.begin(), key.end())) {
            continue;
        }
        content.emplace_back(tmp_key, tmp_sign);
    }
    repository_file.close();
    repository_file.open(path_, std::ios::binary | std::ios::out);
    for (const auto &[open_key, sign]: content) {
        WriteData(repository_file, open_key);
        WriteData(repository_file, sign);
    }
}
