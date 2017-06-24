//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_BINARY_TREE_OF_LIST_H
#define STRUCTURES_BINARY_TREE_OF_LIST_H

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

class BinaryTreeOfListOnDisk {
public:
  BinaryTreeOfListOnDisk();
  ~BinaryTreeOfListOnDisk();

  void insert(const char* key, const size_t manpage);
  //void remove(const char* first_key, const char* second_key);

  //bool contains_primary(const char* primary) const;
  //bool contains_secondary(const char* secondary) const;
  bool empty() const;
  size_t size() const;
  size_t file_size() const;

  LinkedList<size_t>* search(const char* wanted) const;  //!< retorna o offset
  //LinkedList<string>* search_secondary_key(const size_t wanted) const;
  LinkedList<size_t>* conjunctive_search(const char* w1, const char* w2) const;
  LinkedList<size_t>* disjunctive_search(const char* w1, const char* w2) const;


private:
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
           next_{0u};
  };

  size_t depth_{0u},
         size_{0u};
};

BinaryTreeOfListOnDisk::BinaryTreeOfListOnDisk() {
  // Cria arquivo para a arvore ou sobreescreve um existente
  fstream tree("./secondary_tree.dat", ios::in | ios::out | ios::binary | ios::trunc);
  tree.close();
}

BinaryTreeOfListOnDisk::~BinaryTreeOfListOnDisk() {}

void BinaryTreeOfListOnDisk::insert(const char* key, const size_t manpage) {

  fstream tree("./secondary_tree.dat", ios::in | ios::out | ios::binary);
  char node_key[60];
  int compare = 1;
  size_t man_node= -1, offset = 0u, next = 0u, current = 0u, level = 0u,
         offset_left = sizeof(TreeNode::key_)+4,
         offset_right = offset_left + sizeof(size_t),
         offset_list_head = offset_right + sizeof(size_t);

  tree.seekg(0);
  while (tree.good() && size_ != 0) {
    offset = tree.tellg();

    tree.read(node_key, sizeof(TreeNode::key_));
    compare = strcmp(key, node_key);

    if (compare != 0) {  // esquerda ou direita
      current = compare < 0? offset + offset_left : offset + offset_right;

      tree.seekg(current);
      tree.read(reinterpret_cast<char*>(&next), sizeof(size_t));

      if (next == 0u) // Cheguei em um node nulo
        break;

      tree.seekg(next);

    } else { // igual tenho que só percorrer a list

      tree.seekg(offset + offset_list_head);
      tree.read(reinterpret_cast<char*>(&next), sizeof(size_t));

      while (next != 0) {
        current = next;
        tree.seekg(current);
        tree.read(reinterpret_cast<char*>(&man_node), sizeof(size_t));
        if (man_node == manpage) // ja existe
          break;
        tree.read(reinterpret_cast<char*>(&next), sizeof(size_t));
      }

      if (man_node == manpage) // ja existe
        break;

      tree.seekp(0, ios::end);
      next = tree.tellp();

      tree.seekp(current + sizeof(size_t));
      tree.write(reinterpret_cast<char*>(&next), sizeof(size_t));

      ListNode *lnode = new ListNode(manpage);
      tree.seekp(next);
      tree.write(reinterpret_cast<char*>(lnode), sizeof(ListNode));
      delete lnode;
      break;
    }
    ++level;
  }
  ++level; // Mais um level pro node nulo

  if (next == 0 && man_node != manpage) {
    tree.seekp(0, ios::end); // fim do arquivo
    next = tree.tellp();      // pega deslocamento pro filho

    TreeNode *tnode = new TreeNode(key, next + sizeof(TreeNode));
    ListNode *lnode = new ListNode(manpage);
    if (tnode == nullptr || lnode == nullptr)
      throw std::out_of_range("Full tree!");

    if (size_ != 0) {
      tree.seekp(current);    // modifica o pai
      tree.write(reinterpret_cast<char*>(&next), sizeof(size_t));
    }

    tree.seekp(next);            // adiciona o node
    tree.write(reinterpret_cast<char*>(tnode), sizeof(TreeNode));
    tree.write(reinterpret_cast<char*>(lnode), sizeof(ListNode));
    ++size_;
    delete tnode;
    delete lnode;
  }

  depth_ = level > depth_? level : depth_;
  tree.close();
}

bool BinaryTreeOfListOnDisk::empty() const {
  return size_ == 0u;
}

size_t BinaryTreeOfListOnDisk::size() const {
  return size_;
}

size_t BinaryTreeOfListOnDisk::file_size() const {
  struct stat st;
  if (stat("./secondary_tree.dat", &st) != 0)
    throw std::out_of_range("Erro ao verificar tamanho do arquivo.");
  return st.st_size;
}

LinkedList<size_t>* BinaryTreeOfListOnDisk::search(const char* wanted) const {
  // Guardar o deslocamento e nível em uma pilha quando tiver
  // que descer por dois caminhos diferentes.
  fstream tree("./secondary_tree.dat", ios::in | ios::out | ios::binary);
  LinkedList<size_t> *list = new LinkedList<size_t>();
  char node_key[60];
  int compare = 1;
  size_t man_node= -1, offset = 0u, next = 0u, current = 0u, level = 0u,
         offset_left = sizeof(TreeNode::key_)+4,
         offset_right = offset_left + sizeof(size_t),
         offset_list_head = offset_right + sizeof(size_t);

  tree.seekg(0);
  while (tree.good() && size_ != 0) {
    offset = tree.tellg();

    tree.read(node_key, sizeof(TreeNode::key_));
    compare = strcmp(wanted, node_key);

    if (compare != 0) {  // esquerda ou direita
      current = compare < 0? offset + offset_left : offset + offset_right;

      tree.seekg(current);
      tree.read(reinterpret_cast<char*>(&next), sizeof(size_t));

      if (next == 0u) // Cheguei em um node nulo
        break;

      tree.seekg(next);

    } else { // igual tenho que só percorrer a list

      tree.seekg(offset + offset_list_head);
      tree.read(reinterpret_cast<char*>(&next), sizeof(size_t));

      while (next != 0) {
        current = next;
        tree.seekg(current);
        tree.read(reinterpret_cast<char*>(&man_node), sizeof(size_t));
        list->push_back(man_node);

        tree.read(reinterpret_cast<char*>(&next), sizeof(size_t));
      }
    }
    ++level;
  }

  tree.close();
  return list;
}

LinkedList<size_t>* BinaryTreeOfListOnDisk::conjunctive_search(
                                const char* w1, const char* w2) const {
  LinkedList<size_t> *s1 = this->search(w1);
  LinkedList<size_t> *s2 = this->search(w2);

  while (!s2->empty())
    s1->insert_sorted(s2->pop_front());

  delete s2;
  return s1;
}

LinkedList<size_t>* BinaryTreeOfListOnDisk::disjunctive_search(
                                const char* w1, const char* w2) const {
  LinkedList<size_t> *s1 = search(w1);
  LinkedList<size_t> *s2 = search(w2);
  LinkedList<size_t> *list = new LinkedList<size_t>();

  size_t aux;
  while (!s2->empty()) {
    aux = s2->pop_front();
    if (s1->contains(aux))
      list->insert_sorted(aux);
  }

  delete s1;
  delete s2;
  return list;
}

/*LinkedList<string>* KDTreeOnDisk::search_secondary_key(const char* wanted) const {

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
