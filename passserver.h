#ifndef PASSSERVER_H
#define PASSSERVER_H

#include "hashtable.h"
#include "base64.h"
#include <string>

namespace cop4530 {

class PassServer {
public:
    PassServer(size_t size = 101);
    ~PassServer();

    bool load(const char* filename);
    bool addUser(std::pair<std::string, std::string>& kv);
    bool addUser(std::pair<std::string, std::string>&& kv);
    bool removeUser(const std::string& k);
    bool changePassword(const std::pair<std::string, std::string>& p, const std::string& newpassword);
    bool find(const std::string& user) const;
    std::string decodepw(const std::string& user) const;
    void dump() const;
    size_t size() const;
    bool write_to_file(const char* filename) const;

private:
    HashTable<std::string, std::string> table;
    std::string encrypt(const std::string& str) const;
    std::string decrypt(const std::string& str) const;
};

} 

#endif 
