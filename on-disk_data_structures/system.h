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
   UserInterface *user_io_;
   size_t counter_primary{0u},
          counter_secondary{0u};
};

System::System() {
  handler_ = new WordHandler();
  tree_ = new KDTreeOnDisk();
  user_io_ = new UserInterface();
}

System::~System() {
  delete handler_;
  delete tree_;
  delete user_io_;
}

// Idéia: começar pegando os arquivos do meio do array argv e indo
// para as extremidades para aproveitar e deixar a árvore k-d o mais
// "balanceada" possível.
void System::init(int argc, char const *argv[]) {
  size_t decrement, increment;
  string dir;
  LinkedList<string> *words;
  counter_primary = argc-1;

  increment = static_cast<size_t>((argc-1)/2)+1;
  decrement = increment-1;

  printf("\nQuantidade de arquivos indexados: %d\n", argc-1);

  for (size_t i = 1; i < argc; ++i) {
    dir = i % 2 == 0? argv[increment++] : argv[decrement--];

    ifstream file(dir.c_str(), ios::in);
    words = handler_->treatment(file);
    dir = handler_->clean_primary_key(dir);

    counter_secondary += words->size();

    //cout << words->size() << endl;
    string aux;
    cout << dir << endl;
    while (!words->empty()) {
      aux = words->pop_front();
      cout << "Inserindo: " << aux << endl;
      tree_->insert(dir.c_str(), aux.c_str(), 100);
    }
    delete words;
  }

  printf("Total de nodes criados: %lu\n", counter_secondary);

}

}  //  namespace structures

#endif
