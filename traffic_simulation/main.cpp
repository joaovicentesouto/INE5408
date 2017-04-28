//!  Copyright [2017] <João Vicente Souto>
#include <cstdint> // std::size_t
#include <stdexcept> // C++ exceptions
#include <string> // C++ exceptions
#include <stdio.h>

#include "./car.h"

int main(int argc, char const *argv[]) {
  srand(time(NULL));

  structures::Car* carro = new structures::Car();
  printf("%lu\n", carro->size());
  printf("%lu\n", carro->direction());
  structures::Car* carro2 = new structures::Car();
  printf("%lu\n", carro2->size());
  carro2->direction(2u);
  printf("%lu\n", carro2->direction());

  return 0;
}
