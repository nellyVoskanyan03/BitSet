#include <iostream>
#include "../include/bitset.h"
#include <vector>

template <std::size_t N>
void findUniqueCombinations(const std::vector<bitSet<N>>& numbers, const bitSet<N>& target) {
    int n = numbers.size();
    int numOfCombinations = 1 << n;

    std::cout << "Unique combinations that XOR to " << target << ":" << std::endl;

    for (int num = 0; num < numOfCombinations; ++num) {
        bitSet<N> result(0);
        bitSet<N> mask(num);
        std::vector<bitSet<N>> combination;

        for (int i = 0; i < n; ++i) {
            if (mask[i]) {
                result ^= numbers[i]; 
                combination.push_back(numbers[i]);
            }
        }

        if (result == target) {
            std::cout << "{";
            for (int i = 0; i < combination.size(); ++i) {
                std::cout << combination[i] << " (" << combination[i].to_ulong() << ") ";
            }
            std::cout << "}" << std::endl;
        }
    }
}

template <std::size_t N>
void getBinaryNumbers(std::vector<bitSet<N>>& arr) {
    int n;
    std::cout << "Enter the number of binary numbers: ";
    std::cin >> n;

    for (int i = 0; i < n; i++)
    {
        bitSet<N> tmp;
        std::cout << "Enter the binary number "<< i << ": ";
        std::cin >> tmp;
        arr.push_back(tmp);
    }

}

int main() {
    std::cout << "The Problem \nGiven a list of binary numbers, find all unique combinations of these \nnumbers that result in a specific binary number when XORed together." 
        << std::endl;
    std::vector<bitSet<8>> numbers;
    getBinaryNumbers(numbers);


    bitSet<8> target;
    std::cout << "Enter the binary target: ";
    std::cin >> target;

    findUniqueCombinations(numbers, target);

    return 0;
}