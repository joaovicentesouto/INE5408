#include "doubly_linked_list.h"

int main(int argc, char const *argv[]) {
  structures::DoublyLinkedList<int> list{};


  for (auto i = 0; i < 10; ++i) {
      list.push_back(i);
  }

  for (auto i = 0; i < 10; ++i) {
      printf("%d\n", list.at(i));
  }

  printf("%d\n", list.pop(5));
  printf("%lu\n", list.size());
  printf("%d\n", list.pop(5));

  return 0;
}
