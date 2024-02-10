#pragma once

#include <windows.h>
#include <wincrypt.h>

namespace Cryptographic {
    class Provider {
    public:
        Provider();

        ~Provider();

        HCRYPTPROV GetProvider() const;

    private:
        HCRYPTPROV provider_;
    };
}
