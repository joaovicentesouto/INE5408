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
#include "./structures/linked_stack.h"
#include "./structures/array_list.h"
#include "./word_handler.h"
#include "./kd_tree_on_disk.h"

using namespace std;
using namespace structures;

int main(int argc, char const *argv[]) {

  KDTreeOnDisk tree;
  WordHandler handler;

  string dir;
  LinkedList<string> *words;
  LinkedList<string> *aux;

  ifstream file("./ManPages/dlpi_fd.3dlpi.txt", ios::in);
  words = handler.treatment(file);
  cout << "Tam words: " << words->size() << endl;

  for (size_t i = 0; i < words->size(); i++) {
    dir = words->at(i);
    cout << "dlpi_fd.3dlpi -> " << dir << endl;
    tree.insert("dlpi_fd.3dlpi", dir.c_str(), 100);
  }
  cout << "Tam tree: " << tree.size() << endl;

  for (size_t i = 0; i < words->size(); i++) {
    dir = words->at(i);
    aux = tree.search_secondary_key(dir.c_str());
    cout << "tamanho achado: " << aux->size() << endl;
    cout << dir << endl;
    for (size_t j = 0; j < aux->size(); j++) {
      cout << " -> " << aux->at(j) << endl;
    }
  }

  delete words;

  return 0;
}
