//!  Copyright [2017] <João Vicente Souto>
#include <cstdint> // std::size_t
#include <stdexcept> // C++ exceptions
#include <stdio.h>

#include "./system.h"

using namespace structures;

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  std::size_t global_clock=28800;
  std::size_t sema=80;

  System sys{global_clock, sema};
  sys.init();
  sys.run();
  sys.result();

  return 0;
}
