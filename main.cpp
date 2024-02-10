// TEMP TEST DATA
#include <iostream>
#include <vector>
#include <hash-calculator/hash_calculator.h>
#include <io-tools/io_tools.h>
#include <key-sing-manager/key_sign_manager.h>

using namespace std;

int main(int argc, char* argv[]) {
    KeySignManager repo("repo2");
    HashCalculator hasher;
    string s;
    cin >> s;
    uint32_t private_key = static_cast<uint32_t>(hasher.Calculate(vector<char>(s.begin(), s.end())) >> 32);
    srand(private_key);
    uint64_t hash = hasher.Calculate(ReadContents("test_file"));
    cout << hash << endl;
    vector<int64_t> sign;
    {
        string hash_s = to_string(hash);
        sign.assign(hash_s.begin(), hash_s.end());
    }
    vector<int64_t> open;
    cout << "signature: ";
    for(int64_t& c: sign){
        int64_t num = (static_cast<int64_t>(rand()) + static_cast<int64_t>(rand())) - (static_cast<int64_t>(rand()) + static_cast<int64_t>(rand()));
        c += num;
        open.push_back(-num);
        cout << c << " ";
    }
    cout << endl << endl;
    repo.AddData(open, sign);
    cout << "open key: " << open << endl << endl;
    open = repo.GetKey(sign);
    cout << "open key: " << open << endl << endl;
    try{
        repo.RemoveData(open);
    }catch (exception& e){
        cout << e.what() << endl;
    }

    return 0;
}
