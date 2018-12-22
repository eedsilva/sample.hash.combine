#include <eosiolib/crypto.h>
#include <eosiolib/types.h>
#include <eosiolib/eosio.hpp>

using namespace eosio;
using namespace std;

namespace sample {
    
    uint32_t map(uint32_t min, uint32_t max, uint32_t min_rang, uint32_t max_rang, uint32_t num) {
         return  num * (max - min) / (max_rang - min_rang);
    }

    string sha256_to_hex(const checksum256 &sha256) {
        std::string r;
        uint32_t len = sizeof(sha256.data());    
        uint8_t *c = (uint8_t *)sha256.data();
        const char *to_hex = "0123456789abcdef";
        
        for (uint32_t i = 0; i < len; ++i) (r += to_hex[(c[i] >> 4)]) += to_hex[(c[i] & 0x0f)];
        return r;
    }

    // copied from boost https://www.boost.org/
    template <class T> inline void hash_combine(uint32_t &seed, const T &v) {
        std::hash<T> hasher;
        seed ^= hasher(v) + 0x9e3779b9 + (seed << 8) + (seed >> 2);
    }
}