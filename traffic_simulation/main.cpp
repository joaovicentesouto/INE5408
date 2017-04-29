//!  Copyright [2017] <João Vicente Souto>
#include <cstdint> // std::size_t
#include <stdexcept> // C++ exceptions
#include <string> // C++ exceptions
#include <stdio.h>

#include "./car.h"
#include "./event.h"
#include "./structures/linked_list.h"
typedef structures::Event Event;

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  std::size_t global_clock=5;

  structures::LinkedList<Event> events{};
  structures::Event a(global_clock, 3, nullptr);
  structures::Event b(global_clock, 7, nullptr);
  printf("a_time:%lu < b_time:%lu ?\n", a.event_time(), b.event_time());
  printf("%d\n", a<b);

  return 0;
}
