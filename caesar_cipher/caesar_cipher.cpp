#include "caesar_cipher.h"

std::string Decipher(const std::string& cipher, size_t shift) {
    auto ciphers = cipher;
    const size_t fixed_symbols = 26;
    for (size_t i = 0; i < cipher.length(); ++i) {
        ciphers[i] = static_cast<char>(static_cast<char>(cipher[i]) - shift);
        if (ciphers[i] < 'A') {
            ciphers[i] = static_cast<char>(static_cast<char>(ciphers[i]) + fixed_symbols);
        }
    }
    return ciphers;
}