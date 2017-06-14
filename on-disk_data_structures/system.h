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
#include "./word_handler.h"

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
   UserInterface *talk_;
   size_t counter_primary{0u},
          counter_secondary{0u};
};

System::System() {
  handler_ = new WordHandler();
  tree_ = new KDTreeOnDisk();
  talk_ = new UserInterface();
}

System::~System() {
  delete handler_;
  delete tree_;
  delete talk_;
}

void System::init(int argc, char const *argv[]) {
  size_t increment, decrement;
  // Idéia: começar pegando os arquivos do meio do array argv e indo
  // para as extremidades para aproveitar e deixar a árvore k-d o mais
  // "balanceada" possível.
  counter_primary = argc-1;

}

}  //  namespace structures

#endif
