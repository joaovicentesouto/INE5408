//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_KD_TREE_H
#define STRUCTURES_KD_TREE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include <algorithm>
#include <cmath> // pow

#include <iostream>
#include <fstream>
#include <cstdio>  // para gets()
#include <sys/stat.h>

#include "./structures/linked_stack.h"

using namespace std;

namespace structures {

class KDTreeOnDisk {
public:
  KDTreeOnDisk();
  ~KDTreeOnDisk();

  void insert(const char* first_key, const char* second_key, const size_t offset);
  //void remove(const char* first_key, const char* second_key);

  //bool contains_primary(const char* primary) const;
  //bool contains_secondary(const char* secondary) const;
  bool empty() const;
  size_t size() const;
  size_t file_size() const;

  size_t search_primary_key(const char* wanted);  //!< retorna o offset
  //ArrayList<T> search_secondary_key(const char* wanted) const;
  //ArrayList<T> conjunction_search(const char* w1, const char* w2) const;
  //ArrayList<T> disjunction_search(const char* w1, const char* w2) const;

  //ArrayList<T> pre_order() const;
  //ArrayList<T> in_order() const;
  //ArrayList<T> post_order() const;

private:
  class Node {
  public:
    Node() {}

    Node(const char* primary, const char* secondary, const size_t offset) {
      strcpy(primary_, primary);
      strcpy(secondary_, secondary);
      offset_ = offset;
    }

    int compare_primary_key(const char* another_key) {
      return strcmp(primary_, another_key);
    }

    int compare_secondary_key(const char* another_key) {
      return strcmp(secondary_, another_key);
    }

    void print() {
      cout << "Chave 1: " << primary_ << endl;
      cout << "Chave 2: " << secondary_ << endl;
    }

  private:
    char primary_[100]{"@"},
         secondary_[100]{"&"};
    size_t offset_{0u};
  };

  void new_level(const size_t level);

  size_t depth_{0u}, size_{0u};
};

KDTreeOnDisk::KDTreeOnDisk() {
  // Cria arquivo para a arvore ou sobreescreve um existente
  fstream tree("./tree.dat", ios::in | ios::out | ios::binary | ios::trunc);
  Node empty;
  tree.write(reinterpret_cast<char*>(&empty), sizeof(Node));
  tree.close();
}

KDTreeOnDisk::~KDTreeOnDisk() {}

void KDTreeOnDisk::insert(const char* key_1,
                          const char* key_2,
                          const size_t offset) {
  fstream tree("./tree.dat", ios::in | ios::out | ios::binary);

  char primary[100], secondary[100];
  int compare_x = 0, compare_y = 0;
  size_t offset_tree = 0u, direction, level = 0u;

  tree.seekg(0);
  while (tree.good()) {
    offset_tree = tree.tellg();

    tree.read(primary, sizeof(primary));
    tree.read(secondary, sizeof(secondary));
    tree.seekp(offset_tree);
    //cout << "p: " << primary << " s: " << secondary << endl;

    if (primary[0] == '@') { // inserindo
      Node *tnode = new Node(key_1, key_2, offset);
      if (tnode == nullptr)
        throw std::out_of_range("Full tree!");

      tree.write(reinterpret_cast<char*>(tnode), sizeof(Node));
      ++size_;
      delete tnode;

      break;
    }

    compare_x = strcmp(key_1, primary);
    compare_y = strcmp(key_2, secondary);

    if (compare_x == 0 && compare_y == 0) // node ja existe
      break;

    if ((level % 2) == 0) // 1ª dimensão
      direction = compare_x < 0 || (compare_x == 0 && compare_y < 0)? 1 : 2;
    else // 2ª dimensão
      direction = compare_y < 0 || (compare_y == 0 && compare_x < 0)? 1 : 2;

    tree.seekg(2*offset_tree + sizeof(Node)*direction);
    ++level;
  }
  tree.close();
  new_level(level);
}

void KDTreeOnDisk::new_level(const size_t level) {
  if (level == depth_) {

    ofstream tree("./tree.dat", std::ios_base::app | ios::binary);
    tree.seekp((pow(2,(depth_+1))-1)*sizeof(Node));

    Node tnode;
    for (size_t i = 0; i < pow(2,(depth_+1)); ++i)
      tree.write(reinterpret_cast<char*>(&tnode), sizeof(tnode));

    depth_++;
  }
}

bool KDTreeOnDisk::empty() const {
  return size_ == 0u;
}

size_t KDTreeOnDisk::size() const {
  return size_;
}

size_t KDTreeOnDisk::file_size() const {
  struct stat st;
  if (stat("./tree.dat", &st) != 0)
    throw std::out_of_range("Erro ao verificar tamanho do arquivo.");
  return st.st_size;
}

size_t search_primary_key(const char* wanted) {
  // Guardar o deslocamento (e a profundidade???) em uma pilha quando tiver
  // que descer por dois caminhos diferentes, sem recursividade, sem back-tracking
  LinkedStack<size_t> deviations; // desvios
  char primary[100], secondary[100];
  size_t offset;
  int compare;

  ifstream tree("./tree.dat", std::ios_base::app | ios::binary);

  deviations.push(0u); // ???

  do {
    offset = deviations.pop();
    tree.seekg("...");
    tree.read(primary, sizeof(primary));
    compare = strcmp(primary, wanted);

    if (compare == 0) {
      tree.seekg("...");
      tree.read(offset, sizeof(size_t));
      return offset;
    }

    if (profundidade % 2 == 0) { // dimensao x
      // vai para um lado apenas
    } else {
      // tem que ir pros dois
    }

    profundidade++;
    deviations.push("..."); // se nao for folha
  } while (!deviations.empty());

  return 0;
}

}  //  namespace structures

#endif
