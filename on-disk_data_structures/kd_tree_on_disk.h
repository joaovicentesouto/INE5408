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

#include "./structures/linked_list.h"
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

  int search_primary_key(const char* wanted);  //!< retorna o offset
  LinkedList<string>* search_secondary_key(const char* wanted) const;
  LinkedList<string>* conjunctive_search(const char* w1, const char* w2) const;
  LinkedList<string>* disjunctive_search(const char* w1, const char* w2) const;

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

    void print() {
      cout << "Chave 1: " << primary_ << endl;
      cout << "Chave 2: " << secondary_ << endl;
    }

  private:
    char primary_[50]{"@"},
         secondary_[100]{"&"};
    size_t offset_{0u};
  };

  class Descent {
  public:
    Descent() {}

    Descent(const size_t offset, const size_t level) :
    offset_tree_{offset},
    level_{level}
    {}

    Descent& operator=(const Descent& other) {
        if (this != &other) { // self-assignment check expected
            this->offset_tree_ = other.offset_tree_;
            this->level_ = other.level_;
        }
        return *this;
    }

    size_t offset_tree_{0u}, level_{0u};
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

  char primary[50], secondary[100];
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

int KDTreeOnDisk::search_primary_key(const char* wanted) { // return -1 erro
  // Guardar o deslocamento e nível em uma pilha quando tiver
  // que descer por dois caminhos diferentes.
  LinkedStack<Descent> deviations; // desvios
  char primary[50];
  size_t offset, level = 0;
  int compare, offset_tree;
  bool leaf = false;

  ifstream tree("./tree.dat", std::ios_base::app | ios::binary);
  tree.seekg(0); // inicio do arquivo

  do {
    leaf = false;
    offset_tree = tree.tellg();
    //cout << offset_tree << endl; // por onde estamos indo
    tree.read(primary, sizeof(primary));

    if (primary[0] == '@') { // node nulo
      try {
        Descent desc = deviations.pop();
        tree.seekg(desc.offset_tree_);
        level = desc.level_;
        leaf = true;
        continue;
      } catch(std::out_of_range error) {
        break;  // pilha vazia
      }
    }

    compare = strcmp(wanted, primary);

    if (compare == 0) {  // achei
      tree.seekg(offset_tree+200);  // (começo+pri+sec)_pegar o offset do node
      tree.read(reinterpret_cast<char*>(&offset), sizeof(size_t));
      return offset;
    }

    if (level % 2 == 0) { // dimensao x
      if (compare < 0)
        tree.seekg(2*offset_tree + sizeof(Node)*1);  // esquerda
      else
        tree.seekg(2*offset_tree + sizeof(Node)*2);  // direita
    } else {
        tree.seekg(2*offset_tree + sizeof(Node)*1);  // esquerda
        Descent desc((2*offset_tree + sizeof(Node)*2), level+1);
        deviations.push(desc);
    }

    ++level;
  } while (!deviations.empty() || leaf || level < depth_);

  return -1;
}

LinkedList<string>* KDTreeOnDisk::search_secondary_key(const char* wanted) const {
  LinkedStack<Descent> deviations; // desvios
  LinkedList<string>* list = new LinkedList<string>();

  char primary[50], secondary[100];
  size_t offset_tree, level = 0;
  int compare;
  bool leaf = false;

  ifstream tree("./tree.dat", std::ios_base::app | ios::binary);
  tree.seekg(0); // inicio do arquivo

  do {
    leaf = false;
    offset_tree = tree.tellg();
    //cout << offset_tree << endl; // por onde estamos indo
    tree.seekg(offset_tree+sizeof(primary));
    tree.read(secondary, sizeof(secondary));

    if (secondary[0] == '&') { // node nulo
      try {
        Descent desc = deviations.pop();
        tree.seekg(desc.offset_tree_);
        level = desc.level_;
        leaf = true;
        continue;
      } catch(std::out_of_range error) {
        break;  // pilha vazia
      }
    }

    compare = strcmp(wanted, secondary);

    if (compare == 0) {  // achei
      tree.seekg(offset_tree);  // (começo+pri+sec)_pegar o offset do node
      tree.read(primary, sizeof(primary));
      list->insert_sorted(primary);
    }

    if (level % 2 == 1 && compare != 0) { // dimensao x
      if (compare < 0)
        tree.seekg(2*offset_tree + sizeof(Node)*1);  // esquerda
      else
        tree.seekg(2*offset_tree + sizeof(Node)*2);  // direita
    } else {
        tree.seekg(2*offset_tree + sizeof(Node)*1);  // esquerda
        Descent desc((2*offset_tree + sizeof(Node)*2), level+1);
        deviations.push(desc);
    }

    ++level;
  } while (!deviations.empty() || leaf || level < depth_);

  return list;
}

LinkedList<string>* KDTreeOnDisk::conjunctive_search(const char* w1,
                                                     const char* w2) const
{
  LinkedStack<Descent> deviations; // desvios
  LinkedList<string>* list = new LinkedList<string>();

  char primary[50], secondary[100];
  size_t offset_tree, level = 0;
  int compare_one, compare_two;
  bool leaf = false;

  ifstream tree("./tree.dat", std::ios_base::app | ios::binary);
  tree.seekg(0); // inicio do arquivo

  do {
    leaf = false;
    offset_tree = tree.tellg();
    //cout << offset_tree << endl; // por onde estamos indo
    tree.seekg(offset_tree+sizeof(primary));
    tree.read(secondary, sizeof(secondary));

    if (secondary[0] == '&') { // node nulo
      try {
        Descent desc = deviations.pop();
        tree.seekg(desc.offset_tree_);
        level = desc.level_;
        leaf = true;
        continue;
      } catch(std::out_of_range error) {
        break;  // pilha vazia
      }
    }

    compare_one = strcmp(w1, secondary);
    compare_two = strcmp(w2, secondary);

    if (compare_one == 0 || compare_two == 0) {  // achei
      tree.seekg(offset_tree);  // (começo+pri+sec)_pegar o offset do node
      tree.read(primary, sizeof(primary));
      list->insert_sorted(primary);
    }

    if (level % 2 == 1 && compare_one != 0 && compare_two != 0) { // dimensao x
      if (compare_one < 0 && compare_two < 0) {
        tree.seekg(2*offset_tree + sizeof(Node)*1);  // esquerda
      } else if (compare_one > 0 && compare_two > 0) {
        tree.seekg(2*offset_tree + sizeof(Node)*2);  // direita
      } else {
        tree.seekg(2*offset_tree + sizeof(Node)*1);  // esquerda
        Descent desc((2*offset_tree + sizeof(Node)*2), level+1);
        deviations.push(desc);
      }
    } else {
        tree.seekg(2*offset_tree + sizeof(Node)*1);  // esquerda
        Descent desc((2*offset_tree + sizeof(Node)*2), level+1);
        deviations.push(desc);
    }

    ++level;
  } while (!deviations.empty() || leaf || level < depth_);

  return list;
}

LinkedList<string>* KDTreeOnDisk::disjunctive_search(const char* w1,
                                                     const char* w2) const
{
  LinkedStack<Descent> deviations; // desvios
  LinkedList<string>* list_one = new LinkedList<string>();
  LinkedList<string>* list_two = new LinkedList<string>();
  LinkedList<string>* list_disj = new LinkedList<string>();

  char primary[50], secondary[100];
  size_t offset_tree, level = 0;
  int compare_one, compare_two;
  bool leaf = false;

  ifstream tree("./tree.dat", std::ios_base::app | ios::binary);
  tree.seekg(0); // inicio do arquivo

  do {
    leaf = false;
    offset_tree = tree.tellg();
    //cout << offset_tree << endl; // por onde estamos indo
    tree.seekg(offset_tree+sizeof(primary));
    tree.read(secondary, sizeof(secondary));

    if (secondary[0] == '&') { // node nulo
      try {
        Descent desc = deviations.pop();
        tree.seekg(desc.offset_tree_);
        level = desc.level_;
        leaf = true;
        continue;
      } catch(std::out_of_range error) {
        break;  // pilha vazia
      }
    }

    compare_one = strcmp(w1, secondary);
    compare_two = strcmp(w2, secondary);

    if (compare_one == 0) {  // achei pela primeira
      tree.seekg(offset_tree);  // (começo+pri+sec)_pegar o offset do node
      tree.read(primary, sizeof(primary));
      list_one->insert_sorted(primary);
    } else if (compare_two == 0) {  // achei pela segunda
      tree.seekg(offset_tree);  // (começo+pri+sec)_pegar o offset do node
      tree.read(primary, sizeof(primary));
      list_two->insert_sorted(primary);
    }

    if (level % 2 == 1 && compare_one != 0 && compare_two != 0) { // dimensao x
      if (compare_one < 0 && compare_two < 0) {
        tree.seekg(2*offset_tree + sizeof(Node)*1);  // esquerda
      } else if (compare_one > 0 && compare_two > 0) {
        tree.seekg(2*offset_tree + sizeof(Node)*2);  // direita
      } else {
        tree.seekg(2*offset_tree + sizeof(Node)*1);  // esquerda
        Descent desc((2*offset_tree + sizeof(Node)*2), level+1);
        deviations.push(desc);
      }
    } else {
        tree.seekg(2*offset_tree + sizeof(Node)*1);  // esquerda
        Descent desc((2*offset_tree + sizeof(Node)*2), level+1);
        deviations.push(desc);
    }

    ++level;
  } while (!deviations.empty() || leaf || level < depth_);

  bool cond = list_one->size() < list_two->size();
  LinkedList<string>* minor_list = cond ? list_one : list_two;
  LinkedList<string>* major_list = cond ? list_two : list_one;
  string temp;

  for (size_t i = 0; i < major_list->size(); i++) {
    temp = major_list->at(i);
    if (minor_list->contains(temp))
      list_disj->push_front(temp); // é push_front pra otimizar
  }

  return list_disj;
}

}  //  namespace structures

#endif
