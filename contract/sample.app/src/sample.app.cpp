#include "../include/sample.app.hpp"

using namespace sample;

app::app(name s, name code, datastream<const char *> ds) : eosio::contract(s, code, ds) {}
app::~app() {}


void app::randfromstr(string seed_user1, string seed_user2) {
    print("\n----------------");
    
    print("\nstr1: ", seed_user1.c_str());
    print("\nstr1: ", seed_user2.c_str());
    
    print("\n----------------");
    
    auto hash1 = eosio::sha256(seed_user1.c_str(), seed_user1.length());
    auto hash2 = eosio::sha256(seed_user2.c_str(), seed_user2.length());
    randfromhash(hash1, hash2);
    
    print("\n----------------");
}

void app::randfromhash(checksum256 hash_user1, checksum256 hash_user2) {
    size_t num = 0;
    hash_combine(num, sha256_to_hex(hash_user1));
    hash_combine(num, sha256_to_hex(hash_user2));
    
    print("\nnumber: ", num);
}

EOSIO_DISPATCH(sample::app, (randfromhash)(randfromstr))
