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

    //! Passa pelos nodes até o último.
    /*! Retorna o último node.
     *  \sa node_of_index()
     *  \return Node* Último node.
     */
    Node* end() {  // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    //! Passa pelos nodes até o índice procurado.
    /*! Retorna o node que se procura.
     *  \sa end()
     *  \param size_t Índice do node.
     *  \return Node* O node do índice.
     */
    Node* node_of_index(std::size_t index) {
        auto it = head;
        for (auto i = 1u; i <= index; ++i) {
            it = it->next();
        }
        return it;
    }

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
void DoublyCircularList<T>::push_back(const T& data);

template<typename T>
void DoublyCircularList<T>::push_front(const T& data);

template<typename T>
void DoublyCircularList<T>::insert(const T& data, std::size_t index);

template<typename T>
void DoublyCircularList<T>::insert_sorted(const T& data);

template<typename T>
T DoublyCircularList<T>::pop(std::size_t index);

template<typename T>
T DoublyCircularList<T>::pop_back();

template<typename T>
T DoublyCircularList<T>::pop_front();

template<typename T>
void DoublyCircularList<T>::remove(const T& data);

template<typename T>
bool DoublyCircularList<T>::empty() const;

template<typename T>
bool DoublyCircularList<T>::contains(const T& data) const;

template<typename T>
T& DoublyCircularList<T>::at(std::size_t index);

template<typename T>
const T& DoublyCircularList<T>::at(std::size_t index) const;

template<typename T>
std::size_t DoublyCircularList<T>::find(const T& data) const;

template<typename T>
std::size_t DoublyCircularList<T>::size(); const {}

}  // namespace structures

#endif
