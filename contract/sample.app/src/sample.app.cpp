#include "../include/sample.app.hpp"
#include "../include/utils.hpp"

using namespace sample;

app::app(name s, name code, datastream<const char *> ds) : eosio::contract(s, code, ds) {}
app::~app() {}

void app::randfromstr(string seed_user1, string seed_user2) {
    print("\n----------------");
    
    print("\nstr1: ", seed_user1.c_str());
    print("\nstr2: ", seed_user2.c_str());
    
    print("\n----------------");

    auto hash1 = eosio::sha256(seed_user1.c_str(), seed_user1.length());
    auto hash2 = eosio::sha256(seed_user2.c_str(), seed_user2.length());
    randfromhash(hash1, hash2);
    
    print("\n----------------");
}

void app::randfromhash(checksum256 hash_user1, checksum256 hash_user2) {
    uint32_t hash_num = 0;
    hash_combine(hash_num, sha256_to_hex(hash_user1));
    hash_combine(hash_num, sha256_to_hex(hash_user2));
    
    print("\nhash number: ", hash_num);
    
    auto s = hash_num % 100; 
    auto t = hash_num << s;

    uint32_t num = t / 100000;
    print("\nnum: ", num);

    uint32_t map_result = map(0, MAX_INT, 0, 99999, num);
    print("\nmap_result: ", map_result);
    
    to_16bits(map_result);
}

EOSIO_DISPATCH(sample::app, (randfromhash)(randfromstr))
