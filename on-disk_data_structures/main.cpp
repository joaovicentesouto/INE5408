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

  cout << "Tamanho antes: " << tree.size() << endl;

  tree.insert((char*)"e", (char*)"e", 0);
  tree.insert((char*)"c", (char*)"c", 1);
  tree.insert((char*)"g", (char*)"g", 2);
  tree.insert((char*)"b", (char*)"b", 3);
  tree.insert((char*)"d", (char*)"d", 4);
  tree.insert((char*)"f", (char*)"g", 5);
  tree.insert((char*)"h", (char*)"h", 6);
  tree.insert((char*)"a", (char*)"a", 7);
  tree.insert((char*)"i", (char*)"g", 8);
  tree.insert((char*)"j", (char*)"a", 9);
  tree.insert((char*)"k", (char*)"b", 10);

  cout << "Tamanho depois: " << tree.size() << endl;

  int offset = tree.search_primary_key("k");
  cout << "O deslocamento é: " << offset << endl;

  LinkedList<string> *list = tree.search_secondary_key("g");
  cout << "Tamanho lista: " << list->size() << endl;

  for (size_t i = 0; i < list->size(); i++)
    cout << "i: " << i <<  " = " << list->at(i) << endl;

  return 0;
}
