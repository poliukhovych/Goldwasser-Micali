#include "goldwasser-micali.h"
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream messageFile("message.txt");
    if (!messageFile.is_open()) {
        cerr << "Error: Cannot open message.txt\n";
        return 1;
    }

    string message((istreambuf_iterator<char>(messageFile)), istreambuf_iterator<char>());
    messageFile.close();

    ofstream log("log.txt");
    if (!log.is_open()) {
        cerr << "Error: Cannot open log.txt for writing\n";
        return 1;
    }

    print_and_log(log, "\nGoldwasser-Micali Cryptosystem Simulation", 
                        "\n-----------------------------------------\n");

    auto [publicKey, privateKey] = generate_keys();
    print_and_log(log, "\n[Alice] Key Generation\n", "");
    print_big(log, "  Public key N: ", publicKey.N);
    print_big(log, "  Public key x: ", publicKey.x);
    print_big(log, "  Private key p: ", privateKey.p);
    print_big(log, "  Private key q: ", privateKey.q);

    vector<int> bits = string_to_bits(message);
    vector<Botan::BigInt> ciphertext;

    print_and_log(log, "\n[Bob] Encryption\n", "");
    print_and_log(log, "Original message: ", message);
    for (size_t i = 0; i < bits.size(); ++i) {
        int b = bits[i];
        Botan::BigInt r;
        Botan::BigInt c = encrypt_bit(b, publicKey, r);

        print_and_log(log, "  Bit #" + to_string(i + 1) + ": ", to_string(b));
        print_big(log, "    Random r: ", r);
        print_big(log, "    Ciphertext: ", c);
        ciphertext.push_back(c);
    }

    print_and_log(log, "\n[Alice] Decryption\n", "");
    vector<int> decrypted_bits;
    for (size_t i = 0; i < ciphertext.size(); ++i) {
        int b = decrypt_bit(ciphertext[i], privateKey);
        decrypted_bits.push_back(b);
        print_and_log(log, "  Ciphertext bit #" + to_string(i + 1) + ": ", ciphertext[i].to_dec_string());
        print_and_log(log, "    Decrypted bit: ", to_string(b));
    }

    string decrypted_message = bits_to_string(decrypted_bits);
    print_and_log(log, "\n[Alice] Decrypted message: ", decrypted_message);
    log.close();

    return 0;
}
