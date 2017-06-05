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

  tree.insert((char*)"c", (char*)"c", 0);
  tree.insert((char*)"c", (char*)"d", 1);
  tree.insert((char*)"d", (char*)"a", 2);
  tree.insert((char*)"a", (char*)"b", 3);
  tree.insert((char*)"a", (char*)"a", 4);
  tree.insert((char*)"b", (char*)"c", 5);
  tree.insert((char*)"b", (char*)"d", 6);
  tree.insert((char*)"b", (char*)"b", 7);

  cout << "Tamanho depois: " << tree.size() << endl;

  return 0;
}
