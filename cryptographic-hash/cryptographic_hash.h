#pragma once

#include <vector>
#include <windows.h>
#include <wincrypt.h>

class CryptographicHash {
public:
    explicit CryptographicHash(HCRYPTPROV provider);

    ~CryptographicHash();

    [[nodiscard]] std::vector<BYTE> Hash(const std::vector<char> &data) const;

private:
    HCRYPTHASH hash_;
};