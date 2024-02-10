#pragma once

#include <filesystem>
#include <vector>

std::vector<char> ReadContents(const std::filesystem::path &path);

void WriteData(std::fstream &file, const std::vector<int64_t> &data);

std::vector<int64_t> ReadData(std::fstream &file);