#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include <algorithm>

#include <iostream>
#include <fstream>
#include <cstdio>  // para gets()
#include <sys/stat.h>

#include <typeinfo>
#include <string>

#include "./kd_tree_on_disk.h"
#include "./word_handler.h"
#include "./user_interface.h"
#include "./system.h"
#include "./structures/linked_list.h"

// Maior chave primária: 48
// Maior chave secundária: 58

using namespace structures;

int main(int argc, char const *argv[]) {

  System sys;
  sys.init(argc, argv);
  sys.run();

  // mais de 800 mil nodes criados

  return 0;
}
