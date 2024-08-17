#include <string_view>
#include <iostream>
#include <string>
#include <stdexcept>
#include <climits>
#include <sstream>
#include <bitset>

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
		friend class bitset;

	private:
		std::byte& byte;
		std::size_t bit_pos;


	public:

		reference(std::byte& byte_ref, std::size_t bit_pos) : byte(byte_ref), bit_pos(bit_pos) {}
		reference& operator=(bool value) {
			if (value) {
				byte |= (std::byte{ 1 } << bit_pos);
			}
			else {
				byte &= ~(std::byte{ 1 } << bit_pos);
			}
			return *this;
		}

		reference& operator=(const reference& other) {
			return *this = static_cast<bool>(other);
		}

		operator bool() const {
			return static_cast<bool>(byte & (std::byte{ 1 } << bit_pos));
		}

		reference& flip() {
			byte ^= (std::byte{ 1 } << bit_pos); // Toggle the bit
			return *this;
		}
	};


	constexpr bitSet() noexcept;
	constexpr bitSet(unsigned long val) noexcept;
	explicit bitSet(const std::string& str);

	bitSet(const bitSet<N>& other);
	bitSet(bitSet<N>&& other) noexcept;

	bitSet<N>& operator=(const bitSet<N>& other);
	bitSet<N>& operator=(bitSet<N>&& other) noexcept;

	bool operator[](std::size_t pos) const;
	reference operator[](std::size_t pos) {
		return reference(data[pos / BITS_PER_BYTE], pos % BITS_PER_BYTE);
	}

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

#endif //  BBITSET_H