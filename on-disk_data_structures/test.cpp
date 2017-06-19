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

  Node(const char* primary, const size_t secondary, char* manpage) {
    strcpy(primary_, primary);
    secondary_ = secondary;
    strcpy(manpage_, manpage);
  }

  void print() {
    cout << "P: "<< primary_ << endl;
    cout << "S: "<< secondary_ << endl;
    cout << "L: "<< left_ << endl;
    cout << "R: "<< right_ << endl;
    cout << "M: " << manpage_ << endl;
    cout << endl;
  }

  size_t size() {
    size_t aux = sizeof(primary_) + sizeof(secondary_)
                 + sizeof(left_) + sizeof(right_) + strlen(manpage_) + 10;
    return aux;
  }

  char primary_[50]{"@"};
  size_t secondary_{0u},
         left_{1u},
         right_{2u};
  char manpage_[139718]{"&"};
};

int main(int argc, char const *argv[]) {

  ifstream file("./ManPages/in.rexecd.1m.txt", ios::in | ios::binary);

  struct stat st;
  if (stat("./tree.dat", &st) != 0)
    throw std::out_of_range("Erro ao verificar tamanho do arquivo.");
  //cout << st.st_size << endl;

  char man[st.st_size];
  file.seekg(0);
  file.read(man, st.st_size);
  file.close();

  ofstream mantest("./mantest.dat", ios::out | ios::binary | ios::trunc);

  Node *tnode = new Node("in.rexecd.1m", strlen(man), man);
  cout << tnode->size() << endl;

  mantest.seekp(0);
  mantest.write(reinterpret_cast<char*>(tnode), tnode->size());
  mantest.close();

  ifstream in("./mantest.dat", ios::in | ios::binary);

  in.seekg(0);
  char pri[50];
  in.read(pri, 50);
  cout << pri << endl;

  in.seekg(sizeof(Node::primary_)+6);
  size_t tam_man;
  in.read(reinterpret_cast<char*>(&tam_man), sizeof(Node::secondary_));
  cout << tam_man << endl;

  in.seekg(sizeof(Node::primary_)+6+sizeof(size_t));
  size_t aux;
  in.read(reinterpret_cast<char*>(&aux), sizeof(Node::left_));
  cout << aux << endl;

  in.seekg(sizeof(Node::primary_)+6+sizeof(size_t)*2);
  in.read(reinterpret_cast<char*>(&aux), sizeof(Node::left_));
  cout << aux << endl;

  in.seekg(sizeof(Node::primary_)+6+sizeof(size_t)*3);
  char man_node[tam_man];
  in.read(reinterpret_cast<char*>(&man_node), tam_man);
  cout << man_node << endl;

  return 0;
}
