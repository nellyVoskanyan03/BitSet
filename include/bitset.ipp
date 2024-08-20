#include <iostream>
#include <string>
#include <stdexcept>
#include <climits>
#include <sstream>
#include <cstddef>

// Binary operators
template <std::size_t N>
bitSet<N> operator&(bitSet<N> lhs, const bitSet<N>& rhs) {
	lhs &= rhs;
	return lhs;
}

template <std::size_t N>
bitSet<N> operator|(bitSet<N> lhs, const bitSet<N>& rhs) {
	lhs |= rhs;
	return lhs;
}

template <std::size_t N>
bitSet<N> operator^(bitSet<N> lhs, const bitSet<N>& rhs) {
	lhs ^= rhs;
	return lhs;
}

template <std::size_t N>
bitSet<N> operator<<(bitSet<N> lhs, std::size_t shift) {
	lhs <<= shift;
	return lhs;
}

template <std::size_t N>
bitSet<N> operator>>(bitSet<N> lhs, std::size_t shift) {
	lhs >>= shift;
	return lhs;
}

// Constructors
template<std::size_t N>
bitSet<N>::bitSet()  {
	for (int i = 0; i < NUM_BYTES; ++i) {
		data[i] = std::byte{ 0 };
	}
}

template<std::size_t N>
 bitSet<N>::bitSet(unsigned long val)  {
	for (int i = 0; i < NUM_BYTES; ++i) {
		data[i] = std::byte{ static_cast<unsigned char>(val & 0xFF) };
		val >>= BITS_PER_BYTE;
	}
}

template<std::size_t N>
bitSet<N>::bitSet(const std::string& str) {
	if (str.length() > N) {
		throw std::invalid_argument("String length exceeds bitset size");
	}

	for (int i = 0; i < str.length(); ++i) {
		if (str[str.length() - 1 - i] == '1') {
			reference(data[i / BITS_PER_BYTE], i % BITS_PER_BYTE) = true;
		}
		else if (str[str.length() - 1 - i] != '0') {
			throw std::invalid_argument("Invalid character in string");
		}
	}
}

template<std::size_t N>
bitSet<N>::bitSet(const bitSet<N>& other) {
	std::copy(other.data, other.data + NUM_BYTES, this->data);
}

template<std::size_t N>
bitSet<N>::bitSet(bitSet<N>&& other) noexcept {
	if (this != &other) {
		std::move(std::begin(other.data), std::end(other.data), std::begin(data));
		for (int i = 0; i < NUM_BYTES; ++i) {
			other.data[i] = std::byte{ 0 };
		}
	}
}

// Private member function
template<std::size_t N>
void bitSet<N>::validatePosition(std::size_t pos) const {
	if (pos >= N) {
		throw std::out_of_range("Bit position out of range");
	}
}

// Assignement operators
template<std::size_t N>
bitSet<N>& bitSet<N>::operator=(const bitSet<N>& other) {
	std::copy(other.data, other.data + NUM_BYTES, this->data);
	return *this;
}

template<std::size_t N>
bitSet<N>& bitSet<N>::operator=(bitSet<N>&& other) noexcept {
	if (this != &other) {
		std::move(std::begin(other.data), std::end(other.data), std::begin(data));
		for (int i = 0; i < NUM_BYTES; ++i) {
			other.data[i] = std::byte{ 0 };
		}
	}
	return *this;
}

// Public member function
template<std::size_t N>
std::size_t bitSet<N>::size() const {
	return N;
}

// Indexing operator
template<std::size_t N>
bool bitSet<N>::operator[](std::size_t pos) const {
	return static_cast<bool>(data[pos / BITS_PER_BYTE] & (std::byte{ 1 } << (pos % BITS_PER_BYTE)));
}

template<std::size_t N>
bitSet<N>::reference bitSet<N>::operator[](std::size_t pos) {
	return reference(data[pos / BITS_PER_BYTE], pos % BITS_PER_BYTE);
}
// Comparing operators
template<std::size_t N>
bool bitSet<N>::operator==(const bitSet& rhs) const {
	if (N != rhs.size())
	{
		return false;
	}
	for (int i = 0; i < NUM_BYTES; ++i) {
		if (data[i] != rhs.data[i])
		{
			return false;
		}
	}
	return true;
}

template<std::size_t N>
bool bitSet<N>::operator!=(const bitSet& rhs) const {
	if (N != rhs.size())
	{
		return true;
	}
	for (int i = 0; i < NUM_BYTES; ++i) {
		if (data[i] != rhs.data[i])
		{
			return true;
		}
	}
	return false;
}

// binary assignment operators
template<std::size_t N>
bitSet<N>& bitSet<N>::operator&=(const bitSet<N>& other) {
	for (int i = 0; i < NUM_BYTES; ++i) {
		data[i] &= other.data[i];
	}
	return *this;
}

template<std::size_t N>
bitSet<N>& bitSet<N>::operator|=(const bitSet<N>& other) {
	for (int i = 0; i < NUM_BYTES; ++i) {
		data[i] |= other.data[i];
	}
	return *this;
}

template<std::size_t N>
bitSet<N>& bitSet<N>::operator^=(const bitSet<N>& other) {
	for (int i = 0; i < NUM_BYTES; ++i) {
		data[i] ^= other.data[i];
	}
	return *this;
}

//binary operators (with numbers)
template<std::size_t N>
bitSet<N> bitSet<N>::operator~() const {
	bitSet<N> result;
	for (int i = 0; i < NUM_BYTES; ++i) {
		result.data[i] = ~data[i];
	}
	return result;
}

template<std::size_t N>
bitSet<N> bitSet<N>::operator<<(std::size_t pos) const {
	bitSet<N> result(0);
	int byte_pos = pos / BITS_PER_BYTE;
	int bit_pos = pos % BITS_PER_BYTE;

	int j = 0;
	result.data[byte_pos] = data[j] << bit_pos;
	++j;
	for (int i = byte_pos + 1; i < NUM_BYTES; ++i)
	{
		result.data[i] = (((data[j] << bit_pos)) | (data[j - 1] >> (BITS_PER_BYTE - bit_pos)));
		j++;
	}
	return result;
}

template<std::size_t N>
bitSet<N>& bitSet<N>::operator<<=(std::size_t pos) {
	*this = *this << pos;
	return *this;

}

template<std::size_t N>
bitSet<N> bitSet<N>::operator>>(std::size_t pos) const {
	pos = N - pos;
	bitSet<N> result(0);
	int byte_pos = pos / BITS_PER_BYTE;
	int bit_pos = pos % BITS_PER_BYTE;

	int j = NUM_BYTES - 1;
	result.data[byte_pos] = data[j] >> (BITS_PER_BYTE - bit_pos);
	--j;
	for (int i = byte_pos - 1; i >= 0; --i) {
		result.data[i] = (data[j] >> (BITS_PER_BYTE - bit_pos)) | (data[j + 1] << bit_pos);
		--j;
	}
	return result;
}

template<std::size_t N>
bitSet<N>& bitSet<N>::operator>>=(std::size_t pos) {
	*this = *this >> pos;
	return *this;
}

// Convert
template<std::size_t N>
unsigned long bitSet<N>::to_ulong() const {
	if (N > sizeof(unsigned long) * 8)
	{
		throw std::overflow_error("bitset size exceeds the size of unsigned long");
	}
	unsigned long result = 0;
	for (int i = NUM_BYTES - 1; i >= 0; --i) {

		result |= std::to_integer<int>(data[i]);
		if (i != 0)
		{
			result <<= BITS_PER_BYTE;
		}
	}

	return result;
}

template<std::size_t N>
unsigned long long bitSet<N>::to_ullong() const {
	if (N > sizeof(unsigned long long) * 8)
	{
		throw std::overflow_error("bitset size exceeds the size of unsigned long");
	}
	unsigned long long result = 0;
	for (int i = NUM_BYTES - 1; i >= 0; --i) {

		result |= std::to_integer<int>(data[i]);
		if (i != 0)
		{
			result <<= BITS_PER_BYTE;
		}
	}

	return result;
}

template<size_t N>
std::string bitSet<N>::to_string() {
	std::string result(N, '0');
	for (std::size_t i = 0; i < N; ++i) {

		bool val = static_cast<bool>(data[i / BITS_PER_BYTE] & (std::byte{ 1 } << (i % BITS_PER_BYTE)));
		if (val)
		{
			result[N - i - 1] = '1';
		}
	}
	return result;
}

// Stream input and output operators
template<std::size_t N>
std::ostream& operator<<(std::ostream& os, const bitSet<N>& bs) {
	for (std::size_t i = N; i > 0; --i) {
		os << static_cast<bool>(bs[(i - 1)]);
	}
	return os;
}

template<std::size_t N>
std::istream& operator>>(std::istream& is, bitSet<N>& bs) {
	std::string input;
	is >> input;

	
	bs = bitSet<N>(input);

	return is;
}

// Reference
template<std::size_t N>
bitSet<N>::reference::reference(std::byte& byte_ref, std::size_t bit_pos) : byte(byte_ref), bit_pos(bit_pos) {}

template<std::size_t N>
typename bitSet<N>::reference& bitSet<N>::reference::operator=(bool value) {
	if (value) {
		byte |= (std::byte{ 1 } << bit_pos);
	}
	else {
		byte &= ~(std::byte{ 1 } << bit_pos);
	}
	return *this;
}

template<std::size_t N>
typename bitSet<N>::reference& bitSet<N>::reference::operator=(const reference& other) {
	return *this = static_cast<bool>(other);
}

template<std::size_t N>
bitSet<N>::reference::operator bool() const {
	return static_cast<bool>(byte & (std::byte{ 1 } << bit_pos));
}

template<std::size_t N>
typename bitSet<N>::reference& bitSet<N>::reference::flip() {
	byte ^= (std::byte{ 1 } << bit_pos);
	return *this;
}