#pragma once

#include <cstdint>

#include <cryptographic/cryptographic.h>

class HashCalculator {
public:
    HashCalculator();

    uint64_t Calculate(const std::vector<char> &data);

private:
    Cryptographic::Provider provider_;
};
