#ifndef _UTILS_H
#define _UTILS_H

#include <set>
#include <stdint.h>
#include <unordered_set>

namespace utils {
template <typename Key>
bool contains(const std::unordered_set<Key>& set, const Key& key) {
    return set.find(key) != set.end();
}

template <typename Key>
size_t hash_combine(size_t seed, const Key& key) {
    std::hash<Key> hash;
    return seed ^ (hash(key) + 0x9e3779b9 + (seed << 6) + (seed >> 2));
}

inline uint8_t convert_digit_to_int(char digit) {
    // The standard guarantees that the digits 0 through 9 have
    // consecutive char values.
    return digit - '0';
}
}

#endif
