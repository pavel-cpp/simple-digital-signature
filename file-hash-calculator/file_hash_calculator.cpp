#include "file_hash_calculator.h"

FileHashCalculator::FileHashCalculator() :
        provider_(),
        hash_(provider_.GetProvider()) {}

uint64_t FileHashCalculator::Calculate(const std::filesystem::path& path) {
    std::vector<BYTE> hash_data = hash_(ReadContents(path));

    // Преобразование байтового хеша в uint64_t
    uint64_t result_hash_value = 0;
    for (size_t i = 0; i < std::min(hash_data.size(), sizeof(result_hash_value)); ++i) {
        result_hash_value <<= 8;
        result_hash_value |= hash_data[i];
    }

    return result_hash_value;
}