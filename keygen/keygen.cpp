#include "keygen.h"
#include <hash-calculator/hash_calculator.h>

using std::vector;

uint32_t KeyGen::GeneratePrivateKey(std::string text) {
    HashCalculator hasher;
    return static_cast<uint32_t>(hasher.Calculate(vector<char>(text.begin(), text.end())) >> 32);
}

std::pair<std::vector<int64_t>, std::vector<int64_t>> KeyGen::GenerateSign(uint32_t private_key, uint64_t hash) {
    vector<int64_t> key, sign;
    {
        std::string hash_s = std::to_string(hash);
        sign.assign(hash_s.begin(), hash_s.end());
    }
    srand(private_key);
    for(int64_t& el: sign){
        int64_t num = (static_cast<int64_t>(rand()) + static_cast<int64_t>(rand())) - (static_cast<int64_t>(rand()) + static_cast<int64_t>(rand()));
        el += num;
        key.push_back(-num);
    }
    return {key, sign};
}