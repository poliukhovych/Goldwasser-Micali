#include "goldwasser-micali.h"
#include <botan/auto_rng.h>
#include <botan/numthry.h>
#include <iostream>

using namespace Botan;
using namespace std;

bool is_quadratic_residue(const BigInt& a, const BigInt& p) {
    return power_mod(a, (p - 1) / 2, p) == 1;
}

pair<PublicKey, PrivateKey> generate_keys(size_t bits) {
    AutoSeeded_RNG rng;
    BigInt p = random_prime(rng, bits);
    BigInt q = random_prime(rng, bits);
    BigInt N = p * q;

    BigInt x;
    do {
        x = BigInt::random_integer(rng, 2, N - 1);
    } while (is_quadratic_residue(x, p) || is_quadratic_residue(x, q));

    return { {N, x}, {p, q} };
}

BigInt encrypt_bit(int bit, const PublicKey& pub, BigInt& used_r) {
    AutoSeeded_RNG rng;
    BigInt r;
    do {
        r = BigInt::random_integer(rng, 2, pub.N - 1);
    } while (gcd(r, pub.N) != 1);

    used_r = r;

    BigInt c = power_mod(r, 2, pub.N);
    if (bit == 1) {
        c = (c * pub.x) % pub.N;
    }
    return c;
}

int decrypt_bit(const BigInt& c, const PrivateKey& priv) {
    bool is_residue = is_quadratic_residue(c, priv.p) && is_quadratic_residue(c, priv.q);
    return is_residue ? 0 : 1;
}

vector<int> string_to_bits(const string& message) {
    vector<int> bits;
    for (char ch : message) {
        for (int i = 7; i >= 0; --i) {
            bits.push_back((ch >> i) & 1);
        }
    }
    return bits;
}

string bits_to_string(const vector<int>& bits) {
    string result;
    for (size_t i = 0; i < bits.size(); i += 8) {
        char ch = 0;
        for (int j = 0; j < 8 && i + j < bits.size(); ++j) {
            ch = (ch << 1) | bits[i + j];
        }
        result += ch;
    }
    return result;
}

void print_and_log(ofstream& log, const string& label, const string& content) {
    cout << label << content << "\n";
    log << label << content << "\n";
}

void print_big(ofstream& log, const string& label, const BigInt& val) {
    print_and_log(log, label, val.to_dec_string());
}
