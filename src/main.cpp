#include <iostream>
#include <vector>
#include "../include/bitset.h"

template <std::size_t N>
std::vector<bitSet<N>> getCombination(const std::vector<bitSet<N>>& numbers, int num) {
    std::vector<bitSet<N>> combination;
    bitSet<N> mask(num);

    for (int i = 0; i < N; ++i) {
        if (mask[i]) {
            combination.push_back(numbers[i]);
        }
    }
    return combination;
}

template <std::size_t N>
void printCombination(std::vector<bitSet<N>>& combination) {
    std::cout << "{";
    for (int i = 0; i < combination.size(); ++i) {
        std::cout << combination[i] << " (" << combination[i].to_ulong() << ") ";
    }
    std::cout << "}" << std::endl;
}

template <std::size_t N>
bitSet<N> XORCombinationItems(std::vector<bitSet<N>>& combination) {
    bitSet<N> result(0);
    for (auto& item : combination) {
        result ^= item;
    }
    return result;
}

template <std::size_t N>
std::vector<std::vector<bitSet<N>>> findUniqueCombinations(const std::vector<bitSet<N>>& numbers, const bitSet<N>& target) {
    std::vector<std::vector<bitSet<N>>> uniqueCombinations;

    int numOfAllCombinations = 1 << numbers.size();
    for (int num = 0; num < numOfAllCombinations; ++num) {
        auto combination = getCombination(numbers, num);
        auto result = XORCombinationItems(combination);

        if (result == target) {
            uniqueCombinations.push_back(combination);
        }
    }
    return uniqueCombinations;
}

template <std::size_t N>
std::vector<bitSet<N>> getBinaryNumbers() {
    int n;
    std::cout << "Enter the number of binary numbers: ";
    std::cin >> n;

    std::vector<bitSet<N>> arr;
    for (int i = 0; i < n; i++)
    {
        bitSet<N> tmp;
        std::cout << "Enter the binary number "<< i << ": ";
        std::cin >> tmp;
        arr.push_back(tmp);
    }
    return arr;
}

template <std::size_t N>
bitSet<N> getTarget() {
    bitSet<8> target;
    std::cout << "Enter the binary target: ";
    std::cin >> target;
    return target;

}

template <std::size_t N>
void findAndPrintUniqueCombinations(const std::vector<bitSet<N>>& numbers, const bitSet<N>& target) {
    std::cout << "Unique combinations that XOR to " << target << ":" << std::endl;
    auto result = findUniqueCombinations(numbers, target);
    for (auto& combination : result) {
        printCombination(combination);
    }
}

void runTheProblem() {
    std::cout <<
        "The Problem \n \
        Given a list of binary numbers, find all unique combinations of these \n \
        numbers that result in a specific binary number when XORed together."
        << std::endl;

    auto numbers = getBinaryNumbers<8>();
    auto target = getTarget<8>();
    findAndPrintUniqueCombinations(numbers, target);
}

int main() {

    runTheProblem();

    return 0;
}