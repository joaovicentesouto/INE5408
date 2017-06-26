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

//! Classe BinaryTreeOfListOnDisk
/*! Árvore binária de listas encadeadas.
 *  Ideia: Chave secundária é o discriminante e cada node está
 *  associado a uma lista de todos os deslocamentos na árvore
 *  primária.
 *
 *  \author João Vicente Souto.
 *  \since 20/06/17
 *  \version 1.0
 */
class BinaryTreeOfListOnDisk {
public:
  BinaryTreeOfListOnDisk();  // Construtor
  ~BinaryTreeOfListOnDisk();  // Destrutor

  void insert(const char* key, const size_t manpage);  // Inserir
  //void remove(const char* key, const size_t manpage);

  bool empty() const;  // Teste de vazio
  size_t size() const;  // Tamanho da árvore
  size_t depth() const;  // Profundidade da árvore
  size_t file_size() const;  // Tamanho do arquivo da árvore

  LinkedList<size_t>* search(const char* wanted) const;  // Busca uma chave
  LinkedList<size_t>* conjunctive_search(const char* w1, const char* w2) const;  // Busca conjunto de duas chaves
  LinkedList<size_t>* disjunctive_search(const char* w1, const char* w2) const;  // Busca disjunto de duas chaves

private:
  //! Classe TreeNode
  /*! Node da árvore
   *
   *  \author João Vicente Souto.
   *  \since 20/06/17
   *  \version 1.0
   */
  class TreeNode {
  public:
    //! Construtor
    /*! Sem parâmetros
     *  \sa TreeNode(const char* key), TreeNode(const char* key, const size_t list_head)
     */
    TreeNode() {}

    //! Construtor
    /*! Com parâmetros, só a chave
     *  \sa TreeNode(), TreeNode(const char* key, const size_t list_head)
     */
    explicit TreeNode(const char* key) {
      strcpy(key_, key);
    }

    //! Construtor
    /*! Com parâmetros, chave e cabeça da lista
     *  \sa TreeNode(const char* key), TreeNode()
     */
    TreeNode(const char* key, const size_t list_head) {
      strcpy(key_, key);
      list_head_ = list_head;
    }

    //! Destrutor
    /*! Destrutor padrão, não tem nada alocado dinâmicamente.
     */
    ~TreeNode() {}

    char key_[60]{"@"};  //!< Chave
    size_t left_{0u},  //!< Node da esquerda
           right_{0u},  //!< Node da direita
           list_head_{0u};  //!< Cabeça da lista
  };

  //! Classe ListNode
  /*! Node da lista
   *
   *  \author João Vicente Souto.
   *  \since 20/06/17
   *  \version 1.0
   */
  class ListNode {
  public:
    //! Construtor
    /*! Sem parâmetros
     *  \sa ListNode(const size_t manpage), ListNode(const size_t manpage, const size_t next)
     */
    ListNode() {}

    //! Construtor
    /*! Com parametros, deslocamento da manpage
     *  \sa TreeNode(), TreeNode(const char* key, const size_t list_head)
     */
    explicit ListNode(const size_t manpage) :
    manpage_{manpage}
    {}

    //! Construtor
    /*! Com parametros, deslocamento e próximo da lista
     *  \sa TreeNode(const char* key), TreeNode()
     */
    ListNode(const size_t manpage, const size_t next) :
    manpage_{manpage},
    next_{next}
    {}

    //! Destrutor
    /*! Destrutor padrão, não tem nada alocado dinâmicamente.
     */
    ~ListNode() {}

    size_t manpage_{0u},  //!< Deslocamento na árvore primária
           next_{0u};  //!< Próximo da lista
  };

  size_t depth_{0u},  //!< Profundidade
         size_{0u};  //!< Quantidade de nodes
};

//! Construtor
/*! Sem parâmetros, limpa arquivo da arvore
 *  \sa ~BinaryTreeOfListOnDisk()
 */
BinaryTreeOfListOnDisk::BinaryTreeOfListOnDisk() {
  // Cria arquivo para a arvore ou sobreescreve um existente
  fstream tree("./secondary_tree.dat", ios::in | ios::out | ios::binary | ios::trunc);
  tree.close();
}

//! Destrutor
/*! Destrutor padrão, não tem nada alocado dinâmicamente.
 *  \sa BinaryTreeOfListOnDisk()
 */
BinaryTreeOfListOnDisk::~BinaryTreeOfListOnDisk() {}

//! Insere
/*! Recebe chave secundária e deslocamento na árvore primária.
 *  \param char* palavra secundária
 *  \param size_t deslocamento referente a manpage
 */
void BinaryTreeOfListOnDisk::insert(const char* key, const size_t manpage) {

  fstream tree("./secondary_tree.dat", ios::in | ios::out | ios::binary);
  char node_key[60];
  int compare = 1;
  size_t aux = 0, offset = 0u, next = 0u, current = 0u, level = 0u,
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

      tree.seekp(0, ios::end);
      aux = tree.tellp();

      tree.seekp(offset + offset_list_head);
      tree.write(reinterpret_cast<char*>(&aux), sizeof(size_t));

      ListNode *lnode = new ListNode(manpage, next);
      tree.seekp(aux);
      tree.write(reinterpret_cast<char*>(lnode), sizeof(ListNode));
      delete lnode;
      break;
    }
    ++level;
  }
  ++level; // Mais um level pro node nulo

  if (next == 0) {
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

//! Busca por uma chave secundária
/*! Busca todas as manpage que tenham esta chave secundária.
 *  \param char* chave secundária
 *  \return LinkedList<size_t> lista dos deslocamentos
 */
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

//! Busca conjuntiva
/*! Busca todas as manpage que tenham ou das duas, ou ambas.
 *  \param char* primeira chave secundária
 *  \param char* segunda chave secundária
 *  \return LinkedList<size_t> lista dos deslocamentos
 */
LinkedList<size_t>* BinaryTreeOfListOnDisk::conjunctive_search(
                                const char* w1, const char* w2) const {
  LinkedList<size_t> *s1 = this->search(w1);
  LinkedList<size_t> *s2 = this->search(w2);

  while (!s2->empty())
    s1->insert_sorted(s2->pop_front());

  delete s2;
  return s1;
}

//! Busca disjuntiva
/*! Busca todas as manpage que tenham ambas as chaves.
 *  \param char* primeira chave secundária
 *  \param char* segunda chave secundária
 *  \return LinkedList<size_t> lista dos deslocamentos
 */
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

//! Teste de vazio
/*! Retorna o teste se a árvore da lista
 *  \return  bool teste
 */
bool BinaryTreeOfListOnDisk::empty() const {
  return size_ == 0u;
}

//! Tamanho da árvore
/*! Retorna a quantidade de nodes na árvore
 *  \return size_t tamanho
 */
size_t BinaryTreeOfListOnDisk::size() const {
  return size_;
}

//! Profundidade da árvore
/*! Retorna a profundidade de nodes na árvore
 *  \return size_t profundidade
 */
size_t BinaryTreeOfListOnDisk::depth() const {
  return depth_;
}

//! Tamanho do arquivo da árvore
/*! Retorna o tamanho do arquivo
 *  \return Tamanho
 */
size_t BinaryTreeOfListOnDisk::file_size() const {
  struct stat st;
  if (stat("./secondary_tree.dat", &st) != 0)
    throw std::out_of_range("Erro ao verificar tamanho do arquivo.");
  return st.st_size;
}

}  //  namespace structures

#endif
