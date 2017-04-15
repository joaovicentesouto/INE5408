#include "doubly_circular_list.h"

int main(int argc, char const *argv[]) {
  structures::DoublyCircularList<int> list{};
  list.push_back(2);
  printf("%lu\n", list.size());
  list.push_front(1);
  printf("%d\n", list.pop_front());
  printf("%lu\n", list.size());
  printf("%d\n", list.at(0));
  //printf("%lu\n", list.size());
  //list.push_back(1);
  return 0;
}
