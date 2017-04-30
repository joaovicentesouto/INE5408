//!  Copyright [2017] <João Vicente Souto>
#include <cstdint> // std::size_t
#include <stdexcept> // C++ exceptions
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#include "./system.h"

using namespace structures;

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  std::size_t _execution_time=28800;
  std::size_t _semaphore_time=80;

	std::cout << "Informe o tempo, em segundos, de execução da simulação: \n" << "> ";
	std::cin >> _execution_time;
	std::cout << "Informe o tempo, em segundos, que um semáforo ficará aberto: \n" << "> ";
	std::cin >> _semaphore_time;

  System sys{_execution_time, _semaphore_time};
  sys.init();
  sys.run();
  sys.result();

  return 0;
}
