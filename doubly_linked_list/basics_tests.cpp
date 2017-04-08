#include "doubly_linked_list.h"

int main(int argc, char const *argv[]) {
  structures::DoublyLinkedList<int> list{};

  for (auto i = 0; i < 5; ++i) {
      list.push_back(i);
  }
  for (auto i = 6; i < 10; ++i) {
      list.push_back(i);
  }

  list.insert(5, 5u);

  for (auto i = 0; i < 10; ++i) {
      printf("%d\n", list.at(i));
  }
  /*
  for (auto i = 0; i < 10; ++i) {
      ASSERT_EQ(i, list.at(i));
  }*/

  return 0;
}
