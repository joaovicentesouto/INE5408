//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_LINKED_STACK_H
#define STRUCTURES_LINKED_STACK_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include "./linked_list.h"  // Import LinkedList

namespace structures {

//! Classe Pilha Encadeada
/*! Implementação de uma pilha encadeada. Possui o comportamento de uma
 *  pilha de pratos, na qual todas as formas de acesso e modificação se
 *  dão pelo dado que está no topo da pilha.
 *  Aspecto estrutural:
 *    - É guardado apenas o ponteiro do node que está no topo da pilha.
 *    - Cada node aponta para o seguinte.
 *    - Só é possível trabalhar com o node no topo da pilha.
 *  \author João Vicente Souto.
 *  \since 05/04/17
 *  \version 1.0
 */
template<typename T>
class LinkedStack : private LinkedList<T> {
 public:
    LinkedStack();  // Construtor
    ~LinkedStack();  // Destrutor
    void clear();  // limpa pilha
    void push(const T& data);  // empilha
    T pop();  // desempilha
    T& top() const;  // dado no topo
    bool empty() const;  // pilha vazia
    std::size_t size() const;  // tamanho da pilha
};

//! Construtor
/*! Sem parâmetros chamando o contrutor da classe Pai
 */
template<typename T>
LinkedStack<T>::LinkedStack() : LinkedList<T>::LinkedList() {}

//! Destrutor
/*! Método para desalocar a memória utilizada pela pilha.
 */
template<typename T>
LinkedStack<T>::~LinkedStack() {
  LinkedList<T>::clear();
}

//! Esvazia a pilha.
/*! Remove todos os elementos da pilha e desalocando a memória.
 *  \sa push(), pop(), top()
 */
template<typename T>
void LinkedStack<T>::clear() {
  LinkedList<T>::clear();
}

//! Inserção de um novo dado na pilha.
/*! Dado será inserido sempre no topo da pilha.
 *  \param data T Dado que será inserido na pilha.
 *  \sa pop(), top(), clear()
 */
template<typename T>
void LinkedStack<T>::push(const T& data) {
    LinkedList<T>::push_front(data);
}

//! Remoção de um dado da pilha.
/*! Retira o dado que está no topo da pilha.
 *  \return T dado que estava no topo.
 *  \sa push(), top(), clear()
 */
template<typename T>
T LinkedStack<T>::pop() {
    return LinkedList<T>::pop_front();
}

//! Referencia o dado no topo da pilha.
/*! Retorna o dado do topo da pilha que será referenciado para uso externo,
 *  caso exista.
 *  \return T& Dado para ser referenciado.
 *  \sa push(), pop(), clear()
 */
template<typename T>
T& LinkedStack<T>::top() const {
    return LinkedList<T>::at(0u);
}

//! Pilha vazia
/*! Testa se a pilha está vazia.
 *  \return valor booleano.
 */
template<typename T>
bool LinkedStack<T>::empty() const {
  return LinkedList<T>::empty();
}

//! Quantidade de dados na pilha.
/*! Retorna o tamanho da pilha. 0 indica que está vazia.
 *  \return size_t referente ao tamanho da pilha.
 */
template<typename T>
size_t LinkedStack<T>::size() const {
  return LinkedList<T>::size();
}

}  // namespace structures

#endif
