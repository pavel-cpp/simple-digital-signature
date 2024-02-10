#include "hash_calculator.h"

HashCalculator::HashCalculator() :
        provider_(){}

uint64_t HashCalculator::Calculate(const std::vector<char>& data) {
    Cryptographic::Hash hash(provider_.GetProvider());
    std::vector<BYTE> hash_data = hash(data);

    uint64_t result_hash_value = 0;
    for (size_t i = 0; i < std::min(hash_data.size(), sizeof(result_hash_value)); ++i) {
        result_hash_value <<= 8;
        result_hash_value |= hash_data[i];
    }

    return result_hash_value;
}