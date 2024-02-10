#include "doc_signer.h"

#include <fstream>
#include <key-sing-manager/key_sign_manager.h>
#include <hash-calculator/hash_calculator.h>
#include <io-tools/io_tools.h>

void WriteData(std::fstream &file, const std::vector<int64_t> &data) {
    size_t size_of_data = data.size();
    file.write(reinterpret_cast<const char *>(&size_of_data), sizeof(size_t));
    file.write(reinterpret_cast<const char *>(data.data()), data.size() * sizeof(int64_t));
}

std::vector<int64_t> ReadData(std::fstream &file) {
    std::vector<int64_t> data;
    size_t size_of_data;
    file.read(reinterpret_cast<char *>(&size_of_data), sizeof(size_t));
    data.resize(size_of_data);
    file.read(reinterpret_cast<char *>(data.data()), size_of_data * sizeof(int64_t));
    return data;
}

void DocSigner::Sign(const std::filesystem::path &path, const std::vector<int64_t> &sign) {
    using std::operator ""s;
    std::filesystem::path path_to_result = path.parent_path() / (path.filename().stem().string() + "_signed");
    if (!std::filesystem::create_directory(path_to_result)) {
        throw std::runtime_error("Cannot create directory!");
    }
    std::filesystem::copy_file(path, path_to_result / path.filename());
    std::fstream sign_file(path_to_result / ((path.filename().stem().string() + ".sign")),
                           std::ios::binary | std::ios::out);
    WriteData(sign_file, sign);
}

bool DocSigner::HasSign(const std::filesystem::path &path) {
    return std::filesystem::exists(path.parent_path() / (path.filename().stem().string() + ".sign"));
}

bool DocSigner::ValidSign(const std::filesystem::path &doc_path, const std::filesystem::path &sign_path) {
    KeySignManager key_manager("repo");
    std::fstream sign_file(sign_path, std::ios::binary | std::ios::in);
    auto sign = ReadData(sign_file);
    auto key = key_manager.GetKey(sign);
    if (key.empty()) {
        return false;
    }
    if (key.size() != sign.size()) {
        return false;
    }
    uint64_t hash = 0;
    for (int i = 0; i < sign.size(); ++i) {
        hash = hash * 10 + (sign[i] + key[i]);
    }
    HashCalculator hash_calc;
    return hash_calc.Calculate(ReadContents(doc_path)) == hash;
}
