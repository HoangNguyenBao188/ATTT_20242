#include <iostream>
#include <string>

using namespace std;

void KSA(unsigned char S[256], string& key) {
    for (int i = 0; i < 256; ++i) S[i] = i;
    int j = 0;
    for (int i = 0; i < 256; ++i) {
        j = (j + S[i] + key[i % key.length()]) % 256;
        swap(S[i], S[j]);
    }
}

string RC4(string& key, string& data) {
    unsigned char S[256];
    KSA(S, key);

    int i = 0, j = 0;
    string output = data;

    for (size_t k = 0; k < data.size(); ++k) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(S[i], S[j]);
        output[k] = data[k] ^ S[(S[i] + S[j]) % 256];
    }
    return output;
}

void printHex(string& data) {
    for (unsigned char c : data) printf("%02X ", c);
    cout << endl;
}

int main() {
    string key = "helloworld";
    string plaintext = "Hanoi University of Science and Technology";

    string ciphertext = RC4(key, plaintext);

    cout << "Ciphertext: ";
    printHex(ciphertext);

    return 0;
}
