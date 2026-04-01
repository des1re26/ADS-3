// Copyright 2025 NNTU-CS
#include <cstdint>
#include <unordered_map>
#include "alg.h"

static std::unordered_map<uint64_t, unsigned int> lenCache;

uint64_t collatzMaxValue(uint64_t num) {
    uint64_t maxVal = num;
    uint64_t n = num;
    
    while (n != 1) {
        if (n % 2 == 0) {
            n = n / 2;
        } else {
            n = 3 * n + 1;
        }
        if (n > maxVal) {
            maxVal = n;
        }
    }
    
    return maxVal;
}

unsigned int collatzLen(uint64_t num) {
    if (num == 1) return 1;
    
    auto it = lenCache.find(num);
    if (it != lenCache.end()) return it->second;
    
    unsigned int len = 0;
    uint64_t n = num;
    
    while (n != 1 && lenCache.find(n) == lenCache.end()) {
        len++;
        if (n % 2 == 0) {
            n = n / 2;
        } else {
            n = 3 * n + 1;
        }
    }
    
    if (lenCache.find(n) != lenCache.end()) {
        len += lenCache[n];
    } else {
        len += 1;
    }
    
    lenCache[num] = len;
    return len;
}

unsigned int seqCollatz(unsigned int *maxlen,
                        uint64_t lbound,
                        uint64_t rbound) {
    unsigned int bestNum = 0;
    unsigned int bestLen = 0;
    
    for (uint64_t num = lbound; num <= rbound; ++num) {
        unsigned int len = collatzLen(num);
        if (len > bestLen) {
            bestLen = len;
            bestNum = static_cast<unsigned int>(num);
        }
    }
    
    if (maxlen != nullptr) {
        *maxlen = bestLen;
    }
    
    return bestNum;
}
