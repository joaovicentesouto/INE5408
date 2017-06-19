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

using namespace std;
using namespace structures;

int main(int argc, char const *argv[]) {

  KDTreeOnDisk *tree = new KDTreeOnDisk();

  char name[8][50], man[8][50];
  strcpy(name[0], "Joao");
  strcpy(name[1], "Eduarda");
  strcpy(name[2], "Jean");
  strcpy(name[3], "Jorge");
  strcpy(name[4], "Rejane");
  strcpy(name[5], "Camila");
  strcpy(name[6], "Felicity");
  strcpy(name[7], "Claudia");

  strcpy(man[0], "AAA");
  strcpy(man[1], "BBBBBBBB");
  strcpy(man[2], "CCCCCCCCCCCCC");
  strcpy(man[3], "DDDDDD");
  strcpy(man[4], "EEEEEEEEE");
  strcpy(man[5], "FFFFFF");
  strcpy(man[6], "GGGGGGGGGGGGGG");
  strcpy(man[7], "HHHHhHHHHH");

  for (size_t i = 0; i < 8; i++) {
    printf("N: %s, tam: %zu, man: %s\n", name[i], strlen(man[i]), man[i]);
    tree->insert(name[i], strlen(man[i]), man[i]);
  }

  return 0;
}
