#include "hash.h"

#include <testing/testing.h>

Cryptographic::Hash::Hash(HCRYPTPROV provider) : hash_(0) {
    if (!CryptCreateHash(provider, CALG_SHA_256, 0, 0, &hash_)) {
        CryptReleaseContext(provider, 0);
        ASSERT_HINT(false, "Failed to create hash object");
    }
}

Cryptographic::Hash::~Hash() {
    CryptDestroyHash(hash_);
}

std::vector<BYTE> Cryptographic::Hash::operator()(const std::vector<char> &data) {

    if (!CryptHashData(hash_, reinterpret_cast<const BYTE*>(data.data()), data.size(), 0)) {
        CryptDestroyHash(hash_);
        ASSERT_HINT(false, "Failed to hash data");
    }

    DWORD hash_size = 0;
    DWORD size_of_hash_size = sizeof(hash_size);
    if (!CryptGetHashParam(hash_, HP_HASHSIZE, reinterpret_cast<BYTE*>(&hash_size), &size_of_hash_size, 0)) {
        CryptDestroyHash(hash_);
        ASSERT_HINT(false, "Failed to get hash size");
    }

    std::vector<BYTE> hash_data(hash_size);
    if (!CryptGetHashParam(hash_, HP_HASHVAL, hash_data.data(), &hash_size, 0)) {
        CryptDestroyHash(hash_);
        ASSERT_HINT(false, "Failed to get hash data");
    }

    return hash_data;

}
