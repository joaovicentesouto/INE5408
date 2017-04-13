#include "circular_list.h"

int main(int argc, char const *argv[]) {
  structures::CircularList<int> list{};

  for (auto i = 0; i < 10; ++i) {
    list.push_back(i);
  }

  size_t t = 0;
  list.insert(42, t);

  printf("tamanho: %lu\n", list.size());
  list.draw_connection();

  return 0;
}
