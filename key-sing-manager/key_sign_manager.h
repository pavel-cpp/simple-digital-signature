#pragma once

#include <filesystem>
#include <fstream>
#include <vector>

class KeySignManager {
public:

    KeySignManager(const std::filesystem::path &path);

    void AddData(const std::vector<int64_t> &key, const std::vector<int64_t> &sing);

    void GetKey(const std::vector<int64_t> &sing);

    void RemoveData(const std::vector<int64_t> &key);

private:

    std::fstream repository_file_;

};
