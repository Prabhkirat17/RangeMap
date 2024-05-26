#ifndef INTERVAL_MAP_HPP
#define INTERVAL_MAP_HPP

#include <map>

template <typename K, typename V>
class interval_map {
public:
    void assign(K start, K end, const V& value);
    std::map<K, V> m_map;
};

#include "interval_map.cpp"
#endif 