//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_SYSTEM_H
#define STRUCTURES_SYSTEM_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include <algorithm>
#include <cmath> // pow

#include <iostream>
#include <fstream>
#include <cstdio>  // para gets()
#include <sys/stat.h>

#include "./structures/linked_list.h"
#include "./structures/linked_stack.h"
#include "./structures/array_list.h"

using namespace std;

namespace structures {

class System {
 public:
   System();
   ~System();

   void init(int argc, char const *argv[]);
   void run();
   void statistics();

 private:
   WordHandler *handler_;
   KDTreeOnDisk *tree_;
   size_t counter_primary{0u},
          counter_secondary{0u};
};

System::System() {
  handler_ = new WordHandler();
  tree_ = new KDTreeOnDisk();
}

System::~System() {
  delete handler_;
  delete tree_;
}

System::init(int argc, char const *argv[]) {
  
}

}  //  namespace structures

#endif
