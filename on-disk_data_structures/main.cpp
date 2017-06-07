#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include <algorithm>

#include <iostream>
#include <fstream>
#include <cstdio>  // para gets()
#include <sys/stat.h>

#include <typeinfo>
#include <string>

#include "./kd_tree_on_disk.h"

using namespace structures;

int main(int argc, char const *argv[]) {

  KDTreeOnDisk tree;

  ifstream file("./ManPages/Intro.4.txt", ios::in);
  file.seekg(0);
  string word;
  if (!file)
    cout << "Erro" << endl;


  char * pointer;
  char * w;
  while (file >> word) { // pega palavras separadas por espaços
    // Separa nos caracteres especiais
    /*cout << word << endl;
    w = const_cast<char*>(word.c_str());
    pointer = strtok (w, " ',.-+:<>[]()=;|_%*&$#@!?}{/^\"\\0123456789\t\r\n\f\v`");
    while (pointer != nullptr) {
      cout << pointer << endl;
      pointer = strtok (NULL, " ',.-+:<>[]()=;|_%*&$#@!?}{/^\"\\0123456789\t\r\n\f\v`");
    }*/
    char seps[] = " '`,.-+:<>[]()=;|_%*&$#@!?}{/^0123456789\"\f\n\r\t\v\\"; //
    char *token;

    token = strtok( &word[0], seps );
    while( token != NULL )
    {
       /* faz algo entre isso com a palavra*/
       cout << word << endl;
       cout << token << '\n' << endl;
       /* faz algo entre isso */

       // pega próxima separação e limpa
       token = strtok( NULL, seps );
    }



    // limpa caracteres especiais
    /*word.erase(
      std::remove_if(
        word.begin(), word.end(),
        [](char c) {
          return !(std::isspace(c) || std::isalpha(c));
        }
      ),
      word.end());
      cout << word << endl;
      */
  }

  /* TESTE NOME DE ARQUIVOS
  if (argc == 1)
    return 1;

    printf("\n Arquivos: %d \n", argc - 1);
    string temp;
    for (auto i = 1; i < argc; i++) {
      temp = argv[i];
      printf("ant --> %s\n", temp.c_str());
      temp = temp.substr(11, temp.size()-15);
      printf("dps --> %s\n", temp.c_str());
    }*/

  /* TESTES REALIZADOS 06/JUNHO
  cout << "Tamanho antes: " << tree.size() << endl;

  tree.insert((char*)"e", (char*)"e", 0);
  tree.insert((char*)"c", (char*)"c", 1);
  tree.insert((char*)"g", (char*)"g", 2);
  tree.insert((char*)"b", (char*)"b", 3);
  tree.insert((char*)"d", (char*)"d", 4);
  tree.insert((char*)"j", (char*)"g", 5); //j
  tree.insert((char*)"h", (char*)"h", 6);
  tree.insert((char*)"a", (char*)"a", 7);
  tree.insert((char*)"g", (char*)"e", 8); //i
  tree.insert((char*)"j", (char*)"e", 9);
  tree.insert((char*)"k", (char*)"k", 10);

  cout << "Tamanho depois: " << tree.size() << endl;

  int offset = tree.search_primary_key("k");
  cout << "O deslocamento para 'k' é: " << offset << endl;

  LinkedList<string> *list = tree.disjunctive_search("g", "e");
  cout << "Tamanho lista: " << list->size() << endl;

  for (size_t i = 0; i < list->size(); i++)
    cout << "i: " << i <<  " = " << list->at(i) << endl; */

  return 0;
}
