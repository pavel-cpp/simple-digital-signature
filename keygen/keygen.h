#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace KeyGen {

    uint32_t GeneratePrivateKey(std::string text);

    std::pair<std::vector<int64_t>, std::vector<int64_t>> GenerateSign(uint32_t private_key, uint64_t hash);

}