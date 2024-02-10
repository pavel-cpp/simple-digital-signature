// TEMP TEST DATA
#include <iostream>
#include <vector>
#include <hash-calculator/hash_calculator.h>
#include <io-tools/io_tools.h>
#include <bitset>

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

int main(int argc, char* argv[]) {
    HashCalculator hasher;
    string s;
    cin >> s;
    uint32_t private_key = static_cast<uint32_t>(hasher.Calculate(vector<char>(s.begin(), s.end())) >> 32);
    srand(private_key);
    uint64_t hash = hasher.Calculate(ReadContents("test_file"));
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
