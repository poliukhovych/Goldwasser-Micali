#pragma once

#include <botan/bigint.h>
#include <vector>
#include <string>
#include <fstream>

struct PublicKey {
    Botan::BigInt N;
    Botan::BigInt x;
};

struct PrivateKey {
    Botan::BigInt p, q;
};

bool is_quadratic_residue(const Botan::BigInt& a, const Botan::BigInt& p);

std::pair<PublicKey, PrivateKey> generate_keys(size_t bits = 128);

Botan::BigInt encrypt_bit(int bit, const PublicKey& pub, Botan::BigInt& used_r);

int decrypt_bit(const Botan::BigInt& c, const PrivateKey& priv);

std::vector<int> string_to_bits(const std::string& message);

std::string bits_to_string(const std::vector<int>& bits);

void print_and_log(std::ofstream& log, const std::string& label, const std::string& content);

void print_big(std::ofstream& log, const std::string& label, const Botan::BigInt& val);
