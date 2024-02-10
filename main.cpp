// Stdlib
#include <filesystem>
#include <fstream>
#include <iostream>

// Project libs
#include <doc-signer/doc_signer.h>
#include <hash-calculator/hash_calculator.h>
#include <io-tools/io_tools.h>
#include <key-sing-manager/key_sign_manager.h>
#include <keygen/keygen.h>

using namespace std;

namespace fs = filesystem;

bool IsValidDocument(const fs::path &path) {
    return fs::is_regular_file(path) && fs::exists(path) && fs::file_size(path) > 0;
}

bool IsReadable(const fs::path &path) {
    ifstream file(path);
    return file.is_open();
}

bool ConfirmAction(const string &prompt) {
    cout << prompt << " (Y/n): "s;
    char choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return tolower(choice) == 'y';
}

void SignDocument(const fs::path &document_path, KeySignManager &key_manager) {
    string name;
    cout << "Enter your name: "s;
    getline(cin, name);

    HashCalculator hasher;
    auto key_sign = KeyGen::GenerateSign(
            KeyGen::GeneratePrivateKey(name),
            hasher.Calculate(ReadContents(document_path))
    );

    DocSigner::Sign(document_path, key_sign.second);
    key_manager.AddData(key_sign.first, key_sign.second);
}

void ProcessDocument(const fs::path &document_path, KeySignManager &key_manager) {
    if (DocSigner::HasSign(document_path)) {
        fs::path sign_path = document_path;
        sign_path = sign_path.replace_extension(".sign"s);
        if (DocSigner::ValidSign(document_path, sign_path)) {
            cout << "Document has valid signature"s << endl;
        } else {
            cout << "Document has invalid signature"s << endl;
        }
        if (ConfirmAction("Delete this"s)) {
            DocSigner::UnSign(sign_path);
        }
    } else {
        if (ConfirmAction("Sign this"s)) {
            SignDocument(document_path, key_manager);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc > 2) {
        cerr << "Too many arguments"s << endl;
        return 1;
    }

    fs::path document_path;
    if (argc == 2) {
        document_path = argv[1];
    } else {
        cout << "Enter the path to the document: "s;
        string tmp;
        getline(cin, tmp);
        document_path = tmp;
    }

    if (!IsValidDocument(document_path) || !IsReadable(document_path)) {
        cerr << "Invalid path or unreadable document"s << endl;
        return 1;
    }

    KeySignManager key_manager("repo"s);
    ProcessDocument(document_path, key_manager);

    return 0;
}
