#pragma once
#ifndef FIFO_MAP_H
#define FIFO_MAP_H

#include<unordered_map>
#include<list>
#include<string>

using KeyType = std::string;
using ValueType = int;
using Pair = std::pair<const KeyType, ValueType>;

class FifoMap {
public:

    class Iterator {
    public:
        Iterator(FifoMap&, std::list<KeyType>::iterator);
        Iterator(const Iterator&); // copy constructor

        Iterator& operator=(const Iterator&); // copy-assign

        Iterator& operator++(); // Increment

        bool operator==(const Iterator&) const; // equality
        bool operator!=(const Iterator&) const; // inequality

        Pair& operator*() const noexcept; // dereference
        Pair* operator->() const noexcept; // arrow dereference

    private:
        FifoMap& map;
        std::list<KeyType>::iterator m_iter;
    };

    FifoMap(); // default constructor
    FifoMap(const FifoMap&); // copy constructor

    size_t size() const;
    bool empty() const;
    size_t count(const KeyType&) const;
    void clear() noexcept;

    ValueType& operator[](const KeyType&); // indexer
    FifoMap& operator=(const FifoMap&); // copy-assign

    void erase(const std::string&);

    Iterator begin();
    Iterator end();

private:
    std::unordered_map<KeyType, ValueType> m_map;
    std::list<KeyType> m_keylist;
};

#endif
