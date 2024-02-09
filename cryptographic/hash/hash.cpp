#include "hash.h"

#include <stdexcept>

Cryptographic::Hash::Hash(HCRYPTPROV provider) : hash_(0) {
    if (!CryptCreateHash(provider, CALG_SHA_256, 0, 0, &hash_)) {
        CryptReleaseContext(provider, 0);
        throw std::runtime_error("Failed to create hash object");
    }
}

Cryptographic::Hash::~Hash() {
    CryptDestroyHash(hash_);
}

std::vector<BYTE> Cryptographic::Hash::operator()(const std::vector<char> &data) const {
    if (!CryptHashData(hash_, reinterpret_cast<const BYTE*>(data.data()), data.size(), 0)) {
        CryptDestroyHash(hash_);
        throw std::runtime_error("Failed to hash data");
    }

    DWORD hash_size = 0;
    if (!CryptGetHashParam(hash_, HP_HASHSIZE, reinterpret_cast<BYTE*>(&hash_size), 0, 0)) {
        CryptDestroyHash(hash_);
        throw std::runtime_error("Failed to get hash size");
    }

    std::vector<BYTE> hash_data(hash_size);
    if (!CryptGetHashParam(hash_, HP_HASHVAL, hash_data.data(), &hash_size, 0)) {
        CryptDestroyHash(hash_);
        throw std::runtime_error("Failed to get hash data");
    }

    return hash_data;

}
