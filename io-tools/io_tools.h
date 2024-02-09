#pragma once

#include <filesystem>
#include <vector>

std::vector<char> ReadContents(const std::filesystem::path& path);