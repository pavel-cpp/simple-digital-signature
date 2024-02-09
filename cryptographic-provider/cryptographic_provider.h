#pragma once

#include <wincrypt.h>

class CryptographicProvider {
public:
    CryptographicProvider();

    ~CryptographicProvider();

    HCRYPTPROV GetProvider() const;

private:
    HCRYPTPROV provider_;
};