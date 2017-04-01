#include "linked_list.h"
#include <stdlib.h>

int main() {

  structures::LinkedList<int> list{};

  /*for (auto i = 0; i < 10; ++i) {
      list.push_back(i);
      printf("i=%d = %d\n", i, list.at(i));
  }
  for (auto i = 9; i >= 0; --i) {
      //ASSERT_EQ(i, list.pop_back());
      printf("i=%d = %d\n", i, list.pop_back());
  }
  //ASSERT_TRUE(list.empty());

  printf("tamanho = %lu\n", list.size());
  list.desenha_arvore();*/    //popback

  /*for (auto i = 9; i >= 0; --i) {
      list.push_front(i);
  }
  list.desenha_arvore();
  for (auto i = 0; i < 10; ++i) {
      printf("i=%d = %d\n", i, list.pop_front());
  }
  printf("VAZIO = %d\n", list.empty());*/  //  pop_front

  for (auto i = 0; i < 10; ++i) {
      list.push_back(i);
  }
  list.desenha_arvore();

  //ASSERT_EQ(5, list.pop(5));
  printf("5 = %d\n", list.pop(5));

  //ASSERT_EQ(6, list.pop(5));
  printf("6 = %d\n", list.pop(5));

  //ASSERT_EQ(8u, list.size());
  printf("tam 8 = %lu\n", list.size());

  //ASSERT_THROW(list.pop(8), std::out_of_range);
  try {
    list.pop(8);
  }catch(std::out_of_range error) {
    printf("%s\n", error.what());
  }

  return 0;
}
