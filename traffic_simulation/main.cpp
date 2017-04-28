//!  Copyright [2017] <João Vicente Souto>
#include <cstdint> // std::size_t
#include <stdexcept> // C++ exceptions
#include <string> // C++ exceptions
#include <stdio.h>

//#include "./linked_list.h"
//#include "./array_list.h"
//#include "./entry_road.h"
//#include "./exit_road.h"
//#include "./input_event.h"
//#include "./linked_queue_of_cars.h"
#include "./car.h"

int main(int argc, char const *argv[]) {

  //structures::ArrayList<*LinkedQueueOfCars> *entry_roads(8);
  //structures::ArrayList<*LinkedQueueOfCars> *exit_roads(8);

  structures::Car *carro = new structures::Car();
  printf("tamanho carro = %lu\n", carro->size());

  return 0;
}
