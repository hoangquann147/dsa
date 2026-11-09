// LAB 3 - HASH TABLE LOGIN AUTHENTICATION
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// 1. Store colliding usernames in the same bucket.
struct User { string username, password; };
const int SIZE = 100003;
vector<vector<User>> table(SIZE);

int hashKey(const string& username) {
    int key = 0;
    for (unsigned char c : username) key = (key * 31 + c) % SIZE;
    return key;
}

void insertUser(const string& username, const string& password) {
    int key = hashKey(username);
    for (User& user : table[key]) {
        if (user.username == username) {
            user.password = password; // Update duplicate usernames.
            return;
        }
    }
    table[key].push_back({username, password});
}

// 2. Load up to one million account records.
bool loadUsers(const string& filename) {
    ifstream file(filename);
    if (!file) return false;
    string username, password;
    int count = 0;
    while (file >> username) {
        if (!(file >> password) || ++count > 1000000) return false;
        insertUser(username, password);
    }
    return !file.bad();
}

bool authenticate(const string& username, const string& password) {
    for (const User& user : table[hashKey(username)])
        if (user.username == username) return user.password == password;
    return false;
}

// 3. Repeat login until EOF.
int main(int argc, char* argv[]) {
    if (!loadUsers(argc > 1 ? argv[1] : "user.txt")) {
        cerr << "Error: cannot load user file\n";
        return 1;
    }
    string username, password;
    while (true) {
        cout << "Username: ";
        if (!(cin >> username)) break;
        cout << "Password: ";
        if (!(cin >> password)) break;
        cout << (authenticate(username, password)
                 ? "Authentication successful" : "Authentication failure") << '\n';
    }
    return 0;
}
