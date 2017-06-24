#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include <algorithm>

#include <iostream>
#include <fstream>
#include <cstdio>  // para gets()
#include <sys/stat.h>

#include <typeinfo>
#include <string>
#include "./structures/linked_list.h"
#include "./binary_tree_of_lists_on_disk.h"

using namespace std;
using namespace structures;

int main(int argc, char const *argv[]) {

  BinaryTreeOfListOnDisk *tree = new BinaryTreeOfListOnDisk();

  char name[8][60];
  strcpy(name[0], "Joao");
  strcpy(name[1], "Eduarda");
  strcpy(name[2], "Jean");
  strcpy(name[3], "Jorge");
  strcpy(name[4], "Rejane");
  strcpy(name[5], "Camila");
  strcpy(name[6], "Felicity");
  strcpy(name[7], "Claudia");

  for (size_t i = 0; i < 8; i++) {
    printf("N: %s, man: %lu\n", name[i], i);
    tree->insert(name[i], i);
  }

  for (size_t i = 0; i < 10; i++) {
    printf("N: %s, man: %lu\n", name[0], i*i+10);
    tree->insert(name[0], i*i+10);
  }

  for (size_t i = 0; i < 10; i++) {
    printf("N: %s, man: %lu\n", name[4], (i%2==0? i*i+10 : i*i+13));
    tree->insert(name[4], (i%2==0? i*i+10 : i*i+13));
  }

  LinkedList<size_t> *list = tree->search(name[0]);
  printf("Search joao: %lu\n", list->size());
  while (!list->empty()) {
    printf("manp: %lu\n", list->pop_front());
  }

  delete list;
  list = tree->conjunctive_search(name[0], name[4]);
  printf("Conju joao e rejane: %lu\n", list->size());
  while (!list->empty()) {
    printf("manp: %lu\n", list->pop_front());
  }

  delete list;
  list = tree->disjunctive_search(name[0], name[4]);
  printf("Disj joao e rejane: %lu\n", list->size());
  while (!list->empty()) {
    printf("manp: %lu\n", list->pop_front());
  }



  /*char* test = tree->search_primary_key("Rejane");
  if (test != nullptr)
    cout << test << endl;
  else
    cout << "Erro" << endl;*/

  return 0;
}
