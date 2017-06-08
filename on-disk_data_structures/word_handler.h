//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_WORD_HANDLER_H
#define STRUCTURES_WORD_HANDLER_H

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

using namespace std;

namespace structures {

class WordHandler {
 public:
   WordHandler();
   ~WordHandler();

   LinkedList<string> treatment(ifstream &file);

 private:
   LinkedList<string> ignored_words;
   char *separations;
   char *token{nullptr};
};

WordHandler::WordHandler() {
  strcpy(separations, " '`^,.-+:;=<>[](){}|/_%*&$#@!?0123456789\"\f\n\r\t\v\\");

  ifstream file("./ignored_words.txt", ios::in);
  string word;

  if (!file)
    throw std::out_of_range("Error: open ./ignored_words.txt");

  file.seekg(0);
  while (file >> word) { // pega palavras separadas por espaços
    token = strtok(&word[0], separations);

    while (token != NULL) {
      string temp(token);
      ignored_words.insert_sorted(temp); // não precisa ser em ordem
      token = strtok(NULL, separations); // de alguma maneira pega o próximo
    }
  }

  /*for (size_t i = 0; i < ignored_words.size(); i++) {
    cout << ignored_words.at(i) << endl;
  }*/

}

LinkedList<string> WordHandler::treatment(ifstream &file) {
  string word;
  LinkedList<string> test;

  file.seekg(0);
  while (file >> word) { // pega palavras separadas por espaços
    token = strtok(&word[0], separations);

    while (token != NULL) {
      string temp(token);
      transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

      if (!ignored_words.contains(temp))
        test.insert_sorted(temp); // não precisa ser em ordem
      token = strtok(NULL, separations); // de alguma maneira pega o próximo
    }
  }

  return test;
}

/*char seps[] = ;
char *token;
int maior_tam = 0;

// Pegando todos os arquivos e pegando a maior chave secundária
for (size_t i = 1; i < argc; i++) {
  ifstream file(argv[i], ios::in);
  file.seekg(0);
  string word;
  if (!file)
    cout << "Erro" << endl;

  while (file >> word) { // pega palavras separadas por espaços
    token = strtok(&word[0], seps);
    while (token != NULL) {
      if (maior_tam < strlen(token))
        maior_tam = strlen(token);

       token = strtok(NULL, seps); // de alguma maneira pega o próximo
       // Acho que ele pega e coloca vazio até achar \0, ou seja
       // substitui a primeira palavra por nada.
    }
  }
} */

}  //  namespace structures

#endif
