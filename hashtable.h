#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include <string>
#include <functional>
#include <algorithm>
#include <iostream>
#include <utility>
#include <fstream>
#include "base64.h"

namespace cop4530 {

// max_prime is used by the helpful functions provided to you.
static const unsigned int max_prime = 1301081;
// the default_capacity is used if the initial capacity of the underlying vector of the hash table is zero. 
static const unsigned int default_capacity = 11;

template <typename K, typename V>
class HashTable {
public:
    explicit HashTable(size_t size = 101);
    ~HashTable();
    bool contains(const K& k) const;
    bool match(const std::pair<K, V>& kv) const;
    bool insert(const std::pair<K, V>& kv);
    bool insert(std::pair<K, V>&& kv);
    bool remove(const K& k);
    void clear();
    std::string getpassword(const std::string& user) const;
    bool load(const char* filename);
    void dump() const;
    bool write(const char* filename) const;
    size_t size() const; // added size function

private:
    std::vector<std::list<std::pair<K, V>>> Lists;
    size_t currentSize;
    void makeEmpty();
    void rehash();
    size_t myhash(const K& k) const;
    unsigned long prime_below(unsigned long) const;
    void setPrimes(std::vector<unsigned long>&) const;
    std::string encrypt(const std::string& str) const;
    std::string decrypt(const std::string& str) const;
};

} 
#include "hashtable.hpp"

#endif 
