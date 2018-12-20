#pragma once

#include <eosiolib/types.h>
#include <eosiolib/crypto.h>
#include <eosiolib/eosio.hpp>

using namespace eosio;
using namespace std;

namespace sample {
    class[[eosio::contract("sample.app")]] app : public eosio::contract {

    public:
        app(name s, name code, datastream<const char *> ds);
        ~app();
        
        [[eosio::action]]
        void randfromstr(string seed_user1, string seed_user2);

        [[eosio::action]]
        void randfromhash(checksum256 hash_user1, checksum256 hash_user2);
    
    private:
        string sha256_to_hex(const checksum256& sha256) {
            return str_to_hex((char*)sha256.data(), sizeof(sha256.data()));
        }

        string str_to_hex(const char* d, uint32_t s) {
            std::string r;
            const char* to_hex = "0123456789abcdef";
            uint8_t* c = (uint8_t*)d;
            for (uint32_t i = 0; i < s; ++i)
                (r += to_hex[(c[i] >> 4)]) += to_hex[(c[i] & 0x0f)];
            return r;
        }

        // copied from boost https://www.boost.org/
        template <class T>
        inline void hash_combine(std::size_t& seed, const T& v) {
            std::hash<T> hasher;
            seed ^= hasher(v) + 0x9e3779b9 + (seed << 8) + (seed >> 2);
        }
    };
}