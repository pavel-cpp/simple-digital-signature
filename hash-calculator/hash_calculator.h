#pragma once

#include <cryptographic/cryptographic.h>
#include <cstdint>

class HashCalculator {
public:
    HashCalculator();
    uint64_t Calculate(const std::vector<char>& data);
private:
    Cryptographic::Provider provider_;
};
