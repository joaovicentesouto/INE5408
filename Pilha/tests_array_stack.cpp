/* Copyright [2016] <João Paulo Taylor Ienczak Zanette>
 * test_array_stack.cpp
 */

#include "gtest/gtest.h"
#include "array_stack.h"

#include <stdexcept>

int main(int argc, char* argv[]) {
    std::srand(std::time(NULL));
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::FLAGS_gtest_death_test_style = "fast";
    return RUN_ALL_TESTS();
}

class ArrayStackTest: public ::testing::Test {
protected:
    structures::ArrayStack<int> stack{10u};
};


TEST_F(ArrayStackTest, Push) {
    stack.push(0);
    ASSERT_EQ(1u, stack.size());
    ASSERT_EQ(0, stack.top());

    stack.push(2);
    ASSERT_EQ(2, stack.top());
    stack.push(-1);
    ASSERT_EQ(-1, stack.top());
    ASSERT_EQ(3u, stack.size());
}

TEST_F(ArrayStackTest, StackEmpty) {
    ASSERT_TRUE(stack.empty());
}

TEST_F(ArrayStackTest, StackNotEmpty) {
    ASSERT_TRUE(stack.empty());
    stack.push(1);
    ASSERT_FALSE(stack.empty());
}

TEST_F(ArrayStackTest, StackClear) {
    for (auto i = 0; i < 10; ++i) {
        stack.push(i);
    }
    stack.clear();
    ASSERT_EQ(0u, stack.size());
    ASSERT_TRUE(stack.empty());
}

TEST_F(ArrayStackTest, StackOverflow) {
    ASSERT_FALSE(stack.full());
    for (auto i = 0; i < (int)stack.max_size(); ++i) {
        stack.push(i);
    }
    ASSERT_EQ(stack.max_size(), stack.size());
    ASSERT_TRUE(stack.full());
    ASSERT_THROW(stack.push(0), std::out_of_range);
}

TEST_F(ArrayStackTest, Pop) {
    for (auto i = 0; i < 10; ++i) {
        stack.push(i);
    }

    for (auto i = 0u; i < 10u; ++i) {
        ASSERT_EQ(9-i, stack.pop());
    }
    ASSERT_TRUE(stack.empty());
    ASSERT_FALSE(stack.full());
}

TEST_F(ArrayStackTest, PopFromEmptyStack) {
    ASSERT_THROW(stack.pop(), std::out_of_range);
}

