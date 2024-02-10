#pragma once

#include <filesystem>
#include <vector>

class KeySignManager {
public:

    explicit KeySignManager(const std::filesystem::path &path);

    void AddData(const std::vector<int64_t> &key, const std::vector<int64_t> &sign);

    std::vector<int64_t> GetKey(const std::vector<int64_t> &sing) const;

    void RemoveData(const std::vector<int64_t> &key);

private:

    std::filesystem::path path_;

};
