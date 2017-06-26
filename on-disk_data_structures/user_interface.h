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

//! Classe UserInterface
/*! Interface do usuário.
 *
 *  \author João Vicente Souto.
 *  \since 20/06/17
 *  \version 1.0
 */
class UserInterface {
 public:
   UserInterface();  // Construtor
   ~UserInterface();  // Destrutor

   size_t choose_option();  // Escolhe uma opção
   string ask_word(const char* complement);  // Pede chave
};

//! Construtor
/*! Sem parâmetros, mensagem de boas vindas.
 *  \sa ~UserInterface()
 */
UserInterface::UserInterface() {
  cout << "Bem-vindo" << endl;
}

//! Destrutor
/*! Destrutor padrão, não tem nada alocado dinâmicamente.
 *  \sa UserInterface()
 */
UserInterface::~UserInterface() {}

//! Escolhe opção
/*! Imprime opções e espera o usuário passar uma opção válida.
 *  \return size_t opção
 *  \sa ask_word()
 */
size_t UserInterface::choose_option() {
  size_t option = 100;
  string aux;
  do {
    if (option == 100)
      cout << "\nEscolha uma das opções:" << endl;
    else
      cout << "\nOpção inválida, escolha novamente:" << endl;

    cout << "0 : Busca por chave primária (Imprime manpage)." << endl;
    cout << "1 : Busca por chave secundária." << endl;
    cout << "2 : Busca conjuntiva por chave secundária." << endl;
    cout << "3 : Busca disjuntiva por chave secundária." << endl;
    cout << "4 : Informações." << endl;
    cout << "5 : Sair." << endl;
    cout << ">> ";
    cin >> aux;

    try {
      option = stoi(aux);
    } catch (std::invalid_argument e) {
      option = 6;
      continue;
    }
  } while (option > 5);

  return option;
}

//! Pede uma palavra
/*! Imprime frase e retorna a chave que o usuário passar.
 *  \param char* frase
 *  \return size_t opção
 *  \sa ask_word()
 */
string UserInterface::ask_word(const char* phrase) {
  string in;
  cout << phrase << endl;
  cout << ">> ";
  cin >> in;
  return in;
}

}  //  namespace structures

#endif
