//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include "./linked_list.h"

namespace structures {

template<typename T>
class LinkedQueue {
public:
    LinkedQueue();

    ~LinkedQueue();

    void clear(); // limpar

    void enqueue(const T& data); // enfilerar

    T dequeue(); // desenfilerar

    T& front() const; // primeiro dado

    T& back() const; // último dado

    bool empty() const; // fila vazia

    std::size_t size() const; // tamanho

private:
    Node* tail; // nodo-fim
};

template<typename T>
LinkedQueue<T>::LinkedQueue() : LinkedList<T>::LinkedList() {}

template<typename T>
LinkedQueue<T>::~LinkedQueue() {
    LinkedList<T>::~LinkedList();
}

template<typename T>
void LinkedQueue<T>::clear() {
    LinkedList<T>::clear();
}

template<typename T>
void LinkedQueue<T>::enqueue() {
    
}

template<typename T>
T LinkedQueue<T>::dequeue() {}

template<typename T>
T& LinkedQueue<T>::front() {}

template<typename T>
T& LinkedQueue<T>::back() {}

template<typename T>
bool LinkedQueue<T>::empty() {}

template<typename T>
std::size_t LinkedQueue<T>::size() {}

}  // namespace structures

#endif

/* original
namespace structures {


template<typename T>
class LinkedQueue {
public:
    LinkedQueue();

    ~LinkedQueue();

    void clear(); // limpar

    void enqueue(const T& data); // enfilerar

    T dequeue(); // desenfilerar

    T& front() const; // primeiro dado

    T& back() const; // último dado

    bool empty() const; // fila vazia

    std::size_t size() const; // tamanho

private:
    Node* head; // nodo-cabeça
    Node* tail; // nodo-fim
    std::size_t size_; // tamanho
};

}*/

