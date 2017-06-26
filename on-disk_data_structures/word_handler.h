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

//! Classe WordHandler
/*! Tratador de palavras, uma ou um conjunto.
 *
 *  \author João Vicente Souto.
 *  \since 20/06/17
 *  \version 1.0
 */
class WordHandler {
 public:
   WordHandler();  // Construtor
   ~WordHandler();  // Destrutor

   string clean_primary_key(string key);  // Limpa chave primária
   LinkedList<string>* treatment(ifstream &file);  // Limpa chaves secundárias

 private:
   ArrayList<string> ignored_words{250};  //!< Palavras ignoradas
   string separations{" '`^,.-+:;=<>[](){}|/_%*&$#@!?0123456789\"\f\n\r\t\v\\"};  //!< Separadores
   char *token{nullptr};  //!< Ponteiro auxiliar
};

//! Construtor
/*! Sem parâmetros, carrega palavras ignoradas de arquivo em disco.
 *  \sa ~ArrayStack()
 */
WordHandler::WordHandler() {
  ifstream file("./ignored_words.txt", ios::in);
  string word;

  if (!file)
    throw std::out_of_range("Error: open ./ignored_words.txt");

  file.seekg(0);
  while (file >> word) {
    token = strtok(&word[0], separations.c_str());

    while (token != NULL) {
      string temp(token);
      ignored_words.push_back(temp);
      token = strtok(NULL, separations.c_str());
    }
  }

}

//! Destrutor
/*! Destrutor padrão, não tem nada alocado dinâmicamente.
 *  \sa ArrayStack()
 */
WordHandler::~WordHandler() {}

//! Limpa chave primária
/*! Recebe uma palavra primária e tira o ./ManPages/ e o .txt
 *  \param string chave
 *  \return string chave limpa
 *  \sa treatment()
 */
string WordHandler::clean_primary_key(string key) {
  return key.substr(11, key.size()-15);
}

//! Limpa chaves secundárias
/*! Recebe um arquivo, pega as palavras do arquivo, limpa e
 *  retorna uma lista das palavras, sem repeti-las.
 *  \param ifstream &file referencia de um arquivo aberto.
 *  \return LinkedList<string> Lista das chaves do arquivo
 *  \sa clean_primary_key()
 */
LinkedList<string>* WordHandler::treatment(ifstream &file) {
  string word;
  LinkedList<string> *list = new LinkedList<string>();

  file.seekg(0);
  while (file >> word) {
    token = strtok(&word[0], separations.c_str());

    while (token != NULL) {
      string temp(token);
      transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

      if (!ignored_words.contains(temp) && !list->contains(temp))
        list->push_front(temp);
      token = strtok(NULL, separations.c_str());
    }
  }

  return list;
}

}  //  namespace structures

#endif
