//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_LINKED_QUEUE_H
#define STRUCTURES_LINKED_QUEUE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include "./linked_list.h"

namespace structures {

template<typename T>

//! Classe Fila
/*! Implementação de uma fila usando herança da lista encadeada.
 *  A fila possui o comportamento de uma fila normal, onde o primeiro
 *  que entre é o primeiro a sair.
 *  \author João Vicente Souto.
 *  \since 04/04/17
 *  \version 1.0
 */
class LinkedQueue : private LinkedList<T> {
 public:
    LinkedQueue();
    ~LinkedQueue();
    void clear();
    void enqueue(const T& data);
    T dequeue();
    T& front() const;
    T& back() const;
    bool empty() const;
    std::size_t size() const;

 private:
    typedef typename LinkedList<T>::Node Node;
    Node* tail{nullptr};  //!< Ponteiro do último node da fila.
};

//! Construtor padrão
/*! Sem parâmetros, a fila é inicializada com valores padrões.
 */
template<typename T>
LinkedQueue<T>::LinkedQueue() : LinkedList<T>::LinkedList() {}

//! Destrutor
/*! Método para desalocar a memória utilizada pela fila.
 */
template<typename T>
LinkedQueue<T>::~LinkedQueue() {
    LinkedList<T>::clear();
    delete tail;
}

//! Esvazia a fila.
/*! Atualiza o tamanho da fila para -1, indicando que a fila esta vazia.
 *  \sa enqueue(), dequeue()
 */
template<typename T>
void LinkedQueue<T>::clear() {
    LinkedList<T>::clear();
}

//! Inserção de um novo dado na fila.
/*! Sempre será colocado no final da fila, caso não esteja vazia.
 *  \param data um novo dado que será inserido na fila.
 *  \sa dequeue(), clear()
 */
template<typename T>
void LinkedQueue<T>::enqueue(const T& data) {
    auto new_node = new Node(data);
    if (new_node == nullptr)
        throw std::out_of_range("Full queue!");

    if (empty()) {
        LinkedList<T>::head = new_node;
        tail = LinkedList<T>::head;
    } else {
        tail->next(new_node);
        tail = new_node;
    }
    LinkedList<T>::size_++;
}

//! Remoção de um dado da fila.
/*! Sempre será removido o primeiro dado da fila, caso não esteja vazia.
 *  \sa enqueue(), clear()
 */
template<typename T>
T LinkedQueue<T>::dequeue() {
    T temp = LinkedList<T>::pop_front();
    if (empty())
        tail = nullptr;
    return temp;
}

//! Referencia o dado no inicio da fila.
/*! Retorna o dado que esta no inicio da fila para uso externo, caso exista.
 *  \return T& um dado que será referenciado.
 *  \sa back()
 */
template<typename T>
T& LinkedQueue<T>::front() const {
    return LinkedList<T>::at(0u);
}

//! Referencia o dado no final da fila.
/*! Retorna o dado que esta no final da fila para uso externo, caso exista.
 *  \return T& um dado que será referenciado.
 *  \sa front()
 */
template<typename T>
T& LinkedQueue<T>::back() const {
    if (empty())
        throw std::out_of_range("Empty queue!");
    return tail->data();
}

//! Fila vazia
/*! Testa se a fila está vazia.
 *  \return um booleano.
 */
template<typename T>
bool LinkedQueue<T>::empty() const {
    return LinkedList<T>::empty();
}

//! Quantidade de dados na fila.
/*! Retorna o tamanho da fila.
 *  \return um size_t referente ao tamanho da fila.
 */
template<typename T>
std::size_t LinkedQueue<T>::size() const {
    return LinkedList<T>::size();
}

}  // namespace structures

#endif
