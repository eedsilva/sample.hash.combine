#pragma once

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
    };
}