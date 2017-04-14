//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_DOUBLY_CIRCULAR_LIST_H
#define STRUCTURES_DOUBLY_CIRCULAR_LIST_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

template<typename T>
class DoublyCircularList {
public:
    DoublyCircularList();
    ~DoublyCircularList();

    void clear();

    void push_back(const T& data);
    void push_front(const T& data);
    void insert(const T& data, std::size_t index);
    void insert_sorted(const T& data);

    T pop(std::size_t index);
    T pop_back();
    T pop_front();
    void remove(const T& data);

    bool empty() const;
    bool contains(const T& data) const;

    T& at(std::size_t index);
    const T& at(std::size_t index) const;

    std::size_t find(const T& data) const;
    std::size_t size(); const;

private:
    class Node {
    public:

        Node(const T& data) :
        data_{data}
        {}

        Node(const T& data, Node* next):
        data_{data},
        next_{next}
        {}

        Node(const T& data, Node* prev, Node* next):
        data_{data},
        next_{next},
        prev_{prev}
        {}

        T& data() {
          return data_
        }

        const T& data() const {
          return data_;
        }

        Node* prev() {
          return prev_;
        }

        const Node* prev() const {
          return prev_;
        }

        void prev(Node* node) {
          prev_ = node;
        }

        Node* next() {
          return next_;
        }

        const Node* next() const {
          return next_;
        }

        void next(Node* node) {
          next_ = node;
        }

    private:
        T data_;
        Node* prev_;
        Node* next_;
    };

    Node* node_of_index(std::size_t index);

    void insert(const T& data, Node* current);

    Node* head{nullptr};
    std::size_t size_{0u};
};

template<typename T>
DoublyCircularList<T>::DoublyCircularList() {}

template<typename T>
DoublyCircularList<T>::~DoublyCircularList() {
  clear();
}

template<typename T>
void DoublyCircularList<T>::clear() {
  while(!empty())
    pop_front();
}

template<typename T>
void DoublyCircularList<T>::push_back(const T& data) {
  insert(data, size_);
}

template<typename T>
void DoublyCircularList<T>::push_front(const T& data) {
  insert(data, 0);
}

template<typename T>
void DoublyCircularList<T>::insert(const T& data, std::size_t index) {
  if (index > size_)
      throw std::out_of_range("Invalid index!");

  Node* new_node = new Node(data);
  if (new_node == nullptr)
      throw std::out_of_range("Full list!");

  Node* current = node_of_index(index);
  new_node->next(current);
  new_node->prev(current->prev());
  current->prev()->next(new_node);
  current->prev(new_node);
  size_++;
}

//! Inserção em qualquer lugar da lista recebendo um ponteiro de um Node.
/*! Polimorfismo do insert() para uso no insert_sorted().
 *  Possíveis erros:
 *   - Se o índice não existir.
 *   - Se a lista estiver cheia.
 *  \param data Dado T que será inserido na fila.
 *  \param before Node* anterior para inserir a sua frente.
 *  \sa push_back(), push_front(), insert_sorted()
 */
template<typename T>
void DoublyLinkedList<T>::insert(const T& data, Node* previous) {
    Node* new_node = new Node(data);
    if (new_node == nullptr)
        throw std::out_of_range("Full list!");
    if (empty()) {
      head = new_node;
    } else {
      previous->next()->prev(new_node);
      new_node->next(previous->next());
      previous->next(new_node);
      new_node->prev(previous);
    }
    size_++;
}

template<typename T>
void DoublyCircularList<T>::insert_sorted(const T& data) {
  if (empty()) {
      push_front(data);
  } else {

      /*
      auto current = head;
      std::size_t position = size_;
      for (auto i = 0u; i < size_; ++i) {
          if (!(data > current->data())) {
              position = i;
              break;
          }
          current = current->next();
      } */

      auto current = head;
      std::size_t position = 0u;
      while (data > current->data()) {
        if (++position == size_)
          break;
        current = current->next();
      }
      position == 0? push_front(data) :
      position == size_? push_back(data) :
                         insert(data, current);
  }
}

template<typename T>
T DoublyCircularList<T>::pop(std::size_t index);

template<typename T>
T DoublyCircularList<T>::pop_back();

template<typename T>
T DoublyCircularList<T>::pop_front();

template<typename T>
void DoublyCircularList<T>::remove(const T& data) {
  pop(find(data));
}

template<typename T>
bool DoublyCircularList<T>::empty() const {
  return size() != 0u;
}

template<typename T>
bool DoublyCircularList<T>::contains(const T& data) const {
  return find(data) != size();
}

template<typename T>
T& DoublyCircularList<T>::at(std::size_t index) {
  if (index >= size())
      throw std::out_of_range("Invalid index or empty list!");

  Node* current = index == 0? head : node_of_index(index);
  return current->data();
}

template<typename T>
const T& DoublyCircularList<T>::at(std::size_t index) const {
  if (index >= size())
      throw std::out_of_range("Invalid index or empty list!");

  Node* current = index == 0? head : node_of_index(index);
  return current->data();
}

template<typename T>
std::size_t DoublyCircularList<T>::find(const T& data) const {
  std::size_t index = 0u;
  auto current = head;
  while (index < size()) {
      if (current->data() == data)
          break;
      current = current->next();
      index++;
  }
  return index;
}

template<typename T>
std::size_t DoublyCircularList<T>::size(); const {
  return size_;
}

template<typename T>
Node* DoublyCircularList<T>::node_of_index(std::size_t index) {
    auto it = head;
    if (index <= (size()/2)) {
      for (auto i = 1u; i <= index; ++i)
          it = it->next();
    } else {
      for (auto i = 1u; i <= (size_-index); ++i)
          it = it->prev();
    }
    return it;
}

}  // namespace structures

#endif
