#include <gtest/gtest.h>
#include "../include/bitset.h"

// constructionTest
TEST(constructionTest, default_constructor) {
    bitSet<10> b;
    for (size_t i = 0; i < 10; ++i) {
        EXPECT_FALSE(b[i]);
    }
}

TEST(constructionTest, ulong_constructor) {
    bitSet<32> b(0b10101010);
    EXPECT_TRUE(b[1]);
    EXPECT_FALSE(b[0]);
    EXPECT_TRUE(b[3]);
    EXPECT_FALSE(b[2]);
}

TEST(constructionTest, string_constructor) {
    std::string bit_string = "101010";
    bitSet<6> b(bit_string);
    EXPECT_TRUE(b[1]);
    EXPECT_FALSE(b[0]);
    EXPECT_FALSE(b[2]);
}

TEST(constructionTest, copy_constructor) {
    bitSet<8> original(0b10101010); 
    bitSet<8> copy(original); 

    EXPECT_EQ(original.to_string(), copy.to_string());
}

TEST(constructionTest, move_constructor) {
    bitSet<8> original(0b11001100);
    bitSet<8> moved(std::move(original));

    EXPECT_EQ(moved.to_string(), "11001100");
    EXPECT_EQ(original.to_string(), "00000000");
}

// convertTest
TEST(convertTest, to_string) {
    bitSet<8> b(0b10101010);
    EXPECT_EQ(b.to_string(), "10101010");
}

TEST(convertTest, to_ulong) {
    bitSet<32> b(0b10101010);
    EXPECT_EQ(b.to_ulong(), 0b10101010);
}

TEST(convertTest, to_ullong) {
    bitSet<64> b(0b1010101010101010);
    EXPECT_EQ(b.to_ullong(), 0b1010101010101010);
}

// operationTest
TEST(operationTest, copy_assignement_operator) {
    bitSet<8> b1(0b10101010);

    bitSet<8> b2;

    b2 = b1;

    EXPECT_EQ(b1.to_string(), b2.to_string());
    b1[2] = true;
    EXPECT_NE(b1.to_string(), b2.to_string());
}

TEST(operationTest, move_assignement_operator) {
    bitSet<8> b1(0b11001100);

    bitSet<8> b2;
    b2 = std::move(b1);

    EXPECT_EQ(b2.to_string(), "11001100");
    EXPECT_EQ(b1.to_string(), "00000000");
}

TEST(operationTest, operation_and) {
    bitSet<8> b1(0b11001100);
    bitSet<8> b2(0b10101010);
    bitSet<8> result = b1 & b2;
    EXPECT_EQ(result.to_string(), "10001000");
}

TEST(operationTest, operation_or) {
    bitSet<8> b1(0b11001100);
    bitSet<8> b2(0b10101010);
    bitSet<8> result = b1 | b2;
    EXPECT_EQ(result.to_string(), "11101110");
}

TEST(operationTest, operation_xor) {
    bitSet<8> b1(0b11001100);
    bitSet<8> b2(0b10101010);
    bitSet<8> result = b1 ^ b2;
    EXPECT_EQ(result.to_string(), "01100110");
}

TEST(operationTest, operation_not) {
    bitSet<8> b(0b10101010);
    bitSet<8> result = ~b;
    EXPECT_EQ(result.to_string(), "01010101");
}

TEST(operationTest, operation_shift_left) {
    bitSet<8> b(0b00001111); 
    bitSet<8> result = b << 2; 

    EXPECT_EQ(result.to_string(), "00111100");
}

TEST(operationTest, operation_shift_right) {
    bitSet<8> b(0b11110000); 
    bitSet<8> result = b >> 3;

    EXPECT_EQ(result.to_string(), "00011110");
}


// referenceTest
TEST(referenceTest, constructor) {
    std::byte byte = std::byte{ 0 };
    bitSet<8> b;
    auto ref = b[3];

    EXPECT_EQ(static_cast<bool>(ref), false);
}

TEST(referenceTest, assignement_operator) {
    std::byte byte = std::byte{ 0 };
    bitSet<8> b;
    auto ref = b[3];

    ref = true;
    EXPECT_TRUE(static_cast<bool>(ref));

    ref = false;
    EXPECT_FALSE(static_cast<bool>(ref));
}

TEST(referenceTest, copy_assignement_operator) {
    bitSet<8> b1;
    b1[3] = true;

    bitSet<8> b2;
    auto ref1 = b1[3];
    auto ref2 = b2[3];

    ref2 = ref1;

    EXPECT_TRUE(static_cast<bool>(ref2));
    EXPECT_TRUE(static_cast<bool>(ref1));

    ref1 = false;
    EXPECT_FALSE(static_cast<bool>(ref1));
    EXPECT_TRUE(static_cast<bool>(ref2));
}

TEST(referenceTest, bool_operator) {
    std::byte byte = std::byte{ 0 };
    bitSet<8> b;
    auto ref = b[3]; 

    ref = true; 
    EXPECT_TRUE(static_cast<bool>(ref)); 

    ref = false; 
    EXPECT_FALSE(static_cast<bool>(ref));
}

TEST(referenceTest, flip) {
    std::byte byte = std::byte{ 0 };
    bitSet<8> b;
    auto ref = b[3]; 

    ref.flip(); 
    EXPECT_TRUE(static_cast<bool>(ref)); 

    ref.flip(); 
    EXPECT_FALSE(static_cast<bool>(ref));
}