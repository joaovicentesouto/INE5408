//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_USER_INTERFACE_H
#define STRUCTURES_USER_INTERFACE_H

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

class UserInterface {
 public:
   UserInterface();
   ~UserInterface();

   size_t choose_option();
   string ask_word(const char* complement);

   string about();
};

UserInterface::UserInterface() {
  cout << "Bem-vindo" << endl;
}

UserInterface::~UserInterface() {}

size_t UserInterface::choose_option() {
  bool cond = true;
  size_t option = 4;
  do {
    cout << "\nEscolha uma das opções:" << endl;
    cout << "1 : Busca por chave primária (Imprime manpage)." << endl;
    cout << "2 : Busca por chave secundária." << endl;
    cout << "3 : Busca conjuntiva por chave secundária." << endl;
    cout << "4 : Busca disjuntiva por chave secundária." << endl;
    cout << "5 : Informação e estatísticas." << endl;
    cout << "6 : Sair." << endl;
    cout << ">> ";
    cin >> option;

  } while (option > 6);

  return option;
}

string UserInterface::ask_word(const char* complement) {
  string in;
  cout << "Entre com a " << complement << endl;
  cout << ">> ";
  cin >> in;
  return in;
}

}  //  namespace structures

#endif
