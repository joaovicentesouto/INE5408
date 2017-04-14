#include "doubly_circular_list.h"

int main(int argc, char const *argv[]) {
  structures::DoublyCircularList<int> list{};
  list.push_back(0);
  printf("%lu\n", list.size());
  list.push_front(1);
  //printf("%lu\n", list.size());
  //list.push_back(1);
  return 0;
}
