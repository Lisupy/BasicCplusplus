#include "FifoMap.h"

FifoMap::FifoMap() : m_map(), m_keylist() {}

FifoMap::FifoMap(const FifoMap &rhs) : m_map(rhs.m_map), m_keylist(rhs.m_keylist) {}

size_t FifoMap::size() const { return m_keylist.size(); }

bool FifoMap::empty() const { return m_keylist.empty(); }

size_t FifoMap::count(const KeyType &key) const {
    uint32_t cnt = 0;
    for (const auto &k : m_keylist) {
        if (k == key) {
            ++cnt;
        }
    }
    return cnt;
}

void FifoMap::clear() noexcept {
    m_keylist.clear();
    m_map.clear();
}

ValueType &FifoMap::operator[](const KeyType &key) {
    if (m_map.end() == m_map.find(key))
        m_keylist.push_back(key);
    return m_map[key];
}

FifoMap &FifoMap::operator=(const FifoMap &rhs) {
    m_keylist = rhs.m_keylist;
    m_map = rhs.m_map;
    return *this;
}

void FifoMap::erase(const std::string &key) {
    if (m_map.find(key) == m_map.end())
        return;
    m_keylist.remove(key);
    m_map.erase(key);
}

FifoMap::Iterator FifoMap::begin() {
    return FifoMap::Iterator(*this, m_keylist.begin());
}

FifoMap::Iterator FifoMap::end() {
    return FifoMap::Iterator(*this, m_keylist.end());
}

/* FifoMap::Iterator Definition */

// constructor
FifoMap::Iterator::Iterator(FifoMap &m, std::list<KeyType>::iterator iter) : map(m), m_iter(iter) {}

// copy constructor
FifoMap::Iterator::Iterator(const FifoMap::Iterator &rhs) : map(rhs.map), m_iter(rhs.m_iter) {}


FifoMap::Iterator &FifoMap::Iterator::operator=(const FifoMap::Iterator &rhs) {
    map = rhs.map;
    m_iter = rhs.m_iter;
    return *this;
}

FifoMap::Iterator &FifoMap::Iterator::operator++() {
    m_iter++;
    return *this;
}

bool FifoMap::Iterator::operator==(const FifoMap::Iterator &rhs) const {
    return m_iter == rhs.m_iter;
}

bool FifoMap::Iterator::operator!=(const FifoMap::Iterator &rhs) const {
    return !this->operator==(rhs);
}

Pair &FifoMap::Iterator::operator*() const noexcept {
    return *map.m_map.find(*m_iter);
}

Pair *FifoMap::Iterator::operator->() const noexcept {
    return &(*map.m_map.find(*m_iter));
}

