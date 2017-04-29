//!  Copyright [2017] <João Vicente Souto>
#include <cstdint> // std::size_t
#include <stdexcept> // C++ exceptions
#include <string> // C++ exceptions
#include <stdio.h>

#include "./car.h"
#include "./event.h"
//#include "./input_event.h"
//#include "./output_event.h"
#include "./structures/linked_list.h"
#include "./system.h"

using namespace structures;

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  std::size_t global_clock=1000;
  std::size_t sema=30;

  System sys{global_clock, sema};
  sys.init();
  sys.run();
  sys.result();

  return 0;
}
