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
   UserInterface *user_;
   size_t counter_primary{0u},
          counter_secondary{0u};
};

System::System() {
  handler_ = new WordHandler();
  tree_ = new KDTreeOnDisk();
  user_ = new UserInterface();
}

System::~System() {
  delete handler_;
  delete tree_;
  delete user_;
}

// Idéia: começar pegando os arquivos do meio do array argv e indo
// para as extremidades para aproveitar e deixar a árvore k-d o mais
// "balanceada" possível.
void System::init(int argc, char const *argv[]) {
  size_t decrement, increment;
  string dir, aux;
  LinkedList<string> *words;
  counter_primary = argc-1;

  increment = static_cast<size_t>((argc-1)/2)+1;
  decrement = increment-1;

  for (size_t i = 1; i < argc; ++i) {
    dir = i % 2 == 0? argv[increment++] : argv[decrement--];

    ifstream file(dir.c_str(), ios::in);
    words = handler_->treatment(file);
    dir = handler_->clean_primary_key(dir);

    counter_secondary += words->size();

    while (!words->empty()) {
      aux = words->pop_front();
      cout << dir << " -> " << aux << endl;
      tree_->insert(dir.c_str(), aux.c_str(), i);
    }
    delete words;
  }
}

void System::run() {
  string word_one, word_two;
  LinkedList<string> *list;
  size_t option = 0;
  while (option != 5) {
    option = user_->choose_option();
    switch (option) {
      case 0: // Busca primária
        word_one = user_->ask_word("\nInforme a chave primária:");
        cout << "Offset: " << tree_->search_primary_key(word_one.c_str()) << endl;
        break;

      case 1: // Busca secundária
        word_one = user_->ask_word("\nInforme a chave secundária:");
        list = tree_->search_secondary_key(word_one.c_str());

        cout << "Tamanho lista secundária: " << list->size() << endl;
        for (size_t i = 0; i < list->size(); i++)
          cout << "i: " << i <<  " = " << list->at(i) << endl;

        break;

      case 2: // Busca conjuntiva
        word_one = user_->ask_word("\nInforme a 1ª chave secundária:");
        word_two = user_->ask_word("\nInforme a 2ª chave secundária:");
        list = tree_->conjunctive_search(word_one.c_str(), word_two.c_str());

        cout << "Tamanho lista conjunt.: " << list->size() << endl;
        for (size_t i = 0; i < list->size(); i++)
          cout << "i: " << i <<  " = " << list->at(i) << endl;
        break;

      case 3: // Busca disjuntiva
        word_one = user_->ask_word("\nInforme a 1ª chave secundária:");
        word_two = user_->ask_word("\nInforme a 2ª chave secundária:");
        list = tree_->disjunctive_search(word_one.c_str(), word_two.c_str());

        cout << "Tamanho lista disjunt.: " << list->size() << endl;
        for (size_t i = 0; i < list->size(); i++)
          cout << "i: " << i <<  " = " << list->at(i) << endl;
        break;

      case 4: // Busca Informaçoes e estatisticas
        break;

      default: // Sair
        break;
    }
  }
}

}  //  namespace structures

#endif
