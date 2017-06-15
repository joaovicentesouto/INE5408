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
    }

  private:
    char primary_[50]{"@@"},
         secondary_[60]{"&&"};
    size_t left_{0u},
           right_{0u},
           manpage_{0u};
  };

  class Route {
  public:
    Route() {}

    Route(const size_t offset, const size_t level) :
    offset_tree_{offset},
    level_{level}
    {}

    Route& operator=(const Route& other) {
        if (this != &other) { // self-assignment check expected
            this->offset_tree_ = other.offset_tree_;
            this->level_ = other.level_;
        }
        return *this;
    }

    size_t offset_tree_{0u}, level_{0u};
  };

  //void new_level(const size_t level);

  size_t depth_{0u}, size_{0u};
};

KDTreeOnDisk::KDTreeOnDisk() {
  // Cria arquivo para a arvore ou sobreescreve um existente
  fstream tree("./tree.dat", ios::in | ios::out | ios::binary | ios::trunc);
  tree.close();
}

KDTreeOnDisk::~KDTreeOnDisk() {}

void KDTreeOnDisk::insert(const char* key_1,
                          const char* key_2,
                          const size_t manpage) {
  fstream tree("./tree.dat", ios::in | ios::out | ios::binary);

  char node_key[60];
  int compare = 1;
  size_t offset = 0u, son = 0u, level = 0u, father_son = 0u,
         offset_left = 50+60,
         offset_right = offset_left + sizeof(size_t);

  tree.seekg(0);
  while (tree.good() && size_ != 0) {
    offset = tree.tellg();

    if (level % 2 == 0) {
      tree.read(node_key, 50*sizeof(char));
      compare = strcmp(node_key, key_1);
    } else {
      tree.seekg(offset);
      tree.read(node_key, 60*sizeof(char));
      compare = strcmp(node_key, key_2);
    }

    if (compare != 0) {  // esquerda ou direita

      father_son = compare > 0? offset + offset_left : offset + offset_right;
      tree.seekg(father_son);
      tree.read(reinterpret_cast<char*>(&son), sizeof(size_t));

      if (son == 0u) // Cheguei em um node nulo
        break;

      tree.seekg(son);

    } else { // igual

      if (level % 2 == 0) {
        tree.read(node_key, 60*sizeof(char));
        compare = strcmp(node_key, key_2);
      } else {
        tree.read(node_key, 50*sizeof(char));
        compare = strcmp(node_key, key_1);
      }

      if (compare == 0) // node ja existe
        break;

      father_son = compare > 0? offset + offset_left : offset + offset_right;
      tree.seekg(father_son);
      tree.read(reinterpret_cast<char*>(&son), sizeof(size_t));

      if (son == 0u) // cheguei num node nulo
        break;

      tree.seekg(son);
    }
    ++level;
  }
  ++level; // Mais um level pro node nulo

  if (compare != 0) {
    // Se cheguei aqui é pq vou adicionar
    Node *tnode = new Node(key_1, key_2, manpage);
    if (tnode == nullptr)
      throw std::out_of_range("Full tree!");

    tree.seekp(0, ios::end); // fim do arquivo
    son = tree.tellp();      // pega deslocamento pro filho

    if (size_ != 0) {
      tree.seekp(father_son);         // modifica o pai
      tree.write(reinterpret_cast<char*>(&son), sizeof(size_t));
    }

    tree.seekp(son);            // adiciona o node
    tree.write(reinterpret_cast<char*>(tnode), sizeof(Node));
    ++size_;
    delete tnode;
  }

  depth_ = level > depth_? level : depth_;
  tree.close();
  //new_level(level);
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
  if (empty())
    throw std::out_of_range("Árvore vazia.");
  // Guardar o deslocamento e nível em uma pilha quando tiver
  // que descer por dois caminhos diferentes.

  /*char node_key[60];
  int compare = 1;
  size_t offset = 0u, son = 0u, level = 0u, father_son = 0u,
         offset_left = 50+60,
         offset_right = offset_left + sizeof(size_t);*/

  LinkedStack<Route> routes; // desvios
  char primary[50];
  size_t level = 0, offset;
  int compare = 1, offset_tree = -1;
  bool leaf = 0;

  ifstream tree("./tree.dat", std::ios_base::app | ios::binary);
  tree.seekg(0); // inicio do arquivo

  do {
    leaf = false;
    offset_tree = tree.tellg();
    //cout << offset_tree << endl; // por onde estamos indo
    tree.read(primary, sizeof(primary));

    if (primary[0] == '@') { // node nulo
      try {
        Route way = routes.pop();
        tree.seekg(way.offset_tree_);
        level = way.level_;
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
        Route way((2*offset_tree + sizeof(Node)*2), level+1);
        routes.push(way);
    }

    ++level;
  } while (!routes.empty() || leaf || level < depth_);

  return -1; // não achou
}

LinkedList<string>* KDTreeOnDisk::search_secondary_key(const char* wanted) const {
  LinkedStack<Route> routes; // desvios
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
        Route way = routes.pop();
        tree.seekg(way.offset_tree_);
        level = way.level_;
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
        Route way((2*offset_tree + sizeof(Node)*2), level+1);
        routes.push(way);
    }

    ++level;
  } while (!routes.empty() || leaf || level < depth_);

  return list;
}

LinkedList<string>* KDTreeOnDisk::conjunctive_search(const char* w1,
                                                     const char* w2) const
{
  LinkedStack<Route> routes; // desvios
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
        Route way = routes.pop();
        tree.seekg(way.offset_tree_);
        level = way.level_;
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
        Route way((2*offset_tree + sizeof(Node)*2), level+1);
        routes.push(way);
      }
    } else {
        tree.seekg(2*offset_tree + sizeof(Node)*1);  // esquerda
        Route way((2*offset_tree + sizeof(Node)*2), level+1);
        routes.push(way);
    }

    ++level;
  } while (!routes.empty() || leaf || level < depth_);

  return list;
}

LinkedList<string>* KDTreeOnDisk::disjunctive_search(const char* w1,
                                                     const char* w2) const
{
  LinkedStack<Route> routes; // desvios
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
        Route way = routes.pop();
        tree.seekg(way.offset_tree_);
        level = way.level_;
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
        Route way((2*offset_tree + sizeof(Node)*2), level+1);
        routes.push(way);
      }
    } else {
        tree.seekg(2*offset_tree + sizeof(Node)*1);  // esquerda
        Route way((2*offset_tree + sizeof(Node)*2), level+1);
        routes.push(way);
    }

    ++level;
  } while (!routes.empty() || leaf || level < depth_);

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
