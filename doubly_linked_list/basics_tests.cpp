#include "doubly_linked_list.h"

int main(int argc, char const *argv[]) {
  structures::DoublyLinkedList<int> list{};

  for (auto i = 0; i < 5; ++i) {
      //list.push_back(i);
  }
  printf("%lu\n", list.size());
  list.push_back(0);

  for (auto i = 0; i < 10; ++i) {
      //printf("%d\n", list.at(i));
  }
  //list.draw_connection();
  //printf("%d\n", list.pop(5));
  //printf("%d\n", list.pop(5));

  //ASSERT_EQ(5, list.pop(5));
  //ASSERT_EQ(6, list.pop(5));
  //ASSERT_EQ(8u, list.size());
  //ASSERT_THROW(list.pop(8), std::out_of_range);

  return 0;
}
