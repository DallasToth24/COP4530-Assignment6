Project Description:
This project contains two parts. In the first part of the project, you need to implement a hash table class template named HashTable. In the second part of the project, you will develop a simple password server program using the hash table you developed.

Task 1: Requirements of the HastTable Class Template 

Your implementation of HashTable must be in the namespace of cop4530. You must provide the template declaration and implementation in two different files:
hashtable.h (containing HashTable class template declaration) and hashtable.hpp (containing the implementation of member functions).
You must include hashtable.hpp inside hashtable.h as we have done in the previous projects. The two files hashtable.h and hashtable.hpp will be provided to you, which contain some helpful functions that you will need to use in developing the hash table class template.
You must implement hash table using the technique of chaining with separate lists (separate chaining). That is, the internal data structure of the hash table class template should be a vector of lists. Use existing C++ STL containers for the internal storage (instead of any containers you developed in the previous
projects)
You must implement at minimum all the interfaces specified below for the
HashTable class template.

Public HashTable interface (K and V)  are template parameters (generic data types), which represent the key and value types for a table entry, respectively)
HashTable(size_t size = 101): constructor. Create a hash table, where the size of the vector is set to prime_below(size) (where size is default to 101), where prime_below() is a private member function of the HashTable and provided to you.  If an invalide value is entered of less than 1 then the default value of 101 is used.   When setting the size , accept the value entered in on the Default Constructor and call the functions to find out the first Prime Number at or below that number to set the size of the vector in the hash table. 
~HashTable(): destructor. Delete all elements in hash table.
bool contains(const K & k): check if key k is in the hash table.
bool match(const std::pair<K, V> &kv) : check if key-value pair is in the hash table.  Note the password or second value must be encrypted before comparison.   This function is sually used in checking logins.  
bool insert(const std::pair<K, V> & kv): add the key-value pair kv into the hash table. Don't add if kv is already in the hash table. Return True if the value was found, False otherwise.  
bool insert (std::pair<K, V> && kv): move version of insert.  Same specication as the copy version . 
bool remove(const K & k): delete the key k and the corresponding value if it is in the hash table. Return true if k is deleted, return false otherwise (i.e., if key k is not in the hash table).
void clear(): delete all elements in the hash table
string getpassword(const string & s): Returns the encrypted password for the user passed in.   If no user is found a message that can be checked is returned such as "NOT FOUND".  
bool load(const char *filename): load the content of the file with name filename into the hash table. In the file, each line contains a single pair of key and value, separated by a white space.  This function will clear the current table it if is not already and call insert.  This assumes the passwords have already been encrypted.  
void dump(): display all entries in the hash table. If an entry contains multiple key-value pairs, separate them by a semicolon character (:)   Do not decrypt the password before showing. 
bool write(const char *filename): write all elements in the hash table into a file with name filename. Similar to the file format in the load function, each line contains a pair of key-value pair, separated by a white space. Do not decrypt the password before writing to the file.  
Private Helper Functions: 

void makeEmpty(): delete all elements in the hash table. The public interface clear() will call this function.
void rehash(): Rehash function. Called when the number of elements in the hash table is greater than the size of the vector.
size_t myhash(const K &k): return the index of the vector entry where k should be stored. COP4530 Data Structures and Algorithm Analysis
unsigned long prime_below (unsigned long) and void setPrimes(vector&): two helpful functions to determine the proper prime numbers used in setting up the vector size. Whenever you need to set hash table to a new size "sz", call prime_below(sz) to determine the new proper underlying vector size. These two functions have been provided in hashtable.h and hashtable.hpp.
Make sure to declare as const member functions any for which this is appropriate You need to write a simple test program to test various functions of hash table. More details are provided in a later part of this description.

Task 2: Requirements of the Password Server Class (PassSever)

Name the password server class as PassServer. Its declaration and implementation should be provided in two files, passserver.h and passserver.cpp, respectively.
PassServer should be implemented as an adaptor class, with the HashTable you developed as the adaptee class. The type for both K and V in HashTable should be string. The key and value will be the username and password, respectively.
PassServer must store username and encrypted password pairs in the hash table.
PassServer must at least support the following member functions (again, make sure to declare as const member functions any that are appropriate):
Public Interface: 

PassServer(size_t size = 101): constructor, create a hash table of the specified size. You just need to pass this size parameter to the constructor of the HashTable. Therefore, the real hash table size could be different from the parameter size (because prime_below() will be called in the constructor of the HashTable).
~PassServer(): destructor. You need to decide what you should do based on your design of PassServer (how you develop the adaptor class based on the adaptee HashTable). In essence, we do not want to have memory leak.
bool load(const char *filename): load a password file into the HashTable object. Each line contains a pair of username and an un-encrypted password. Read in the name and encrypt the password and insert into the hash table.   This function is used to initially load the hast table with usernames and passwords.   Use the hashtable insert function to load them into the hast table. 
bool addUser(std::pair<string, string> & kv): add a new username and password. The password passed in is in plaintext, it should be encrypted before insertion.
bool addUser(std::pair<string, string> && kv): move version of addUser.
bool removeUser(const string & k): delete an existing user with username k.
bool changePassword(const pair<string, string> &p, const string & newpassword): change an existing user's password. Note that both passwords passed in are in plaintext. They should be encrypted before you interact with the hash table. If the user is not in the hash table, or they are in the  hashtable but the old password does not then return false;  Also return false if the new password and the old password are the same (i.e., we cannot update the password).
bool find(const string & user): check if a user exists (if user is in thehash table).
string decodepw(const string & s):  Finds the user in string "s" and returns the decoded password to be displayed. Used to make sure the encryption works.   
void dump(): show the structure and contents of the HashTable object to the screen. This should just call the hashtable dump routine.  
size_t size(): return the size of the HashTable (the number of username/password pairs in the table).
bool write_to_file(const char *filename):  Should just call the associated HashTable routine that writes the file with encrypted passwords.    
Private Helper Functions:  

string encrypt(const string & str): encrypt the parameter str and return the encrypted string.
For this project, we will use a modified encryption and and un-encryption algorithm that was modified to be used in this course.  The code for this base64.h and base64.cpp. 
encode you pass a string and it returns the encoded string.
decode you pasa s string that represents the encoded string and it returns it decoded.   
Driver Program:

In addition to developing the HashTable class template and the PassServer class, you need to write a driver program to test your code. Name the driver program proj6.cpp.

 A partial implementation of proj6.cpp is provided to you, which contains a Menu() function. You must use this function as the standard option menu for user to type input. You may not alter the Menu function.
The driver program must re-prompt the user for the next choice from the menu and exit the program only when the user selection the exit "x" option.
Run the provided executable proj6.x on linprog to see the expected behavior of each of the menu options, and the expected order of inputs. Make sure to test with error cases too, so that you see the appropriate error messages that are printed.
Provided Partial code:  The following partial code has been provided for you.  

 hashtable.h: partial implementation
 hashtable.hpp: partial implementation
proj6.cpp: driver program, partial implementation.
test1: sample test case (which contains the commands that a user will type). You can redirect it to proj6.x as "proj6.x < test1". Results will save in the file "outtest1"
base64.h     Definition file for the encryption algorithm.  Do not modify these files. 
base64.cpp  Implementation file for the encryption algorithm. Do not modify these files.  
Deliverables: 

Your implementation must be entirely contained in the following files, which MUST be named in the same way.

hashtable.h
hashtable.hpp
passserver.h
passserver.cpp
proj6.cpp
makefile
