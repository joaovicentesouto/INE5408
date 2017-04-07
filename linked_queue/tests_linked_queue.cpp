/* Copyright [2016] <João Paulo Taylor Ienczak Zanette> */

#include "gtest/gtest.h"
#include "linked_queue.h"

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


class LinkedQueueTest: public ::testing::Test {
protected:
    structures::LinkedQueue<int> queue{};
};


TEST_F(LinkedQueueTest, Enqueue) {
    queue.enqueue(0);
    ASSERT_EQ(0, queue.front());
    ASSERT_EQ(0, queue.back());
    ASSERT_EQ(1u, queue.size());

    queue.enqueue(2);
    ASSERT_EQ(0, queue.front());
    ASSERT_EQ(2, queue.back());
    ASSERT_EQ(2u, queue.size());

    queue.enqueue(-1);
    ASSERT_EQ(0, queue.front());
    ASSERT_EQ(-1, queue.back());
    ASSERT_EQ(3u, queue.size());
}

TEST_F(LinkedQueueTest, Dequeue) {
    for (auto i = 0; i < 10; ++i) {
        queue.enqueue(i);
        ASSERT_EQ(0, queue.front());
        ASSERT_EQ(i, queue.back());
    }

    for (auto i = 0; i < 10; ++i) {
        ASSERT_EQ(i, queue.front());
        ASSERT_EQ(9, queue.back());
        ASSERT_EQ(i, queue.dequeue());
    }
    ASSERT_TRUE(queue.empty());
}

TEST_F(LinkedQueueTest, ClearQueue) {
    for (auto i = 0; i < 10; ++i) {
        queue.enqueue(i);
    }
    queue.clear();
    ASSERT_EQ(0u, queue.size());
}

TEST_F(LinkedQueueTest, EmptyQueue) {
    ASSERT_TRUE(queue.empty());
    ASSERT_THROW(queue.front(), std::out_of_range);
    ASSERT_THROW(queue.back(), std::out_of_range);
}

TEST_F(LinkedQueueTest, NotEmptyQueue) {
    queue.enqueue(1);
    ASSERT_FALSE(queue.empty());
    queue.clear();
    ASSERT_TRUE(queue.empty());
    ASSERT_THROW(queue.back(), std::out_of_range);
    ASSERT_THROW(queue.dequeue(), std::out_of_range);
}

