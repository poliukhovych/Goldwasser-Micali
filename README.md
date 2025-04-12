# Goldwasser-Micali Cryptosystem Simulator

This project is a C++ simulation of the **Goldwasser-Micali cryptosystem**, using the [Botan](https://botan.randombit.net/) cryptographic library.

It demonstrates:
- Key generation (Alice)
- Bit-wise encryption (Bob)
- Bit-wise decryption (Alice)
- Conversion of strings to/from bits
- Logging the entire process to `log.txt`
- Reading the plaintext message from `message.txt`

## Requirements

- C++20 compiler (e.g. `g++`)
- [Botan](https://botan.randombit.net/) library (v3.x)

## Build
To build with a custom Botan installation
```bash
make BOTAN_PREFIX=/your/custom/path
