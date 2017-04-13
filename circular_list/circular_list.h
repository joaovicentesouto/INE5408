#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>  //  std::size_t
#include <stdexcept>  //  C++ exceptions
#include "linked_list.h"

namespace structures {

template<typename T>
class CircularList : public LinkedList<T> {
public:
    // CircularList();
    // ~CircularList();
    //
    // void clear(); //  limpar lista
    //
    void push_back(const T& data); //  inserir no fim
    // void push_front(const T& data); //  inserir no início
    // void insert(const T& data, std::size_t index); //  inserir na posição
    // void insert_sorted(const T& data); //  inserir em ordem
    //
    // T& at(std::size_t index); //  acessar em um indice (com checagem de limites)
    // const T& at(std::size_t index) const; //  versão const do acesso ao indice
    //
    // T pop(std::size_t index); //  retirar da posição
    // T pop_back(); //  retirar do fim
    // T pop_front(); //  retirar do início
    // void remove(const T& data); //  remover dado específico
    //
    // bool empty() const; //  lista vazia
    // bool contains(const T& data) const; //  lista contém determinado dado?
    // std::size_t find(const T& data) const; //  posição de um item na lista
    //
    // std::size_t size() const; //  tamanho da lista
    void draw_connection();

  private:
     typedef typename LinkedList<T>::Node Node;
};

// template<typename T>
// CircularList<T>::CircularList() : LinkedList<T>::LinkedList() {}
//
// template<typename T>
// CircularList<T>::~CircularList() {}

template<typename T>
void CircularList<T>::push_back(const T& data) {
  if (this->empty()) {
    this->push_front(data);
    this->head->next(LinkedList<T>::head);
  } else {
    Node* novoHead = new Node(this->head->data(), this->head->next());
    this->head->next(novoHead);
    this->head->data() = data;
    this->head = novoHead;
    this->size_++;
  }
}

template<typename T>
void CircularList<T>::draw_connection() {
  auto temp = this->head;
  for (auto i = 0; i < this->size_+2; ++i) {
    printf("%d -> ", temp->data());
    temp = temp->next();
  }
  printf("%d -> \n", temp->data());
}


}  //  namespace structures

#endif
