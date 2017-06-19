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
    manpage_ = manpage;
  }

  void print() {
    cout << "P: "<< primary_ << endl;
    cout << "S: "<< secondary_ << endl;
    cout << "L: "<< left_ << endl;
    cout << "R: "<< right_ << endl;
    cout << "M: " << manpage_ << endl;
    cout << endl;
  }

  void print_size() {
    cout << "P: "<< sizeof(primary_) << endl;
    cout << "S: "<< sizeof(secondary_) << endl;
    cout << "L: "<< sizeof(left_) << endl;
    cout << "R: "<< sizeof(right_) << endl;
    cout << "M: " << strlen(manpage_) << endl;
    cout << endl;
  }

//private:
  char primary_[50]{"@"};
  size_t secondary_,
         left_{0u},
         right_{0u};
  char *manpage_;
};

int main(int argc, char const *argv[]) {

  ifstream file("./ManPages/in.rexecd.1m.txt", ios::in | ios::binary);

  struct stat st;
  if (stat("./tree.dat", &st) != 0)
    throw std::out_of_range("Erro ao verificar tamanho do arquivo.");
  cout << st.st_size << endl;

  char man[st.st_size];
  file.seekg(0);
  file.read(man, st.st_size);

  cout << "man: " << strlen(man) << endl;

  ofstream out("./mantest.dat", ios::out | ios::binary);
  out.write(man, strlen(man));

  Node *tnode = new Node("Nome", 100, man);
  tnode->print();
  tnode->print_size();

  Node *t2 = new Node("Aaaaa", 100, "AJHASJJSJSKAKJKLAJSKLJDkskdjalksjkldfasdfsdfsdfsdfsdfsdfs");
  t2->print();
  t2->print_size();

  return 0;
}
