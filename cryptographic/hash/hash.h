#pragma once

#include <vector>
#include <windows.h>
#include <wincrypt.h>

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

