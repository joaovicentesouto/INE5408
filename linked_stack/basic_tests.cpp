#include "linked_stack.h"

int main() {
  structures::LinkedStack<int> stack{};

  for(auto i = 0; i < 10; ++i)
    stack.push(i);

  printf("%d\n", stack.top());

  for(auto i = 0; i < 10; ++i)
    printf("%d\n", stack.pop());

  try {
    printf("%d\n", stack.top());
  } catch (std::out_of_range error) {
    printf("%s\n", error.what());
  }

  return 0;
}
