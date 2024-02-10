#pragma once

#include <filesystem>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> data){
    bool first = true;
    for(const T& item: data){
        if(first){
            os << item;
            first = false;
            continue;
        }
        os << " " << item;
    }
    return os;
}

std::vector<char> ReadContents(const std::filesystem::path& path);

void WriteData(std::fstream &file, const std::vector<int64_t> &data);

std::vector<int64_t> ReadData(std::fstream &file);