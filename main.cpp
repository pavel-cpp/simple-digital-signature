// TEMP TEST DATA
#include <iostream>
#include <vector>
#include <keygen/keygen.h>
#include <hash-calculator/hash_calculator.h>
#include <key-sing-manager/key_sign_manager.h>
#include <doc-signer/doc_signer.h>
#include <io-tools/io_tools.h>
#include <filesystem>
#include <fstream>

using namespace std;

bool IsReadable(const filesystem::path &path) {
    std::ifstream file(path);
    return file.is_open();
}

int main(int argc, char *argv[]) {
    if (argc > 2) {
        cerr << "Too much arguments"s << endl;
        return 1;
    }

    filesystem::path document_path;

    if (argc == 2) {
        document_path = argv[1];
    } else {
        cout << "Enter the path to document"s << endl << "> "s;
        string tmp;
        getline(cin, tmp);
        document_path = tmp;
    }

    if (!filesystem::is_regular_file(document_path) || !IsReadable(document_path)) {
        cerr << "Invalid path or document is not readable"s << endl;
        return 1;
    }

    KeySignManager key_manager("repo");

    if (DocSigner::HasSign(document_path)) {

        filesystem::path sign_path = document_path.parent_path() / (document_path.filename().stem().string() + ".sign");

        if (DocSigner::ValidSign(document_path, sign_path)) {
            cout << "Document has valid sign"s << endl;
        } else {
            cout << "Document has invalid sign"s << endl;
        }

        cout << "Delete this? (Y/n): ";
        char choice;
        cin >> choice;
        cin.ignore();
        if (tolower(choice) == 'y') {
            DocSigner::UnSign(sign_path);
        }
    } else {
        cout << "Sign this? (Y/n): ";
        char choice;
        cin >> choice;
        cin.ignore();
        if (tolower(choice) == 'y') {
            string name;
            cout << "Enter your name: ";
            getline(cin, name);
            HashCalculator hasher;
            auto key_sign = KeyGen::GenerateSign(
                    KeyGen::GeneratePrivateKey(name),
                    hasher.Calculate(ReadContents(document_path))
            );
            DocSigner::Sign(document_path, key_sign.second);
            key_manager.AddData(key_sign.first, key_sign.second);
        }
    }

    return 0;
}
