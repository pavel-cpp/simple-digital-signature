// TEMP TEST DATA
#include <iostream>
#include <vector>
#include <hash-calculator/hash_calculator.h>
#include <io-tools/io_tools.h>
#include <key-sing-manager/key_sign_manager.h>
#include <doc-signer/doc_signer.h>
#include <filesystem>
#include <fstream>

using namespace std;

bool IsReadable(const filesystem::path& path) {
    std::ifstream file(path);
    return file.is_open();
}

int main(int argc, char* argv[]) {
    if(argc > 2){
        cerr << "Too much arguments" << endl;
        return 1;
    }

    filesystem::path document_path;

    if(argc == 2){
        document_path = argv[1];
    }else{
        cout << "Enter the path to document"s << endl << "> "s;
        string tmp;
        getline(cin, tmp);
        document_path = tmp;
    }

    if(!filesystem::is_regular_file(argv[1]) || !IsReadable(argv[1])){
        cerr << "Invalid path or document is not readable" << endl;
        return 1;
    }

    return 0;
}
