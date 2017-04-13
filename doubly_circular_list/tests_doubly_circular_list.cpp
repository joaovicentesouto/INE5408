// Copyright 2016 João Paulo Taylor Ienczak Zanette
#include "gtest/gtest.h"
#include "doubly_circular_list.h"

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/**
 * Teste para lista circular
 */
class DoublyCircularListTest: public ::testing::Test {
protected:
    /**
     * Lista para as operações de teste
     */
    structures::DoublyCircularList<int> list{};
};


TEST_F(DoublyCircularListTest, BasicPushBack) {
    list.push_back(0);
    ASSERT_EQ(1u, list.size());
    ASSERT_EQ(0, list.at(0));

    list.push_back(-1);
    ASSERT_EQ(2u, list.size());
    ASSERT_EQ(0, list.at(0));
    ASSERT_EQ(-1, list.at(1));
}

TEST_F(DoublyCircularListTest, PushBack) {
    for (auto i = 0; i < 10; ++i) {
        list.push_back(i);
    }

    ASSERT_EQ(10u, list.size());

    for (auto i = 0u; i < 10u; ++i) {
        ASSERT_EQ(i, list.at(i));
    }
}

TEST_F(DoublyCircularListTest, BasicPushFront) {
    list.push_front(0);
    ASSERT_EQ(1u,list.size());
    ASSERT_EQ(0, list.at(0));

    list.push_front(-1);
    ASSERT_EQ(2u, list.size());
    ASSERT_EQ(-1, list.at(0));
    ASSERT_EQ(0, list.at(1));
}

TEST_F(DoublyCircularListTest, PushFront) {
    for (auto i = 0; i < 10; ++i) {
        list.push_front(i);
    }

    ASSERT_EQ(10u, list.size());
    for (auto i = 0u; i < 10u; ++i) {
        ASSERT_EQ(9-i, list.at(i));
    }
}

TEST_F(DoublyCircularListTest, Empty) {
    ASSERT_TRUE(list.empty());
}

TEST_F(DoublyCircularListTest, NotEmpty) {
    ASSERT_TRUE(list.empty());
    list.push_back(1);
    ASSERT_FALSE(list.empty());
}

TEST_F(DoublyCircularListTest, Clear) {
    for (auto i = 0; i < 10; ++i) {
        list.push_back(i);
    }
    list.clear();
    ASSERT_EQ(0u, list.size());
}

TEST_F(DoublyCircularListTest, Find) {
    for (auto i = 0u; i < 10u; ++i) {
        list.push_back(i);
    }

    for (auto i = 0u; i < 10u; ++i) {
        ASSERT_EQ(i, list.find(i));
    }
    ASSERT_EQ(list.size(), list.find(10));
}

TEST_F(DoublyCircularListTest, Contains) {
    for (auto i = 0; i < 10; ++i) {
        list.push_back(i);
    }
    ASSERT_TRUE(list.contains(0));
    ASSERT_TRUE(list.contains(5));
    ASSERT_FALSE(list.contains(10));
}

TEST_F(DoublyCircularListTest, AccessAt) {
    for (auto i = 0; i < 10; ++i) {
        list.push_back(i);
    }
    for (auto i = 0u; i < 10u; ++i) {
        ASSERT_EQ(i, list.at(i));
    }
    list.clear();
    for (auto i = 10; i > 0; --i) {
        list.push_back(i);
    }
    for (auto i = 0u; i < 10u; ++i) {
        ASSERT_EQ(10-i, list.at(i));
    }
}

TEST_F(DoublyCircularListTest, AccessAtBoundCheck) {
    for (auto i = 0; i < 10; ++i) {
        list.push_back(i);
    }
    for (auto i = 0; i < 10; ++i) {
        ASSERT_NO_THROW(list.at(i));
    }
    ASSERT_NO_THROW(list.at(0));
    ASSERT_THROW(list.at(-1), std::out_of_range);
}

TEST_F(DoublyCircularListTest, Insert) {
    for (auto i = 0; i < 5; ++i) {
        list.push_back(i);
    }
    for (auto i = 6; i < 10; ++i) {
        list.push_back(i);
    }
    list.insert(5, 5u);

    for (auto i = 0; i < 10; ++i) {
        ASSERT_EQ(i, list.at(i));
    }
}

TEST_F(DoublyCircularListTest, InsertSorted) {
    for (auto i = 9; i >= 0; --i) {
        list.insert_sorted(i);
    }
    for (auto i = 0; i < 10; ++i) {
        ASSERT_EQ(i, list.at(i));
    }

    list.clear();

    list.insert_sorted(10);
    list.insert_sorted(-10);
    list.insert_sorted(42);
    list.insert_sorted(0);
    ASSERT_EQ(-10, list.at(0));
    ASSERT_EQ(0, list.at(1));
    ASSERT_EQ(10, list.at(2));
    ASSERT_EQ(42, list.at(3));
}

TEST_F(DoublyCircularListTest, InsertionBounds) {
    ASSERT_THROW(list.insert(1u, 1), std::out_of_range);
    ASSERT_THROW(list.insert(-1, 1), std::out_of_range);
}

TEST_F(DoublyCircularListTest, EmptyPopBack) {
    ASSERT_THROW(list.pop_back(), std::out_of_range);
}

TEST_F(DoublyCircularListTest, PopBack) {
    for (auto i = 0; i < 10; ++i) {
        list.push_back(i);
    }
    for (auto i = 9; i >= 0; --i) {
        ASSERT_EQ(i, list.pop_back());
    }
    ASSERT_TRUE(list.empty());
}

TEST_F(DoublyCircularListTest, EmptyPopFront) {
    ASSERT_THROW(list.pop_front(), std::out_of_range);
}

TEST_F(DoublyCircularListTest, PopFront) {
    for (auto i = 9; i >= 0; --i) {
        list.push_front(i);
    }
    for (auto i = 0; i < 10; ++i) {
        ASSERT_EQ(i, list.pop_front());
    }
    ASSERT_TRUE(list.empty());
}

TEST_F(DoublyCircularListTest, PopAt) {
    for (auto i = 0; i < 10; ++i) {
        list.push_back(i);
    }
    ASSERT_EQ(5, list.pop(5));
    ASSERT_EQ(6, list.pop(5));
    ASSERT_EQ(8u, list.size());
    ASSERT_THROW(list.pop(8), std::out_of_range);
}

TEST_F(DoublyCircularListTest, RemoveElement) {
    for (auto i = 0; i < 10; ++i) {
        list.push_back(i);
    }
    list.remove(4);
    ASSERT_EQ(9u, list.size());
    ASSERT_FALSE(list.contains(4));
}

