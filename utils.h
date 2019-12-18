#ifndef _UTILS_H
#define _UTILS_H

#include <set>
#include <stdint.h>


namespace utils {
template <typename Key, typename Compare, typename Allocator>
bool contains(const std::set<Key, Compare, Allocator>& set, const Key& key) {
    return set.find(key) != set.end();
}

uint8_t convert_digit_to_int(char digit) {
    return digit - '0';
}
}

#endif
