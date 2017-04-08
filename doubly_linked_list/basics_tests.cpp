#include "doubly_linked_list.h"

int main(int argc, char const *argv[]) {
  structures::DoublyLinkedList<int> list{};

  for (auto i = 9; i >= 0; --i) {
      list.insert_sorted(i);
  }
  for (auto i = 0; i < 10; ++i) {
      //printf("%d\n", list.at(i));
  }

  list.clear();

  list.insert_sorted(10);
  list.insert_sorted(-10);
  list.insert_sorted(42);
  list.insert_sorted(0);
  list.insert_sorted(-42);
  for (auto i = 0; i < list.size(); ++i) {
      printf("%d\n", list.at(i));
  }
  //ASSERT_EQ(-10, list.at(0));
  //ASSERT_EQ(0, list.at(1));
  //ASSERT_EQ(10, list.at(2));
  //ASSERT_EQ(42, list.at(3));

  return 0;
}
