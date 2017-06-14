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
#include "./structures/array_list.h"

using namespace std;

namespace structures {

class WordHandler {
 public:
   WordHandler();
   ~WordHandler();

   LinkedList<string> treatment(ifstream &file);

 private:
   ArrayList<string> ignored_words{150};
   string separations{" '`^,.-+:;=<>[](){}|/_%*&$#@!?0123456789\"\f\n\r\t\v\\"};
   char *token{nullptr};
};

WordHandler::WordHandler() {
  ifstream file("./ignored_words.txt", ios::in);
  string word;

  if (!file)
    throw std::out_of_range("Error: open ./ignored_words.txt");

  file.seekg(0);
  while (file >> word) { // pega palavras separadas por espaços
    token = strtok(&word[0], separations.c_str());

    while (token != NULL) {
      string temp(token);
      ignored_words.push_back(temp); // não precisa ser em ordem
      token = strtok(NULL, separations.c_str()); // de alguma maneira pega o próximo
    }
  }

  /*for (size_t i = 0; i < ignored_words.size(); i++) {
    cout << ignored_words.at(i) << endl;
  }*/

}

WordHandler::~WordHandler() {}

LinkedList<string> WordHandler::treatment(ifstream &file) {
  string word;
  LinkedList<string> list;

  file.seekg(0);
  while (file >> word) { // pega palavras separadas por espaços
    token = strtok(&word[0], separations.c_str());

    while (token != NULL) {
      string temp(token);
      transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

      if (!ignored_words.contains(temp))
        list.insert_sorted(temp); // não precisa ser em ordem
      token = strtok(NULL, separations.c_str()); // de alguma maneira pega o próximo
    }
  }

  return list;
}

}  //  namespace structures

#endif
