#include <string_view>
#include <iostream>
#include <string>
#include <stdexcept>
#include <climits>
#include <sstream>
#include <bitset>
#include <cstddef>

#ifndef BBITSET_H
#define BBITSET_H

template<std::size_t N>
class bitSet {
private:
	static constexpr std::size_t BITS_PER_BYTE = 8;
	static constexpr std::size_t NUM_BYTES = (N + BITS_PER_BYTE - 1) / BITS_PER_BYTE;

	std::byte data[NUM_BYTES] = {};

	void validatePosition(std::size_t pos) const;
public:
	class reference {
		friend class bitSet;

	private:
		std::byte& byte;
		std::size_t bit_pos;

		reference(std::byte& byte_ref, std::size_t bit_pos);

	public:
		reference& operator=(bool value);
		reference& operator=(const reference& other);

		operator bool() const;
		reference& flip();
	};


	bitSet();
	explicit bitSet(unsigned long val);
	explicit bitSet(const std::string& str);

	bitSet(const bitSet<N>& other);
	bitSet(bitSet<N>&& other) noexcept;

	bitSet<N>& operator=(const bitSet<N>& other);
	bitSet<N>& operator=(bitSet<N>&& other) noexcept;

	bool operator[](std::size_t pos) const;
	reference operator[](std::size_t pos);

	bool operator==(const bitSet& rhs) const;
	bool operator!=(const bitSet& rhs) const;

	bitSet& operator&=(const bitSet<N>& other);
	bitSet& operator|=(const bitSet<N>& other);
	bitSet& operator^=(const bitSet<N>& other);
	bitSet operator~() const;

	bitSet operator<<(std::size_t pos) const;
	bitSet& operator<<=(std::size_t pos);
	bitSet operator>>(std::size_t pos) const;
	bitSet& operator>>=(std::size_t pos);

	std::size_t size() const;

	unsigned long to_ulong() const;
	unsigned long long to_ullong() const;

	std::string to_string();
};

#include "bitset.ipp"

#endif //  BBITSET_H