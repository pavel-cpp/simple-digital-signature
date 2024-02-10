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
        for(char c: hash_s){
            sign.push_back(c - '0');
        }
    }
    srand(private_key);
    for(int64_t& el: sign){
        int64_t key_el = (static_cast<int64_t>(rand()) + static_cast<int64_t>(rand())) - (static_cast<int64_t>(rand()) + static_cast<int64_t>(rand()));
        el += key_el;
        key.push_back(-key_el);
    }
    return {key, sign};
}