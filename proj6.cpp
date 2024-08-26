#include <iostream>
#include <list>
#include "hashtable.h"
#include "passserver.h"

using namespace std;
using namespace cop4530;

void PrintMenu();
void useLoad(PassServer& ps);
void useAddUser(PassServer& ps);
void useRemoveUser(PassServer& ps);
void useChangePassword(PassServer& ps);
void useFindUser(PassServer& ps);
void useDisplayPassword(PassServer& ps);
void useDumpHashTable(PassServer& ps);
void useHashTableSize(PassServer& ps);
void useWriteToFile(PassServer& ps);

int main() {
    size_t size;
    cout << "Enter hash table size: ";
    cin >> size;
    PassServer ps(size);

    char choice;
    do {
        PrintMenu();
        cin >> choice;

        switch (choice) {
         case 'l':
            useLoad(ps);
                break;
         case 'a':
            useAddUser(ps);
                break;
        case 'r':
            useRemoveUser(ps);
                break;
        case 'c':
            useChangePassword(ps);
                break;
        case 'f':
            useFindUser(ps);
                break;
        case 'p':
            useDisplayPassword(ps);
                break;
        case 'd':
            useDumpHashTable(ps);
                break;
        case 's':
            useHashTableSize(ps);
                break;
        case 'w':
            useWriteToFile(ps);
                break;
        case 'x':
            cout << "Exiting program." << endl;
                break;
        default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 'x');

    return 0;
}

void PrintMenu() {
    cout << "\n\n";
    cout << "l - Load From File" << endl;
    cout << "a - Add User" << endl;
    cout << "r - Remove User" << endl;
    cout << "c - Change User Password" << endl;
    cout << "f - Find User" << endl;
    cout << "p - Display Decoded Password" << endl;
    cout << "d - Dump HashTable" << endl;
    cout << "s - HashTable Size" << endl;
    cout << "w - Write to Password File" << endl;
    cout << "x - Exit program" << endl;
    cout << "\nEnter choice : ";
}

void useLoad(PassServer& ps) {
    string filename;
    
    cout << "Enter filename: ";
    cin >> filename;
    
    if (ps.load(filename.c_str())) {
        cout << "File loaded successfuly" << endl;
    } else {
        cout << "Error loading file" << endl;
    }
}

void useAddUser(PassServer& ps) {
    string user;
    string password;
    
    cout << "Enter username: ";
    cin >> user;
    
    cout << "Enter password: ";
    cin >> password;
    
    if (ps.addUser(make_pair(user, password))) {
        cout << "User added successfully" << endl;
    } else {
        cout << "Error adding user" << endl;
    }
}

void useRemoveUser(PassServer& ps) {
    string user;
    
    cout << "Enter username: ";
    cin >> user;
    
    if (ps.removeUser(user)) {
        cout << "User removed successfully" << endl;
    } else {
        cout << "Error removing user" << endl;
    }
}

void useChangePassword(PassServer& ps) {
    string user;
    cout << "Enter username: ";
    cin >> user;

    string oldPassword;
    cout << "Enter old password: ";
    cin >> oldPassword;
    
    string newPassword;
    cout << "Enter new password: ";
    cin >> newPassword;
    
    if (ps.changePassword(make_pair(user, oldPassword), newPassword)) {
        cout << "Password changed successfully" << endl;
    } else {
        cout << "Error changing password" << endl;
    }
}

void useFindUser(PassServer& ps) {
    string user;
    cout << "Enter username: ";
    cin >> user;
    
    if (ps.find(user)) {
        cout << "User found." << endl;
    } else {
        cout << "User not found." << endl;
    }
}

void useDisplayPassword(PassServer& ps) {
    string user;
    cout << "Enter username: ";
    cin >> user;
    
    string password = ps.decodepw(user);
    
    if (password == "NOT FOUND") {
        cout << "User not found" << endl;
    } else {
        cout << "Decoded password: " << password << endl;
    }
}

void useDumpHashTable(PassServer& ps) {
    ps.dump();
}

void useHashTableSize(PassServer& ps) {
    cout << "HashTable size: " << ps.size() << endl;
}

void useWriteToFile(PassServer& ps) {
    string filename;
    cout << "Enter filename: ";
    cin >> filename;
    
    if (ps.write_to_file(filename.c_str())) {
        cout << "File saved successfully" << endl;
    } else {
        cout << "Error writing to file" << endl;
    }
}
