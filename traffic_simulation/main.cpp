//!  Copyright [2017] <João Vicente Souto>
#include <cstdint> // std::size_t
#include <stdexcept> // C++ exceptions
#include <string> // C++ exceptions
#include <stdio.h>

#include "./car.h"
#include "./event.h"
//#include "./input_event.h"
#include "./output_event.h"
#include "./output_event.h"
#include "./structures/linked_list.h"
typedef structures::Event Event;

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  std::size_t global_clock=5;

  structures::LinkedList<Event> events{};
  structures::OutputEvent a(global_clock, 3, nullptr);
  structures::OutputEvent b(global_clock, 7, nullptr);
  //structures::OutputEvent c(global_clock, 4, nullptr);
  //structures::OutputEvent d(global_clock, 1, nullptr);
  //structures::OutputEvent e(global_clock, 10, nullptr);
  events.insert_sorted(a);
  //events.insert_sorted(b);
  //events.insert_sorted(c);
  //events.insert_sorted(d);
  //events.insert_sorted(e);
  printf("tamanho:%lu\n", events.size());
  printf("primeiro:%lu\n", events.at(0).event_time());
  printf("segundo:%lu\n", events.at(1).event_time());
  //printf("terceiro:%lu\n", events.at(2).event_time());
  //printf("quarto:%lu\n", events.at(3).event_time());
  //printf("quinto:%lu\n", events.at(4).event_time());

  printf("a_time:%lu < b_time:%lu ?\n", events.at(0).event_time(), events.at(1).event_time());
  printf("%d\n", events.at(0)<events.at(1));

  return 0;
}
