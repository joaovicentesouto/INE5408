//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_SYSTEM_H
#define STRUCTURES_SYSTEM_H

#include <cstdint>
#include <stdexcept>
#include <fstream>
#include <cstdio>
#include <sys/stat.h>

#include "./structures/linked_list.h"

#include "./kd_tree_on_disk.h"
#include "./binary_tree_of_lists_on_disk.h"
#include "./word_handler.h"
#include "./user_interface.h"

using namespace std;

namespace structures {

//! Classe System
/*! Sistema responsável por gerenciar todas as árvore e interface
 *  com o usuário.
 *
 *  \author João Vicente Souto.
 *  \since 20/06/17
 *  \version 1.0
 */
class System {
 public:
   System();  // Construtor
   ~System();  // Destrutor

   void init(int argc, char const *argv[]);  // Iniciação
   void run();  // Roda sistema

 private:
   WordHandler *handler_;                 //!< Tratador de palavras
   KDTreeOnDisk *primary_tree_;           //!< Árvore primária
   BinaryTreeOfListOnDisk *secondary_tree_;  //!< Árvore secundária
   UserInterface *user_;                  //!< Interface usuário
   size_t counter_primary{0u},            //!< Contador de chaves primárias
          counter_secondary{0u};          //!< Contador de chaves secundárias
};

//! Construtor
/*! Sem parâmetros, carrega palavras ignoradas de arquivo em disco.
 *  \sa ~System()
 */
System::System() {
  handler_ = new WordHandler();
  primary_tree_ = new KDTreeOnDisk();
  secondary_tree_ = new BinaryTreeOfListOnDisk();
  user_ = new UserInterface();
}

//! Destrutor
/*! Destrutor padrão, desaloca memória.
 *  \sa System()
 */
System::~System() {
  delete handler_;
  delete primary_tree_;
  delete secondary_tree_;
  delete user_;
}

//! Inicialização
/*! Recebe quantidade e arquivos a serem indexados.
 *  Idéia: começar pegando os arquivos do meio do array argv e indo
 *  para as extremidades para aproveitar e deixar a árvore k-d o mais
 *  "balanceada" possível.
 *  \param int argc quantidade-1 de arquivos
 *  \param char const *argv[] diretórios dos arquivos
 *  \sa run()
 */
void System::init(int argc, char const *argv[]) {
  size_t decrement, increment;
  int offset = 0;
  string dir, aux;
  LinkedList<string> *words;
  struct stat st;

  increment = static_cast<size_t>(((int) ((argc-1) / 2)) + 1);
  decrement = increment-1;

  for (size_t i = 1; i < argc; ++i) {
    counter_primary++;
    dir = i % 2 == 1? argv[increment++] : argv[decrement--];

    // Chave primária e manpages
    if (stat(dir.c_str(), &st) != 0)
      throw std::out_of_range("Erro ao verificar tamanho do arquivo.");

    ifstream file(dir.c_str(), ios::in);

    char manpage[st.st_size];
    file.seekg(0);
    file.read(manpage, st.st_size);

    manpage[st.st_size-1] = '\0';
    dir = handler_->clean_primary_key(dir);
    offset = primary_tree_->insert(dir.c_str(), st.st_size, manpage);

    words = handler_->treatment(file);
    counter_secondary += words->size();

    while (!words->empty()) {
      aux = words->pop_front();
      secondary_tree_->insert(aux.c_str(), offset);
    }

    file.close();
    delete words;
  }
}

//! Roda sistema
/*! Conversa com usuário e executa as opções que ele deseja.
 *  \sa init()
 */
void System::run() {
  string word_one, word_two;
  char* manpage;
  LinkedList<string> *manpages;
  LinkedList<size_t> *offsets;
  size_t option = 0, count;

  while (option != 5) {
    option = user_->choose_option();

    switch (option) {
      case 0:
        word_one = user_->ask_word("\nInforme a chave primária:");
        manpage = primary_tree_->search_primary_key(word_one.c_str());
        if (manpage != nullptr) {
          cout << endl << word_one << endl << endl;
          cout << manpage << endl;
        } else {
          cout << "\nArquivo \"" << word_one << "\" não encontrado." << endl;
        }

        delete manpage;
        break;

      case 1:
        word_one = user_->ask_word("\nInforme a chave secundária:");
        offsets = secondary_tree_->search(word_one.c_str());
        manpages = primary_tree_->return_primary_key(offsets);

        cout << endl << manpages->size() << " arquivos encontrados com \"";
        cout << word_one << "\":\n" << endl;
        count = 1;
        while (!manpages->empty()) {
          cout << count++ << ". " << manpages->pop_front() << endl;
        }

        delete offsets;
        delete manpages;
        break;

      case 2:
        word_one = user_->ask_word("\nInforme a chave 1ª secundária:");
        word_two = user_->ask_word("\nInforme a chave 2ª secundária:");
        offsets = secondary_tree_->conjunctive_search(word_one.c_str(), word_two.c_str());
        manpages = primary_tree_->return_primary_key(offsets);

        cout << endl << manpages->size() << " arquivos encontrados com \"";
        cout << word_one << "\" ou \"" << word_two << "\":\n" << endl;
        count = 1;
        while (!manpages->empty()) {
          cout << count++ << ". " << manpages->pop_front() << endl;
        }

        delete offsets;
        delete manpages;
        break;

      case 3:
        word_one = user_->ask_word("\nInforme a chave 1ª secundária:");
        word_two = user_->ask_word("\nInforme a chave 2ª secundária:");
        offsets = secondary_tree_->disjunctive_search(word_one.c_str(), word_two.c_str());
        manpages = primary_tree_->return_primary_key(offsets);

        cout << endl << manpages->size() << " arquivos encontrados com \"";
        cout << word_one << "\" e \"" << word_two << "\":\n" << endl;
        count = 1;
        while (!manpages->empty()) {
          cout << count++ << ". " << manpages->pop_front() << endl;
        }

        delete offsets;
        delete manpages;
        break;

      case 4:
        cout << "\nÁrvore primária\nQuantidade de nodes: ";
        cout << primary_tree_->size() << endl;
        cout << "Profundidade: " << primary_tree_->depth() << endl;
        cout << "\nÁrvore secundária\nQuantidade de nodes: ";
        cout << secondary_tree_->size() << endl;
        cout << "Profundidade: " << secondary_tree_->depth() << endl;
        break;

      default:
        cout << "\nFIM" << endl;
        break;
    }
  }
}

}  //  namespace structures

#endif
