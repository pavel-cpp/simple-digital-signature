#include "file_hasher.h"

#include <fstream>
#include <vector>
#include <windows.h>

uint64_t FileHasher::Hash(const std::filesystem::path &path) {
    uint64_t result_hash_value = 0;

    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    file.seekg(0, std::ios::end);
    std::streamsize file_size = file.tellg();
    if (file_size <= 0) {
        throw std::runtime_error("Empty or invalid file");
    }
    file.seekg(0, std::ios::beg);

    std::vector<char> file_content(file_size);
    if (!file.read(file_content.data(), file_size)) {
        throw std::runtime_error("Failed to read file content");
    }

    HCRYPTPROV cryptographic_provider = 0;
    HCRYPTHASH cryptographic_hash = 0;
    if (!CryptAcquireContext(&cryptographic_provider, nullptr, nullptr, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
        throw std::runtime_error("Failed to acquire cryptographic context");
    }

    if (!CryptCreateHash(cryptographic_provider, CALG_SHA_256, 0, 0, &cryptographic_hash)) {
        CryptReleaseContext(cryptographic_provider, 0);
        throw std::runtime_error("Failed to create hash object");
    }

    if (!CryptHashData(cryptographic_hash, reinterpret_cast<const BYTE*>(file_content.data()), file_size, 0)) {
        CryptDestroyHash(cryptographic_hash);
        CryptReleaseContext(cryptographic_provider, 0);
        throw std::runtime_error("Failed to hash file content");
    }

    DWORD hash_size = 0;
    {
        DWORD size_of_hash_size = sizeof(hash_size);
        if (!CryptGetHashParam(cryptographic_hash, HP_HASHSIZE, reinterpret_cast<BYTE*>(&hash_size), &size_of_hash_size, 0)) {
            CryptDestroyHash(cryptographic_hash);
            CryptReleaseContext(cryptographic_provider, 0);
            throw std::runtime_error("Failed to get hash size");
        }
    }

    std::vector<BYTE> hash_data(hash_size);
    if (!CryptGetHashParam(cryptographic_hash, HP_HASHVAL, hash_data.data(), &hash_size, 0)) {
        CryptDestroyHash(cryptographic_hash);
        CryptReleaseContext(cryptographic_provider, 0);
        throw std::runtime_error("Failed to get hash data");
    }

    for (DWORD i = 0; i < std::min(hash_size, static_cast<DWORD>(sizeof(result_hash_value))); ++i) {
        result_hash_value <<= 8;
        result_hash_value |= hash_data[i];
    }

    CryptDestroyHash(cryptographic_hash);
    CryptReleaseContext(cryptographic_provider, 0);

    return result_hash_value;
}
