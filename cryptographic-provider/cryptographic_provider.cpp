#include "cryptographic_provider.h"

#include <stdexcept>

CryptographicProvider::CryptographicProvider() {
    if (!CryptAcquireContext(&provider_, nullptr, nullptr, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
        throw std::runtime_error("Failed to acquire cryptographic context");
    }
}

CryptographicProvider::~CryptographicProvider() {
    CryptReleaseContext(provider_, 0);
}

HCRYPTPROV CryptographicProvider::GetProvider() const {
    return provider_;
}
