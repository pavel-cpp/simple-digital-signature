#pragma once

#include <vector>
#include <wincrypt.h>
#include <windows.h>

namespace Cryptographic {
    class Hash {
    public:
        explicit Hash(HCRYPTPROV provider);

        ~Hash();

        [[nodiscard]] std::vector<BYTE> operator()(const std::vector<char> &data);

    private:
        HCRYPTHASH hash_;
    };
}

