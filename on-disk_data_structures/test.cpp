#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include <algorithm>

#include <iostream>
#include <fstream>
#include <cstdio>  // para gets()
#include <sys/stat.h>

#include <typeinfo>
#include <string>

using namespace std;

class Node {
public:
  Node() {}

  Node(const char* primary, const char* secondary, const size_t manpage) {
    strcpy(primary_, primary);
    strcpy(secondary_, secondary);
    manpage_ = manpage;
  }

  void print() {
    cout << "Chave 1: " << primary_ << endl;
    cout << "Chave 2: " << secondary_ << endl;
    cout << "Filho esquerda: " << left_ << endl;
    cout << "Filho direita: " << right_ << endl;
    cout << "Manpage: " << manpage_ << endl;
  }

//private:
  char primary_[50]{"@"},
       secondary_[60]{"&"};
  size_t left_{1u},
         right_{2u},
         manpage_{3u};
};

int main(int argc, char const *argv[]) {

  fstream file("./teste.dat", ios::in | ios::out | ios::binary | ios::trunc);

  Node no((char*)"A", (char*)"B", 10);
  //no.print();
  printf("%lu\n", sizeof(no));

  file.write(reinterpret_cast<char*>(&no), sizeof(no));

  file.seekg(ios::beg);
  char pri[sizeof(Node::primary_)];
  file.read(pri, sizeof(Node::primary_));
  printf("%s\n", pri);

  char sec[sizeof(Node::secondary_)];
  file.seekg(sizeof(Node::primary_));
  file.read(sec, sizeof(Node::secondary_));
  printf("%s\n", sec);

  file.seekg(0);
  Node ddd;
  file.read(reinterpret_cast<char*>(&ddd), sizeof(Node));
  ddd.print();
  return 0;
}
