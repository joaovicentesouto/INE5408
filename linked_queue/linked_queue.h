//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_LINKED_QUEUE_H
#define STRUCTURES_LINKED_QUEUE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include "./linked_list.h"

namespace structures {

template<typename T>
//! Title
/*! Description
 */
class LinkedQueue : private LinkedList<T> {
 public:
    LinkedQueue();
    ~LinkedQueue();
    void clear();  // limpar
    void enqueue(const T& data);  // enfilerar
    T dequeue();  // desenfilerar
    T& front() const;  // primeiro dado
    T& back() const;  // último dado
    bool empty() const;  // fila vazia
    std::size_t size() const;  // tamanho

 private:
    typedef typename LinkedList<T>::Node Node;
    Node* tail{nullptr};  // nodo-fim
};

//! Title
/*! Description
 */
template<typename T>
LinkedQueue<T>::LinkedQueue() : LinkedList<T>::LinkedList() {}

//! Title
/*! Description
 */
template<typename T>
LinkedQueue<T>::~LinkedQueue() {
    LinkedList<T>::clear();
}

//! Title
/*! Description
 */
template<typename T>
void LinkedQueue<T>::clear() {
    LinkedList<T>::clear();
}

//! Title
/*! Description
 */
template<typename T>
void LinkedQueue<T>::enqueue(const T& data) {
    auto new_node = new Node(data);
    if (new_node == nullptr)
        throw std::out_of_range("Full list!");

    if (empty()) {
        LinkedList<T>::head = new_node;
        tail = LinkedList<T>::head;
    } else {
        tail->next(new_node);
        tail = new_node;
    }
    LinkedList<T>::size_++;
}

//! Title
/*! Description
 */
template<typename T>
T LinkedQueue<T>::dequeue() {
    T temp = LinkedList<T>::pop_front();
    if (empty())
        tail = nullptr;
    return temp;
}

//! Title
/*! Description
 */
template<typename T>
T& LinkedQueue<T>::front() const {
    return LinkedList<T>::at(0u);
}

//! Title
/*! Description
 */
template<typename T>
T& LinkedQueue<T>::back() const {
    if (empty())
        throw std::out_of_range("Empty list!");
    return tail->data();
}

//! Title
/*! Description
 */
template<typename T>
bool LinkedQueue<T>::empty() const {
    return LinkedList<T>::empty();
}

//! Title
/*! Description
 */
template<typename T>
std::size_t LinkedQueue<T>::size() const {
    return LinkedList<T>::size();
}

}  // namespace structures

#endif
