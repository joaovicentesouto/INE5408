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

class TreeNode {
public:
  TreeNode() {}

  explicit TreeNode(const char* key) {
    strcpy(key_, key);
  }

  TreeNode(const char* key, const size_t list_head) {
    strcpy(key_, key);
    list_head_ = list_head;
  }

  char key_[60]{"@"};
  size_t left_{0u},
         right_{0u},
         list_head_{0u};
};

class ListNode {
public:
  ListNode() {}

  ListNode(const size_t manpage) :
  manpage_{manpage}
  {}

  size_t manpage_{0u},
         next{0u};
};

int main(int argc, char const *argv[]) {

  //ifstream file("./ManPages/in.rexecd.1m.txt", ios::in | ios::binary);
  ofstream binary("./secondary_tree.dat", ios::out | ios::binary | ios::trunc);

  /*struct stat st;
  if (stat("./secondary_tree.dat", &st) != 0)
    throw std::out_of_range("Erro ao verificar tamanho do arquivo.");

  char man[st.st_size];
  file.seekg(0);
  file.read(man, st.st_size);
  file.close();*/
  char key[60];
  size_t aux, offset = 0;
  size_t list = offset + sizeof(TreeNode);

  TreeNode *t1 = new TreeNode("in.rexecd.1m", list);
  ListNode *l1 = new ListNode(100);

  binary.seekp(offset);
  binary.write(reinterpret_cast<char*>(t1), sizeof(TreeNode));
  binary.seekp(list);
  binary.write(reinterpret_cast<char*>(l1), sizeof(ListNode));

  //TreeNode *t2 = new TreeNode("in.rexecd.1m", sizeof(TreeNode));

  binary.close();

  ifstream in("./secondary_tree.dat", ios::in | ios::binary);

  in.seekg(0);
  in.read(key, sizeof(key));
  cout << key << endl;

  in.seekg(sizeof(TreeNode::key_)+4);
  in.read(reinterpret_cast<char*>(&aux), sizeof(size_t));
  cout << aux << endl;
  in.read(reinterpret_cast<char*>(&aux), sizeof(size_t));
  cout << aux << endl;
  in.read(reinterpret_cast<char*>(&aux), sizeof(size_t));
  cout << aux << endl;

  // desloc. manpage
  in.seekg(aux);
  in.read(reinterpret_cast<char*>(&aux), sizeof(size_t));
  cout << aux << endl;
  // next
  in.read(reinterpret_cast<char*>(&aux), sizeof(size_t));
  cout << aux << endl;

  in.close();

  return 0;
}
