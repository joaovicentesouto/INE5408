#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include <algorithm>

#include <iostream>
#include <fstream>
#include <cstdio>  // para gets()
#include <sys/stat.h>

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
  tree.insert((char*)"f", (char*)"f", 5);
  tree.insert((char*)"h", (char*)"h", 6);
  tree.insert((char*)"a", (char*)"a", 7);
  tree.insert((char*)"i", (char*)"i", 8);

  cout << "Tamanho depois: " << tree.size() << endl;

  try {
    size_t offset = tree.search_primary_key("i");
    cout << "O deslocamento é: " << offset << endl;
  } catch (std::out_of_range error) {
    cout << error.what() << endl;
  }

  return 0;
}
