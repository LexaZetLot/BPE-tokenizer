#include "BPE.h"

#define BIG_CONSTANT(x) (x##ULL) 

uint64_t RotateRight(uint64_t value, int shift){
    return (value >> shift) | (value << (64 - shift));
}

uint64_t Mix(uint64_t a, uint64_t b){
    a ^= RotateRight(b, 37);
    a *= BIG_CONSTANT(0x9ddfea08eb382d69);
    b ^= RotateRight(a, 27);
    b *= BIG_CONSTANT(0xc6a4a7935bd1e995);
    return a ^ b;
}

uint64_t SimpleCityHash64cons(const char *data, size_t len, size_t sizeHashTable){
    const uint64_t seed = BIG_CONSTANT(0xdeadbeefdeadbeef);
    uint64_t hash = seed ^ len;
    
    const uint64_t *blocks = (const uint64_t *)data;
    size_t num_blocks = len / 8;

    for(int i = 0; i < num_blocks; i++){
        uint64_t k = blocks[i];
        hash = Mix(hash, k);
    }
    
    const uint8_t *tail = (const uint8_t *)(data + num_blocks * 8);
    uint64_t tailValue = 0;
    for (size_t i = 0; i < len % 8; i++) {
        tailValue |= ((uint64_t)tail[i]) << (8 * i);
    }

    hash = Mix(hash, tailValue);
    return hash % sizeHashTable;
}
