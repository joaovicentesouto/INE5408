//!  Copyright [2017] <João Vicente Souto>
#include <cstdint> // std::size_t
#include <stdexcept> // C++ exceptions
#include <string> // C++ exceptions
#include <stdio.h>

#include <stdlib.h>
#include <time.h>

#include "./linked_list.h"
//#include "./array_list.h"
//#include "./entry_road.h"
//#include "./exit_road.h"
//#include "./input_event.h"
#include "./linked_queue_of_cars.h"
#include "./car.h"
#include "./event.h"

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  std::size_t b = 5;
  //structures::LinkedList<structures::Event*> system_events{};
  structures::LinkedQueueOfCars test{50,50,b};
  structures::Car* car = new structures::Car();
  printf("car:%lu\n", car->size());
  printf("sizep:%lu\n", test.size());
  printf("maxp:%lu\n", test.max_size());
  printf("b:%lu\n", b);
  structures::Event* x = nullptr;
  test.enqueue(car, x);
  printf("b:%lu\n", b);

  return 0;
}
