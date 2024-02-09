#include <iostream>
#include <vector>
#include <file_hasher.h>

using namespace std;

template<typename T>
ostream& operator<<(ostream& os, vector<T> data){
    bool first = true;
    for(const T& item: data){
        if(first){
            os << item;
            first = false;
            continue;
        }
        os << " " << item;
    }
    return os;
}

int main() {
    FileHasher hasher;
    int private_key = 12;
    srand(private_key);
    uint64_t hash = FileHasher::Hash("test_file");
    cout << hash << endl;
    string hash_s = to_string(hash);
    vector<int> open;
    cout << "signature: ";
    for(char& c: hash_s){
        int num = rand() % 255 - 127;
        c += num;
        open.push_back(-num);
        cout << static_cast<int>(c) << " ";
    }
    cout << endl << endl;
    cout << "open key: " << open << endl << endl;
    return 0;
}
