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
#include "./word_handler.h"
#include "./user_interface.h"
#include "./system.h"
#include "./structures/linked_list.h"

// Maior chave primária: 48
// Maior chave secundária: 58

using namespace structures;

int main(int argc, char const *argv[]) {

  System sys;
  sys.init(argc, argv);

  /* Testes kd

  KDTreeOnDisk tree;
  cout << "Tamanho antes: " << tree.size() << endl;

  tree.insert((char*)"e", (char*)"e", 30);
  tree.insert((char*)"c", (char*)"c", 1);
  tree.insert((char*)"g", (char*)"g", 2);
  tree.insert((char*)"b", (char*)"b", 3);
  tree.insert((char*)"e", (char*)"g", 4);
  tree.insert((char*)"g", (char*)"e", 5); //j
  tree.insert((char*)"a", (char*)"e", 6);
  tree.insert((char*)"d", (char*)"e", 7);
  tree.insert((char*)"a", (char*)"h", 7);
  tree.insert((char*)"j", (char*)"j", 7);
  tree.insert((char*)"j", (char*)"j", 8); //i
  tree.insert((char*)"j", (char*)"e", 9);
  tree.insert((char*)"k", (char*)"k", 10);

  cout << "Tamanho depois: " << tree.size() << endl;

  int offset = tree.search_primary_key("h");
  cout << "O deslocamento para 'h' é: " << offset << endl;

  LinkedList<string> *list = tree.disjunctive_search("e", "g");
  cout << "Tamanho lista: " << list->size() << endl;

  for (size_t i = 0; i < list->size(); i++)
    cout << "i: " << i <<  " = " << list->at(i) << endl;

  delete list;
  */

  return 0;
}
