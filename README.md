# BitSet Implementation
This repository contains a custom implementation of a bitset class template in C++. The bitset class is designed to store bits efficiently using `std::byte`, providing functionalities similar to `std::bitset`. The class is templated to support different sizes and includes a variety of operations for manipulating and querying bits. Unit tests are implemented using the Google Test (gtest) framework.

## Installation and Setup
### Cloning the Repository
Use the following command to clone the repository and initialize its submodules (googleTest):
```sh
git clone --recurse-submodules https://github.com/nellyVoskanyan03/BitSet.git
```
### Pulling submodules
Use the following command to pull commits that include submodules (googleTest):
```sh
git pull --rebase --recurse-submodules
```
### Building
This is a **CMake** project. To build the project, run the following commands:

 ```sh
cmake -S . -B build
cmake --build build
```
After building, two executables will be available:
- `./build/tests` : Runs the tests.
- `./build/main` : Runs main.cpp.
  
## Features
 - Default Construction
 - Copy and Move Construction
 - Copy and Move Assignment
 - Constructors from integers and strings
 - Bitwise shift operators (`<<`, `>>`)
 - Bitwise logical operators (`&`, `|`, `^`, `~`)
 - Stream input/output operators
 - Conversion functions to `std::string` and `integer` types
## Class Interface
### `bitset<N>`
A template class that stores `N` bits efficiently.

### Constructors
 - `bitset()`: Default constructor.
 - `bitset(unsigned long val)`: Initialize with an unsigned long value.
 - `bitset(const std::string& str)`: Initialize from a string.

### Operators
 - `bool operator[](size_t pos) const`: Access bit at position pos.
 - `reference operator[](size_t pos)`: Access bit at position pos with a reference for modification.
 - `bitset& operator&=(const bitset& other)`: Bitwise AND assignment.
 - `bitset& operator|=(const bitset& other)`: Bitwise OR assignment.
 - `bitset& operator^=(const bitset& other)`: Bitwise XOR assignment.
 - `bitset operator~() const`: Bitwise NOT.
 - `bitset operator<<(size_t pos) const`: Left shift operator.
 - `bitset& operator<<=(size_t pos)`: Left shift assignment operator.
 - `bitset operator>>(size_t pos) const`: Right shift operator.
 - `bitset& operator>>=(size_t pos)`: Right shift assignment operator.

### Binary operators
 - `bitSet<N> operator&(bitSet<N> lhs, const bitSet<N>& rhs)`
 - `bitSet<N> operator|(bitSet<N> lhs, const bitSet<N>& rhs)`
 - `bitSet<N> operator^(bitSet<N> lhs, const bitSet<N>& rhs)`
 - `bitSet<N> operator<<(bitSet<N> lhs, std::size_t shift)`
 - `bitSet<N> operator>>(bitSet<N> lhs, std::size_t shift)`
### Conversion Functions
 - `unsigned long to_ulong() const`: Convert to an unsigned long.
 - `unsigned long long to_ullong() const`: Convert to an unsigned long long.
 - `std::string to_string(char zero = '0', char one = '1') const`: Convert to a string representation.
