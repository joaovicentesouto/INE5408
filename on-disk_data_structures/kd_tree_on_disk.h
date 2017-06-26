//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_KD_TREE_H
#define STRUCTURES_KD_TREE_H

#include <cstdint>
#include <stdexcept>
#include <fstream>
#include <cstdio>
#include <sys/stat.h>

#include "./structures/linked_list.h"
#include "./structures/linked_stack.h"

using namespace std;

namespace structures {

//! Classe KDTreeOnDisk
/*! Árvore KD sendo a chave primária o nome do arquivo e a chave
 *  secundária o tamanho do árquivo para melhorar a distribuição.
 *
 *  \author João Vicente Souto.
 *  \since 20/06/17
 *  \version 1.0
 */
class KDTreeOnDisk {
public:
  KDTreeOnDisk();  // Construtor
  ~KDTreeOnDisk();  // Destrutor

  int insert(const char* primary, const size_t secondary, char* manpage);  // Inserir
  //void remove(const char* primary, const size_t secondary, char* manpage);

  bool empty() const;  // Teste de vazio
  size_t size() const;  // Tamanho da árvore
  size_t depth() const;  // Profundidade da árvore
  size_t file_size() const;  // Tamanho do arquivo da árvore

  char* search_primary_key(const char* wanted);  // Procura manpage
  string return_primary_key(const size_t wanted);  // Procura nome da mapage
  LinkedList<string>* return_primary_key(LinkedList<size_t> *wanted_list);  // Procura nomes das mapages
  //LinkedList<string>* search_secondary_key(const size_t wanted) const;


private:
  //! Classe Node
  /*! Node da árvore
   *
   *  \author João Vicente Souto.
   *  \since 20/06/17
   *  \version 1.0
   */
  class Node {
  public:
    //! Construtor
    /*! Sem parâmetros, carrega palavras ignoradas de arquivo em disco.
     *  \sa Node(const char* primary, const size_t secondary, char* manpage), ~Node()
     */
    Node() {}

    //! Construtor
    /*! Com parâmetros, dados basicos de um node
     *  \sa Node(), ~Node()
     */
    Node(const char* primary, const size_t secondary, char* manpage) {
      strcpy(primary_, primary);
      secondary_ = secondary;
      strcpy(manpage_, manpage);
    }

    //! Destrutor
    /*! Destrutor padrão, não tem nada alocado dinâmicamente.
     *  \sa Node(const char* primary, const size_t secondary, char* manpage), Node()
     */
    ~Node() {}

    //! Tamanho do node
    /*! Tamanho real do node que será escrito no arquivo
     * \return size_t tamanho real do node
     */
    size_t size() {
      size_t aux = sizeof(primary_) + sizeof(secondary_)
                   + sizeof(left_) + sizeof(right_) + secondary_ + 10;
      return aux;
    }

    char primary_[50]{"@"};  //!< Chave primária
    size_t secondary_{0u},  //!< Chave secundária
           left_{0u},  //!< Node da esquerda
           right_{0u};  //!< Node da direita
    char manpage_[139718]{"&"};  //!< Manpage
  };

  //! Classe Route
  /*! Objeto auxiliar para percorrer a árvore
   *
   *  \author João Vicente Souto.
   *  \since 20/06/17
   *  \version 1.0
   */
  class Route {
  public:
    //! Construtor
    /*! Sem parâmetros.
     *  \sa Route(const size_t offset, const size_t level), ~Route()
     */
    Route() {}

    //! Construtor
    /*! Com parâmetros, dados basicos da route
     *  \sa Route(), ~Route()
     */
    Route(const size_t offset, const size_t level) :
    offset_tree_{offset},
    level_{level}
    {}

    //! Destrutor
    /*! Destrutor padrão, não tem nada alocado dinâmicamente.
     *  \sa Node(const char* primary, const size_t secondary, char* manpage), Node()
     */
    ~Route() {}

    //! Sobreescrita do operador =
    /*! Recebe um Route para copiar
     *  \param Route copiado
     *  \return Route this
     */
    Route& operator=(const Route& other) {
        if (this != &other) {
            this->offset_tree_ = other.offset_tree_;
            this->level_ = other.level_;
        }
        return *this;
    }

    size_t offset_tree_{0u},  //!< Deslocamento na árvore
           level_{0u};  //!< Level do deslocamento
  };

  size_t depth_{0u},  //!< Profundidade
         size_{0u};  //!< Quantidade de nodes
};

//! Construtor
/*! Sem parâmetros, limpa arquivo da arvore
 *  \sa ~KDTreeOnDisk()
 */
KDTreeOnDisk::KDTreeOnDisk() {
  // Cria arquivo para a arvore ou sobreescreve um existente
  fstream tree("./primary_tree.dat", ios::in | ios::out | ios::binary | ios::trunc);
  tree.close();
}

//! Destrutor
/*! Destrutor padrão, não tem nada alocado dinâmicamente.
 *  \sa KDTreeOnDisk()
 */
KDTreeOnDisk::~KDTreeOnDisk() {}

//! Insere
/*! Recebe manpage para inserção
 *  \param char* nome da manpage
 *  \param size_t tamanho do arquivo
 *  \param char* manpage
 *  \return int deslocamento na árvore
 */
int KDTreeOnDisk::insert(const char* key_1,
                          const size_t key_2, char* manpage) {
  fstream tree("./primary_tree.dat", ios::in | ios::out | ios::binary);

  char node_key_1[50];
  size_t node_key_2;
  int compare = 1;
  size_t offset = 0u, son = 0u, level = 0u, father_son = 0u,
         offset_secondary = sizeof(Node::primary_)+6,
         offset_left = offset_secondary + sizeof(size_t),
         offset_right = offset_left + sizeof(size_t);

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
    Node *tnode = new Node(key_1, key_2, manpage);
    if (tnode == nullptr)
      throw std::out_of_range("Full tree!");

    tree.seekp(0, ios::end); // fim do arquivo
    son = tree.tellp();      // pega deslocamento pro filho

    if (size_ != 0) {
      tree.seekp(father_son);    // modifica o pai
      tree.write(reinterpret_cast<char*>(&son), sizeof(size_t));
    }

    tree.seekp(son);            // adiciona o node
    tree.write(reinterpret_cast<char*>(tnode), tnode->size());
    ++size_;
    delete tnode;
  }

  depth_ = level > depth_? level : depth_;
  tree.close();
  // retorna o descolocamento onde esta o node inserido
  return compare == 0u? -1 : son;
}

//! Procura manpage
/*! Recebe nome da manpage e retorna texto do arquivo da manpage.
 *  \param char* nome da manpage
 *  \return char* manpage
 */
char* KDTreeOnDisk::search_primary_key(const char* wanted) {
  // Guardar o deslocamento e nível em uma pilha quando tiver
  // que descer por dois caminhos diferentes.
  LinkedStack<Route> routes; // desvios
  char node_key_1[50];
  size_t node_key_2;
  int compare = 1;
  size_t offset = 0u, son = 0u, level = 0u,
         offset_secondary = sizeof(Node::primary_)+6,
         offset_left = offset_secondary + sizeof(size_t),
         offset_right = offset_left + sizeof(size_t),
         offset_manpage = offset_right + sizeof(size_t);

  ifstream tree("./primary_tree.dat", std::ios_base::app | ios::binary);
  tree.seekg(0); // inicio do arquivo

  while (tree.good()) {
    offset = tree.tellg();

    tree.read(node_key_1, sizeof(Node::primary_));
    compare = strcmp(wanted, node_key_1);

    if (compare == 0) {  // achei
      // le offset da manpage
      tree.seekg(offset + offset_secondary);
      tree.read(reinterpret_cast<char*>(&node_key_2), sizeof(size_t));

      char *manpage = new char[node_key_2];
      tree.seekg(offset + offset_manpage);
      tree.read(manpage, node_key_2);
      return manpage;
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

    if (son != 0) { // próximo node nao é nulo
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

  return nullptr; // não achou
}

//! Procura nome da manpage
/*! Recebe o deslocamento na árvore da manpage
 *  \param size_t deslocamento
 *  \return string nome da manpage
 */
string KDTreeOnDisk::return_primary_key(const size_t wanted) {
  char node_key[50];
  ifstream tree("./primary_tree.dat", std::ios_base::app | ios::binary);
  tree.seekg(wanted);
  tree.read(node_key, sizeof(node_key));
  return string(node_key);
}

//! Procura todos os nomes das manpages passadas na lista.
/*! Recebe lista com todos os deslocamentos
 *  \param LinkedList<size_t> lista de deslocamento
 *  \return LinkedList<string> lista com os nomes da lista
 */
LinkedList<string>* KDTreeOnDisk::return_primary_key(LinkedList<size_t> *wanted_list) {
  LinkedList<string> *list = new LinkedList<string>();

  char node_key[50];
  ifstream tree("./primary_tree.dat", std::ios_base::app | ios::binary);
  while (!wanted_list->empty()) {
    tree.seekg(wanted_list->pop_front());
    tree.read(node_key, sizeof(node_key));
    list->insert_sorted(node_key);
  }

  return list;
}

//! Teste de vazio
/*! Retorna o teste se a árvore da lista
 *  \return  bool teste
 */
bool KDTreeOnDisk::empty() const {
  return size_ == 0u;
}

//! Tamanho da árvore
/*! Retorna a quantidade de nodes na árvore
 *  \return size_t tamanho
 */
size_t KDTreeOnDisk::size() const {
  return size_;
}

//! Profundidade da árvore
/*! Retorna a profundidade de nodes na árvore
 *  \return size_t profundidade
 */
size_t KDTreeOnDisk::depth() const {
  return depth_;
}

//! Tamanho do arquivo da árvore
/*! Retorna o tamanho do arquivo
 *  \return Tamanho
 */
size_t KDTreeOnDisk::file_size() const {
  struct stat st;
  if (stat("./primary_tree.dat", &st) != 0)
    throw std::out_of_range("Erro ao verificar tamanho do arquivo.");
  return st.st_size;
}

}  //  namespace structures

#endif
