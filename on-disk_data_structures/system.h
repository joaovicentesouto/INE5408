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
  //LinkedList<string> *words;
  struct stat st;

  increment = static_cast<size_t>((argc-1)/2)+1;
  decrement = increment-1;

  for (size_t i = 1; i < argc; ++i) {
    counter_primary++;
    dir = i % 2 == 0? argv[increment++] : argv[decrement--];

    // Chaves secundárias ainda nao implementado
    //words = handler_->treatment(file);
    //counter_secondary += words->size();

    // Chave primária e manpages
    if (stat(dir.c_str(), &st) != 0)
      throw std::out_of_range("Erro ao verificar tamanho do arquivo.");

    ifstream file(dir.c_str(), ios::in);

    char manpage[st.st_size];
    file.seekg(0);
    file.read(manpage, st.st_size);

    cout << "Inserindo: " << dir << " Tam: " << strlen(manpage) << endl;
    cout << manpage << endl;
    dir = handler_->clean_primary_key(dir);
    tree_->insert(dir.c_str(), strlen(manpage), manpage);

    file.close();
    //delete words;
  }
}

void System::run() {
  string word_one, word_two;
  char* manpage;
  LinkedList<string> *list;
  size_t option = 0;

  while (option != 5) {
    option = user_->choose_option();

    switch (option) {
      case 0:
        word_one = user_->ask_word("\nInforme a chave primária:");
        manpage = tree_->search_primary_key(word_one.c_str());
        cout << word_one << endl;
        cout << manpage << endl;
        break;

      default:
        cout << "FIM" << endl;
        break;
    }
  }
}

}  //  namespace structures

#endif
