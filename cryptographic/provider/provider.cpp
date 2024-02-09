#include "provider.h"

#include <stdexcept>

Cryptographic::Provider::Provider() {
    if (!CryptAcquireContext(&provider_, nullptr, nullptr, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
        throw std::runtime_error("Failed to acquire cryptographic context");
    }
}

Cryptographic::Provider::~Provider() {
    CryptReleaseContext(provider_, 0);
}

HCRYPTPROV Cryptographic::Provider::GetProvider() const {
    return provider_;
}
