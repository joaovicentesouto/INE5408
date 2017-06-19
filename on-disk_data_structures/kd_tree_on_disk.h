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

  void insert(const char* primary, const size_t secondary, char* manpage);
  //void remove(const char* first_key, const char* second_key);

  //bool contains_primary(const char* primary) const;
  //bool contains_secondary(const char* secondary) const;
  bool empty() const;
  size_t size() const;
  size_t file_size() const;

  //int search_primary_key(const char* primary);  //!< retorna o offset
  //LinkedList<string>* search_secondary_key(const size_t wanted) const;
  //LinkedList<string>* conjunctive_search(const size_t w1, const size_t w2) const;
  //LinkedList<string>* disjunctive_search(const size_t w1, const size_t w2) const;


private:
  class Node {
  public:
    Node() {}

    Node(const char* primary, const size_t secondary, char* manpage) {
      strcpy(primary_, primary);
      secondary_ = secondary;
      strcpy(manpage_, manpage);
    }

    size_t size() {
      size_t aux = sizeof(primary_) + sizeof(secondary_)
                   + sizeof(left_) + sizeof(right_) + strlen(manpage_) + 10;
      return aux;
    }

    char primary_[50]{"@"};
    size_t secondary_{0u},
           left_{0u},
           right_{0u};
    char manpage_[139718]{"&"};
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
                          const size_t key_2, char* manpage) {
  fstream tree("./tree.dat", ios::in | ios::out | ios::binary);

  char node_key_1[50];
  size_t node_key_2;
  int compare = 1;
  size_t offset = 0u, son = 0u, level = 0u, father_son = 0u,
         offset_secondary = sizeof(Node::primary_)+6,
         offset_left = offset_secondary + sizeof(size_t),
         offset_right = offset_left + sizeof(size_t),
         offset_manpage = offset_right + sizeof(size_t);

  tree.seekg(0);
  while (tree.good() && size_ != 0) {
    offset = tree.tellg();

    if (level % 2 == 0) {
      tree.read(node_key_1, sizeof(Node::primary_));
      compare = strcmp(key_1, node_key_1);
    } else {
      tree.seekg(offset + offset_secondary);
      tree.read(reinterpret_cast<char*>(&node_key_2), sizeof(size_t));
      compare = key_2 - node_key_2;
    }

    if (compare != 0) {  // esquerda ou direita
      father_son = compare < 0? offset + offset_left : offset + offset_right;

      tree.seekg(father_son);
      tree.read(reinterpret_cast<char*>(&son), sizeof(size_t));

      if (son == 0u) // Cheguei em um node nulo
        break;

      tree.seekg(son);

    } else { // igual

      if (level % 2 == 0) {
        tree.seekg(offset + offset_secondary);
        tree.read(reinterpret_cast<char*>(&node_key_2), sizeof(size_t));
        compare = key_2 - node_key_2;
      } else {
        tree.seekg(offset);
        tree.read(node_key_1, sizeof(Node::primary_));
        compare = strcmp(key_1, node_key_1);
      }

      if (compare == 0) // node ja existe
        break;

      father_son = compare < 0? offset + offset_left : offset + offset_right;
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

/*int KDTreeOnDisk::search_primary_key(const char* wanted) { // return -1 erro
  // Guardar o deslocamento e nível em uma pilha quando tiver
  // que descer por dois caminhos diferentes.

  LinkedStack<Route> routes; // desvios
  char primary[50];
  int compare = 1;
  size_t level = 0u, son = 0u, offset= 0u,
         offset_left = 50+60+2,
         offset_right = offset_left + sizeof(size_t),
         offset_manpage = offset_right + sizeof(size_t);

  ifstream tree("./tree.dat", std::ios_base::app | ios::binary);
  tree.seekg(0); // inicio do arquivo

  while (tree.good()) {
    offset = tree.tellg();

    tree.read(primary, sizeof(primary));
    compare = strcmp(wanted, primary);

    if (compare == 0) {  // achei
      // le offset da manpage
      tree.seekg(offset + offset_manpage);
      tree.read(reinterpret_cast<char*>(&offset), sizeof(size_t));
      return (int) offset;
    }

    if (level % 2 == 0) {  // dimensao x, divide árvore
      if (compare < 0)
        son = offset + offset_left;
      else
        son = offset + offset_right;

      tree.seekg(son);
      tree.read(reinterpret_cast<char*>(&son), sizeof(size_t));

    } else {               // dimensao y, vai pros dois lados
      tree.seekg(offset + offset_right);
      tree.read(reinterpret_cast<char*>(&son), sizeof(size_t));
      if (son != 0) {
        Route way(son, level+1);
        routes.push(way);
      }

      tree.seekg(offset + offset_left);
      tree.read(reinterpret_cast<char*>(&son), sizeof(size_t));
    }

    if (son != 0) { // próximo node é nulo
      tree.seekg(son);  // próxima posição
      ++level;
    } else {
      try {
        Route way = routes.pop();
        tree.seekg(way.offset_tree_);
        level = way.level_;
      } catch(std::out_of_range error) {
        break;  // pilha vazia
      }
    }
  }

  return -1; // não achou
}

LinkedList<string>* KDTreeOnDisk::search_secondary_key(const char* wanted) const {

  LinkedStack<Route> routes; // desvios
  LinkedList<string>* list = new LinkedList<string>();

  char primary[50], secondary[60];
  int compare = 1;
  size_t level = 0u, son = 0u, offset= 0u,
         offset_left = 50+60+2,
         offset_right = offset_left + sizeof(size_t);

  ifstream tree("./tree.dat", std::ios_base::app | ios::binary);
  tree.seekg(0); // inicio do arquivo

  while (tree.good() || !routes.empty()) {
    offset = tree.tellg();

    tree.seekg(offset + sizeof(primary));
    tree.read(secondary, sizeof(secondary));
    //cout << "Todas as chave 2: " << secondary << endl;
    compare = strcmp(wanted, secondary);

    if (compare == 0) {  // achei
      // Pega chave primaria
      tree.seekg(offset);
      tree.read(primary, sizeof(primary));
      //cout << "Busca in achada: " << primary << endl;
      list->insert_sorted(primary);
    }

    if (level % 2 == 1) {  // dimensao y, divide árvore
      if (compare < 0)
        son = offset + offset_left;
      else
        son = offset + offset_right;

      tree.seekg(son);
      tree.read(reinterpret_cast<char*>(&son), sizeof(size_t));

    } else {               // dimensao x, vai pros dois lados
      tree.seekg(offset + offset_right);
      tree.read(reinterpret_cast<char*>(&son), sizeof(size_t));
      if (son != 0) {
        Route way(son, level+1);
        routes.push(way);
      }

      tree.seekg(offset + offset_left);
      tree.read(reinterpret_cast<char*>(&son), sizeof(size_t));
    }

    if (son != 0) { // próximo node é nulo
      tree.seekg(son);  // próxima posição
      ++level;
    } else {
      try {
        Route way = routes.pop();
        tree.seekg(way.offset_tree_);
        level = way.level_;
      } catch(std::out_of_range error) {
        break;  // pilha vazia
      }
    }
  }

  return list;
}

LinkedList<string>* KDTreeOnDisk::conjunctive_search(const char* w1,
                                                     const char* w2) const
{
  LinkedStack<Route> routes; // desvios
  LinkedList<string>* list = new LinkedList<string>();

  char primary[50], secondary[60];
  int compare_one = 1, compare_two = 1;
  size_t level = 0u, son = 0u, offset= 0u,
         offset_left = 50+60+2,
         offset_right = offset_left + sizeof(size_t);

  ifstream tree("./tree.dat", std::ios_base::app | ios::binary);
  tree.seekg(0); // inicio do arquivo

  while (tree.good()) {
    offset = tree.tellg();

    tree.seekg(offset + sizeof(primary));
    tree.read(secondary, sizeof(secondary));
    compare_one = strcmp(w1, secondary);
    compare_two = strcmp(w2, secondary);

    if (compare_one == 0 || compare_two == 0) {  // achei
      // le offset da manpage
      tree.seekg(offset);
      tree.read(primary, sizeof(primary));
      list->insert_sorted(primary);
    }

    if (level % 2 == 1 && compare_one != 0 && compare_two != 0) {  // dimensao y, divide árvore
      if (compare_one < 0 && compare_two < 0) {
        son = offset + offset_left;
      } else if (compare_one > 0 && compare_two > 0) {
        son = offset + offset_right;
      } else {  // um == vai pros dois lados
        tree.seekg(offset + offset_right);
        tree.read(reinterpret_cast<char*>(&son), sizeof(size_t));
        if (son != 0) {
          Route way(son, level+1);
          routes.push(way);
        }
        son = offset + offset_left;
      }

      tree.seekg(son);
      tree.read(reinterpret_cast<char*>(&son), sizeof(size_t));

    } else {               // dimensao x, vai pros dois lados
      tree.seekg(offset + offset_right);
      tree.read(reinterpret_cast<char*>(&son), sizeof(size_t));
      if (son != 0) {
        Route way(son, level+1);
        routes.push(way);
      }

      tree.seekg(offset + offset_left);
      tree.read(reinterpret_cast<char*>(&son), sizeof(size_t));
    }

    if (son != 0) { // próximo node é nulo
      tree.seekg(son);  // próxima posição
      ++level;
    } else {
      try {
        Route way = routes.pop();
        tree.seekg(way.offset_tree_);
        level = way.level_;
      } catch(std::out_of_range error) {
        break;  // pilha vazia
      }
    }
  }

  return list;
}

LinkedList<string>* KDTreeOnDisk::disjunctive_search(const char* w1,
                                                     const char* w2) const
{
  LinkedStack<Route> routes; // desvios
  LinkedList<string>* list_one = new LinkedList<string>();
  LinkedList<string>* list_two = new LinkedList<string>();
  LinkedList<string>* list_disj = new LinkedList<string>();

  char primary[50], secondary[60];
  int compare_one = 1, compare_two = 1;
  size_t level = 0u, son = 0u, offset= 0u,
         offset_left = 50+60+2,
         offset_right = offset_left + sizeof(size_t);

  ifstream tree("./tree.dat", std::ios_base::app | ios::binary);
  tree.seekg(0); // inicio do arquivo

  while (tree.good()) {
    offset = tree.tellg();

    tree.seekg(offset + sizeof(primary));
    tree.read(secondary, sizeof(secondary));
    compare_one = strcmp(w1, secondary);
    compare_two = strcmp(w2, secondary);

    if (compare_one == 0) {  // achei
      tree.seekg(offset);
      tree.read(primary, sizeof(primary));
      list_one->insert_sorted(primary);
    } else if (compare_two == 0) {
      // le offset da manpage
      tree.seekg(offset);
      tree.read(primary, sizeof(primary));
      list_two->insert_sorted(primary);
    }

    if (level % 2 == 1 && compare_one != 0 && compare_two != 0) {  // dimensao y, divide árvore
      if (compare_one < 0 && compare_two < 0) {
        son = offset + offset_left;
      } else if (compare_one > 0 && compare_two > 0) {
        son = offset + offset_right;
      } else {  // um == vai pros dois lados
        tree.seekg(offset + offset_right);
        tree.read(reinterpret_cast<char*>(&son), sizeof(size_t));
        if (son != 0) {
          Route way(son, level+1);
          routes.push(way);
        }
        son = offset + offset_left;
      }

      tree.seekg(son);
      tree.read(reinterpret_cast<char*>(&son), sizeof(size_t));

    } else {               // dimensao x, vai pros dois lados
      tree.seekg(offset + offset_right);
      tree.read(reinterpret_cast<char*>(&son), sizeof(size_t));
      if (son != 0) {
        Route way(son, level+1);
        routes.push(way);
      }

      tree.seekg(offset + offset_left);
      tree.read(reinterpret_cast<char*>(&son), sizeof(size_t));
    }

    if (son != 0) { // próximo node é nulo
      tree.seekg(son);  // próxima posição
      ++level;
    } else {
      try {
        Route way = routes.pop();
        tree.seekg(way.offset_tree_);
        level = way.level_;
      } catch(std::out_of_range error) {
        break;  // pilha vazia
      }
    }
  }

  bool cond = list_one->size() < list_two->size();
  LinkedList<string>* minor_list = cond ? list_one : list_two;
  LinkedList<string>* major_list = cond ? list_two : list_one;

  string temp;
  for (size_t i = 0; i < major_list->size(); i++) {
    temp = major_list->at(i);
    if (minor_list->contains(temp))
      list_disj->insert_sorted(temp);
  }

  delete list_one;
  delete list_two;

  return list_disj;
}

*/

}  //  namespace structures

#endif
