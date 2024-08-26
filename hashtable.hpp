#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include "hashtable.h"

namespace cop4530 {

    // ***********************************************************************
    // * Function Name: HashTable                                            *
    // * Description: Constructor for the HashTable class, initializes the   *
    // *              hash table with a specified size                       *
    // *                                                                     *
    // * Parameter Description:                                              *
    // * - size_t size: initial size of the hash table                       *
    // *                                                                     *
    // * Date: 7/17/2024                                                     *
    // * Author: Dallas Toth                                                 *
    // * References: None                                                    *
    // ***********************************************************************
template <typename K, typename V>
HashTable<K, V>::HashTable(size_t size) : currentSize(0) {
     if (size < 1) {
        size = 101;
    }
    size_t primeSize = prime_below(size);
    Lists.resize(primeSize);
}

    // ***********************************************************************
    // * Function Name: ~HashTable                                           *
    // * Description: Destructor, clears the hash table                      *
    // *                                                                     *
    // * Parameter Description: none                                         *
    // * Date: 7/17/2024                                                     *
    // * Author: Dallas Toth                                                 *
    // * References: None                                                    *
    // ***********************************************************************
template <typename K, typename V>
HashTable<K, V>::~HashTable() {
    clear();
}

    // ***********************************************************************
    // * Function Name: contains                                             *
    // * Description: Checks if a key is  in the hash table                  *
    // *                                                                     *
    // * Parameter Description:                                              *
    // * - const K& k: The key to check for  in the hash table               *
    // * Date: 7/17/2024                                                     *
    // * Author: Dallas Toth                                                 *
    // * References: None                                                    *
    // ***********************************************************************
template <typename K, typename V>
bool HashTable<K, V>::contains(const K& k) const {
    auto& selectedList = Lists[myhash(k)];
    for (const auto& kv : selectedList) {
    if (kv.first == k) {
        return true;
    }
}
    return false;
}

    // ***********************************************************************
    // * Function Name: match                                                *
    // * Description: Checks if a given key value pair is  in the table      *
    // *                                                                     *
    // * Parameter Description:                                              *
    // * - const std::pair<K, V>& kv: The key value pair to check for        *
    // *                              presence in the hash table             *
    // * Date: 7/17/2024                                                     *
    // * Author: Dallas Toth                                                 *
    // * References: None                                                    *
    // ***********************************************************************
template <typename K, typename V>
bool HashTable<K, V>::match(const std::pair<K, V>& kv) const {
    auto encryptedValue = encrypt(kv.second);
    auto& selectedList = Lists[myhash(kv.first)];
    for (const auto& pair : selectedList) {
        if (pair.first == kv.first && pair.second == encryptedValue) {
            return true;
        }
    }
    return false;
}

    // ***********************************************************************
    // * Function Name: insert                                               *
    // * Description: Inserts a key value pair into the hash table           *
    // *                                                                     *
    // * Parameter Description:                                              *
    // * - std::pair<K, V>&& kv: The key value pair to insert                *
    // * Date: 7/17/2024                                                     *
    // * Author: Dallas Toth                                                 *
    // * References: None                                                    *
    // ***********************************************************************
template <typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K, V>& kv) {
    auto& selectedList = Lists[myhash(kv.first)];
    for (const auto& pair : selectedList) {
        if (pair.first == kv.first) {
            return false;
        }
    }
    selectedList.push_back({kv.first, encrypt(kv.second)});
    if (++currentSize > Lists.size()) {
        rehash();
    }
    return true;
}

    // ***********************************************************************
    // * Function Name: insert                                               *
    // * Description: Inserts a key value pair using move semantics.         *
    // *              Fails if key exists                                    *
    // *                                                                     *
    // * Parameter Description:                                              *
    // * - std::pair<K, V>&& kv: The key-value pair to insert                *
    // * Date: 7/17/2024                                                     *
    // * Author: Dallas Toth                                                 *
    // * References: None                                                    *
    // ***********************************************************************
template <typename K, typename V>
bool HashTable<K, V>::insert(std::pair<K, V>&& kv) {
    auto& selectedList = Lists[myhash(kv.first)];
    for (const auto& pair : selectedList) {
        if (pair.first == kv.first) {
            return false;
        }
    }
    selectedList.push_back({std::move(kv.first), encrypt(std::move(kv.second))});
    
    if (++currentSize > Lists.size()) {
        rehash();
    }
    return true;
}

    // ***********************************************************************
    // * Function Name: remove                                               *
    // * Description: Removes a key value pair from the hash table           *
    // *                                                                     *
    // * Parameter Description:                                              *
    // * - const K& k: The key to remove                                     *
    // * Date: 7/17/2024                                                     *
    // * Author: Dallas Toth                                                 *
    // * References: None                                                    *
    // ***********************************************************************
template <typename K, typename V>
bool HashTable<K, V>::remove(const K& k) {
    auto& selectedList = Lists[myhash(k)];
    auto iterate = std::find_if(selectedList.begin(), selectedList.end(), [&k](const std::pair<K, V>& kv) {
        return kv.first == k;
    });
    if (iterate == selectedList.end()) {
        return false;
    }
      selectedList.erase(iterate);
    currentSize--;
    return true;
}

    // ***********************************************************************
    // * Function Name: clear                                                *
    // * Description: Clears the hash table by removing all key-value pairs. *
    // * Parameter Description:                                              *
    // * - None                                                              *
    // * Date: 7/17/2024                                                     *
    // * Author: Dallas Toth                                                 *
    // * References: None                                                    *
    // ***********************************************************************
template <typename K, typename V>
void HashTable<K, V>::clear() {
    makeEmpty();
}

    // ***********************************************************************
    // * Function Name: getpassword                                          *
    // * Description: Retrieves the password for a user                      *
    // * Parameter Description:                                              *
    // * - const std::string& user: The username to look up.                 *
    // *                                                                     *
    // * Date: 7/17/2024                                                     *
    // * Author: Dallas Toth                                                 *
    // * References: None                                                    *
    // ***********************************************************************
template <typename K, typename V>
std::string HashTable<K, V>::getpassword(const std::string& user) const {
    auto& selectedList = Lists[myhash(user)];
    auto iterate = std::find_if(selectedList.begin(), selectedList.end(), [&user](const std::pair<K, V>& kv) {
        return kv.first == user;
    });
    if (iterate == selectedList.end()) {
        return "NOT FOUND";
    }
    return decrypt(iterate -> second); 
}

    // ***********************************************************************
    // * Function Name: load                                                 *
    // * Description: Loads key-value pairs from file into the hash table    *
    // *              Clears the current table before loading                *
    // *                                                                     *
    // * Parameter Description:                                              *
    // * - const char* filename: The name of the file to load from           *
    // *                                                                     *
    // * Date: 7/17/2024                                                     *
    // * Author: Dallas Toth                                                 *
    // * References: None                                                    *
    // ***********************************************************************
template <typename K, typename V>
bool HashTable<K, V>::load(const char* filename) {
    K key;
    V value;
    std::ifstream infile(filename);
    if (!infile) {
        return false;
    }
    clear();
    while (infile >> key >> value) {
        insert({key, value});
    }
    infile.close();
    
    return true;
}

    // ***********************************************************************
    // * Function Name: dump                                                 *
    // * Description: Outputs all key value pairs in the hash table          *
    // *                                                                     *
    // * Parameter Description:                                              *
    // * - None                                                              *
    // * Date: 7/17/2024                                                     *
    // * Author: Dallas Toth                                                 *
    // * References: None                                                    *
    // ***********************************************************************
template <typename K, typename V>
void HashTable<K, V>::dump() const {
    for (const auto& selectedList : Lists) {
        for (const auto& kv : selectedList) {
            std::cout << kv.first << " " << kv.second << std::endl;
        }
    }
}

    // ***********************************************************************
    // * Function Name: write                                                *
    // * Description: Writes all key value pairs in the hash table to a file *
    // *                                                                     *
    // * Parameter Description:                                              *
    // * - const char* filename: The name of the file to write               *
    // *                                                                     *
    // * Date: 7/17/2024                                                     *
    // * Author: Dallas Toth                                                 *
    // * References: None                                                    *
    // ***********************************************************************
template <typename K, typename V>
bool HashTable<K, V>::write(const char* filename) const {
    std::ofstream outfile(filename);
    if (!outfile) {
        return false;
    }
    for (const auto& selectedList : Lists) {
        for (const auto& kv : selectedList) {
            outfile << kv.first << " " << kv.second << std::endl;
        }
    }
    outfile.close();
    
    return true;
}

    // ***********************************************************************
    // * Function Name: makeEmpty                                            *
    // * Description: Clears all key value pairs from hash table             *
    // *                                                                     *
    // * Parameter Description:                                              *
    // * - None                                                              *
    // * Date: 7/17/2024                                                     *
    // * Author: Dallas Toth                                                 *
    // * References: None                                                    *
    // ***********************************************************************
template <typename K, typename V>
void HashTable<K, V>::makeEmpty() {
    for (auto& thisList : Lists) {
        thisList.clear();
    }
    currentSize = 0;
}

    // ***********************************************************************
    // * Function Name: rehash                                               *
    // * Description: Resizes the hash table and re inserts all key value    *
    // *              pairs                                                  *
    // *                                                                     *
    // * Parameter Description:                                              *
    // * - None                                                              *
    // * Date: 7/17/2024                                                     *
    // * Author: Dallas Toth                                                 *
    // * References: None                                                    *
    // ***********************************************************************
template <typename K, typename V>
void HashTable<K, V>::rehash() {
    std::vector<std::list<std::pair<K, V>>> oldLists = Lists;
    
    Lists.resize(prime_below(2 * Lists.size()));
    for (auto& thisList : Lists) {
        thisList.clear();
    }
    currentSize = 0;
    
    for (auto& thisList : oldLists) {
        for (auto& kv : thisList) {
            insert(std::move(kv));
        }
    }
}
    // ***********************************************************************
    // * Function Name: myhash                                               *
    // * Description: Calculates the hash value for a key                    *
    // *                                                                     *
    // * Parameter Description:                                              *
    // * - const K& k: The key to hash.                                      *
    // * Date: 7/17/2024                                                     *
    // * Author: Dallas Toth                                                 *
    // * References: None                                                    *
    // ***********************************************************************
template <typename K, typename V>
size_t HashTable<K, V>::myhash(const K& k) const {
    static std::hash<K> hf;
    return hf(k) % Lists.size();
}

// returns largest prime number <= n or zero if input is too large
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below(unsigned long n) const {
    if (n > max_prime) {
        std::cerr << "** input too large for prime_below()\n";
        return 0;
    }
    if (n == max_prime) {
        return max_prime;
    }
    if (n <= 1) {
        std::cerr << "** input too small \n";
        return 0;
    }
    // now: 2 <= n < max_prime
    std::vector<unsigned long> v(n + 1);
    setPrimes(v);
    while (n > 2) {
        if (v[n] == 1)
            return n;
        --n;
    }
    return 2;
}

// Sets all prime number indexes to 1. Called by method prime_below(n)
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes) const {
    int i = 0;
    int j = 0;

    vprimes[0] = 0;
    vprimes[1] = 0;
    int n = vprimes.capacity();

    for (i = 2; i < n; ++i)
        vprimes[i] = 1;

    for (i = 2; i * i < n; ++i) {
        if (vprimes[i] == 1)
            for (j = i + i; j < n; j += i)
                vprimes[j] = 0;
    }
}

    // ***********************************************************************
    // * Function Name: encrypt                                              *
    // * Description: Encrypts a string using base64                         *
    // *                                                                     *
    // * Parameter Description:                                              *
    // * - const std::string& str:  string to be encrypted                   *
    // *                                                                     *
    // * Date: 7/17/2024                                                     *
    // * Author: Dallas Toth                                                 *
    // * References: None                                                    *
    // ***********************************************************************
template <typename K, typename V>
std::string HashTable<K, V>::encrypt(const std::string& str) const {
    std::string encoded;
    encoded.resize(((str.size() + 2) / 3) * 4);
    
    base64_encode(reinterpret_cast<const BYTE*>(str.data()), reinterpret_cast<BYTE*>(&encoded[0]), str.size(), 0);
    return encoded;
}

    // ***********************************************************************
    // * Function Name: decrypt                                              *
    // * Description: Decrypts a base64 encoded string                       *
    // *                                                                     *
    // * Parameter Description:                                              *
    // * - const std::string& str: The string to be decrypted                *
    // *                                                                     *
    // * Date: 7/17/2024                                                     *
    // * Author: Dallas Toth                                                 *
    // * References: None                                                    *
    // ***********************************************************************
template <typename K, typename V>
std::string HashTable<K, V>::decrypt(const std::string& str) const {
    std::string decoded;
    decoded.resize((str.size() * 3) / 4);
    
    base64_decode(reinterpret_cast<const BYTE*>(str.data()), reinterpret_cast<BYTE*>(&decoded[0]), str.size());
    return decoded;
}

    // ***********************************************************************
    // * Function Name: size                                                 *
    // * Description: Returns the number of key value pairs in the hash table*
    // *                                                                     *
    // * Parameter Description:                                              *
    // * - None                                                              *
    // * Date: 7/17/2024                                                     *
    // * Author: Dallas Toth                                                 *
    // * References: None                                                    *
    // ***********************************************************************
template <typename K, typename V>
size_t HashTable<K, V>::size() const {
    return currentSize;
}
} 
#endif 
