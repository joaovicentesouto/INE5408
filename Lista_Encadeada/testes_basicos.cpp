#include "linked_list.h"
#include <stdlib.h>

int main() {

  structures::LinkedList<int> list{};

  /*for (auto i = 9; i >= 0; --i) {
      list.insert_sorted(i);
  }
  for (auto i = 0; i < 10; ++i) {
      //ASSERT_EQ(i, list.at(i));
      printf("i=%d = %d\n", i, list.at(i));
  }

  list.clear();*/

  list.insert_sorted(10);
  list.insert_sorted(-10);
  list.insert_sorted(42);
  list.insert_sorted(0);
  list.insert_sorted(10000);
  list.insert_sorted(-10000);
  list.insert_sorted(2);
  //ASSERT_EQ(-10, list.at(0));
  //ASSERT_EQ(0, list.at(1));
  //ASSERT_EQ(10, list.at(2));
  //ASSERT_EQ(42, list.at(3));

  /*list.clear();
  list.insert_sorted(10);
  list.insert_sorted(-10);
  list.insert_sorted(42);
  list.insert_sorted(0);
  //printf("Valor = %d\n", list.at(0));
  //printf("Valor = %d\n", list.at(1));
  //printf("Valor = %d\n", list.at(2));*/
  printf("tamanho = %lu\n", list.size());
  list.desenha_arvore();

  return 0;
}
