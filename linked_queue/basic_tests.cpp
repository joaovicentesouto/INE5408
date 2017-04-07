#include "linked_queue.h"

int main(int argc, char const *argv[]) {
  structures::LinkedQueue<int> queue{};

  for (auto i = 0; i < 10; ++i)
    queue.enqueue(i);

  for (auto i = 0; i < 10; ++i) {
    printf("%d\n", queue.dequeue());
  }

  printf("Tamanho: %lu\n", queue.size());
  return 0;
}
