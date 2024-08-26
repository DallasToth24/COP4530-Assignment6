#include "passserver.h"

namespace cop4530 {

    // ***********************************************************************
    // * Function Name: PassServer                                           *
    // * Description: Constructor for the PassServer class                   *
    // *                                                                     *
    // * Parameter Description:                                              *
    // * - size_t size: The initial size of the hash table                   *
    // *                                                                     *
    // * Date: 7/17/2024                                                     *
    // * Author: Dallas Toth                                                 *
    // * References: None                                                    *
    // ***********************************************************************
PassServer::PassServer(size_t size) : table(size) {
    
}

    // ***********************************************************************
    // * Function Name: ~PassServer                                          *
    // * Description: Destructor for the PassServer class. clears the        *
    // *              underlying hash table.                                 *
    // *                                                                     *
    // * Parameter Description:                                              *
    // * - None                                                              *
    // * Date: 7/17/2024                                                     *
    // * Author: Dallas Toth                                                 *
    // * References: None                                                    *
    // ***********************************************************************
PassServer::~PassServer() {
    table.clear();
}

    // ***********************************************************************
    // * Function Name: load                                                 *
    // * Description: Loads user password pairs from a file into the         *
    // *                                                                     *
    // * Parameter Description:                                              *
    // * - const char* filename: name of the file to load from               *
    // *                                                                     *
    // * Date: 7/17/2024                                                     *
    // * Author: Dallas Toth                                                 *
    // * References: None                                                    *
    // ***********************************************************************
bool PassServer::load(const char* filename) {
    std::ifstream infile(filename);
    if (!infile) {
        return false;
    }
     table.clear();
    std::string user, password;
    while (infile >> user >> password) {
        addUser({user, password});
    }
    infile.close();
    return true;
}

    // ***********************************************************************
    // * Function Name: addUser                                              *
    // * Description: Adds a user password pair. Encrypts                    *
    // *              the password before insertion                          *
    // *                                                                     *
    // * Parameter Description:                                              *
    // * - std::pair<std::string, std::string>& kv: The user-password pair to add*
    // *                                                                     *
    // * Date: 7/17/2024                                                     *
    // * Author: Dallas Toth                                                 *
    // * References: None                                                    *
    // ***********************************************************************
bool PassServer::addUser(std::pair<std::string, std::string>& kv) {
    kv.second = encrypt(kv.second);
    return table.insert(kv);
}

    // ***********************************************************************
    // * Function Name: addUser                                              *
    // * Description: Adds a user password pair to the PassServer using move *
    // *                                                                     *
    // * Parameter Description:                                              *
    // * - std::pair<std::string, std::string>&& kv: The user password pair  *
    // *                                             to add                  *
    // *                                                                     *
    // * Date: 7/17/2024                                                     *
    // * Author: Dallas Toth                                                 *
    // * References: None                                                    *
    // ***********************************************************************
bool PassServer::addUser(std::pair<std::string, std::string>&& kv) {
    kv.second = encrypt(kv.second);
    return table.insert(std::move(kv));
}

    // ***********************************************************************
    // * Function Name: removeUser                                           *
    // * Description: Removes a user from the PassServer                     *
    // *                                                                     *
    // * Parameter Description:                                              *
    // * - const std::string& k: The username to remove                      *
    // *                                                                     *
    // * Date: 7/17/2024                                                     *
    // * Author: Dallas Toth                                                 *
    // * References: None                                                    *
    // ***********************************************************************
bool PassServer::removeUser(const std::string& k) {
    return table.remove(k);
}

    // ***********************************************************************
    // * Function Name: changePassword                                       *
    // * Description: Changes the password for an existing user in the       *
    // *              PassServer                                             *
    // *                                                                     *
    // * Parameter Description:                                              *
    // * - const std::pair<std::string, std::string>& p:  username and       *
    // *                                                  old password       *
    // * - const std::string& newpassword: new password                      *
    // *                                                                     *
    // * Date: 7/17/2024                                                     *
    // * Author: Dallas Toth                                                 *
    // * References: None                                                    *
    // ***********************************************************************
bool PassServer::changePassword(const std::pair<std::string, std::string>& p, const std::string& newpassword) {
    if (!table.contains(p.first)) {
        return false;
    }
    if (newpassword == p.second) {
        return false;
    }
    std::string encryptedOldPassword = encrypt(p.second);
    if (!table.match({p.first, encryptedOldPassword})) {
        return false;
    }
     table.remove(p.first);
    return table.insert({p.first, encrypt(newpassword)});
}

    // ***********************************************************************
    // * Function Name: find                                                 *
    // * Description: Checks if a user exists                                *
    // *                                                                     *
    // * Parameter Description:                                              *
    // * - const std::string& user: the username to find                     *
    // *                                                                     *
    // * Date: 7/17/2024                                                     *
    // * Author: Dallas Toth                                                 *
    // * References: None                                                    *
    // ***********************************************************************
bool PassServer::find(const std::string& user) const {
    return table.contains(user);
}

    // ***********************************************************************
    // * Function Name: decodepw                                             *
    // * Description: Finds and decrypts the password for a given user       *
    // *                                                                     *
    // * Parameter Description:                                              *
    // * - const std::string& user: The username to find                     *
    // *                                                                     *
    // * Date: 7/17/2024                                                     *
    // * Author: Dallas Toth                                                 *
    // * References: None                                                    *
    // ***********************************************************************
std::string PassServer::decodepw(const std::string& user) const {
    auto encryptedPassword = table.getpassword(user);
    if (encryptedPassword == "NOT FOUND") {
        return "NOT FOUND";
    }
    return decrypt(encryptedPassword);
}

    // ***********************************************************************
    // * Function Name: dump                                                 *
    // * Description: Outputs all user password pairs in the PassServer      *
    // *                                                                     *
    // * Parameter Description:                                              *
    // * - None                                                              *
    // * Date: 7/17/2024                                                     *
    // * Author: Dallas Toth                                                 *
    // * References: None                                                    *
    // ***********************************************************************
void PassServer::dump() const {
    table.dump();
}

    // ***********************************************************************
    // * Function Name: size                                                 *
    // * Description: Returns the number of user password pairs              *                                 
    // *                                                                     *
    // * Parameter Description:                                              *
    // * - None                                                              *
    // *                                                                     *
    // * Date: 7/17/2024                                                     *
    // * Author: Dallas Toth                                                 *
    // * References: None                                                    *
    // ***********************************************************************
size_t PassServer::size() const {
    return table.size();
}

    // ***********************************************************************
    // * Function Name: write_to_file                                        *
    // * Description: Writes all user-password pairs in the PassServer to a  *
    // *              file                                                   *
    // *                                                                     *
    // * Parameter Description:                                              *
    // * - const char* filename: The name of the file to write               *
    // *                                                                     *
    // * Date: 7/17/2024                                                     *
    // * Author: Dallas Toth                                                 *
    // * References: None                                                    *
    // ***********************************************************************
bool PassServer::write_to_file(const char* filename) const {
    return table.write(filename);
}

    // ***********************************************************************
    // * Function Name: encrypt                                              *
    // * Description: Encrypts a string using base64 encoding                *
    // *                                                                     *
    // * Parameter Description:                                              *
    // * - const std::string& str: string being encrypted                    *
    // *                                                                     *
    // * Date: 7/17/2024                                                     *
    // * Author: Dallas Toth                                                 *
    // * References: None                                                    *
    // ***********************************************************************
std::string PassServer::encrypt(const std::string& str) const {
    std::string encoded;
    encoded.resize(((str.size() + 2) / 3) * 4);
    
    size_t encoded_len = base64_encode(reinterpret_cast<const BYTE*>(str.data()), reinterpret_cast<BYTE*>(&encoded[0]), str.size(), 0);
    
    encoded.resize(encoded_len); 
    return encoded;
}

    // ***********************************************************************
    // * Function Name: decrypt                                              *
    // * Description: Decrypts an encoded string                             *
    // *                                                                     *
    // * Parameter Description:                                              *
    // * - const std::string& str: The string to decrypt                     *
    // *                                                                     *
    // * Date: 7/17/2024                                                     *
    // * Author: Dallas Toth                                                 *
    // * References: None                                                    *
    // ***********************************************************************
std::string PassServer::decrypt(const std::string& str) const {
    std::string decoded;
    decoded.resize((str.size() * 3) / 4);
    
    size_t decoded_len = base64_decode(reinterpret_cast<const BYTE*>(str.data()), reinterpret_cast<BYTE*>(&decoded[0]), str.size());
    
    decoded.resize(decoded_len); 
    return decoded;
}

} 
