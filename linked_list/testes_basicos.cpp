//#include "linked_list_curta.h"
#include "linked_list.h"
#include <stdlib.h>

int main() {

  structures::LinkedList<int> list{};

  for (auto i = 9; i >= 0; --i) {
      list.insert_sorted(i);
  }
  list.draw_connection();
  for (auto i = 0; i < 10; ++i) {
      list.pop_back();
      list.draw_connection();
  }
  list.clear();

  list.insert_sorted(10);
  list.insert_sorted(-10);
  list.insert_sorted(42);
  list.insert_sorted(0);
  list.draw_connection();

  return 0;
}
