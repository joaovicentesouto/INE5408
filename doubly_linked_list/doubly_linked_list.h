//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_DOUBLY_LINKED_LIST_H
#define STRUCTURES_DOUBLY_LINKED_LIST_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

template<typename T>

//! Title
//* Description
class DoublyLinkedList {
 public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    void clear();

    void push_back(const T& data);  // insere no fim
    void push_front(const T& data);  // insere no início
    void insert(const T& data, std::size_t index);  // insere na posição
    void insert_sorted(const T& data);  // insere em ordem

    T pop(std::size_t index);  // retira da posição
    T pop_back();  // retira do fim
    T pop_front();  // retira do início
    void remove(const T& data);  // retira específico

    bool empty() const;  // lista vazia
    bool contains(const T& data) const;  // contém

    T& at(std::size_t index);  // acesso a um elemento (checando limites)
    const T& at(std::size_t index) const;  // getter constante a um elemento

    std::size_t find(const T& data) const;  // posição de um dado
    std::size_t size() const;  // tamanho

 private:
    //! Title
    //* Description
    class Node {
     public:
        //! Title
        //* Description
        explicit Node(const T& data):
        data_{data}
        {}

        //! Title
        //* Description
        Node(const T& data, Node* next):
        data_{data},
        next_{next}
        {}

        //! Title
        //* Description
        Node(const T& data, Node* prev, Node* next):
        data_{data},
        prev_{prev},
        next_{next}
        {}

        //! Title
        //* Description
        T& data() {
            return data_;
        }

        //! Title
        //* Description
        const T& data() const {
            return data_;
        }

        //! Title
        //* Description
        Node* prev() {
            return prev_;
        }

        //! Title
        //* Description
        const Node* prev() const {
            return prev_;
        }

        //! Title
        //* Description
        void prev(Node* node) {
            prev_ = node;
        }

        //! Title
        //* Description
        Node* next() {
            return next_;
        }

        //! Title
        //* Description
        const Node* next() const {
            return next_;
        }

        //! Title
        //* Description
        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;  //< data
        Node* prev_{nullptr};  //< prev
        Node* next_{nullptr};  //< next
    };

    //! Passa pelos nodes até o último.
    /*! Retorna o último node.
     *  \sa before_index()
     *  \return Node* Último node.
     */
    Node* end() {  // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    //! Title
    //* Description
    Node* node_of_index(std::size_t index) {  // node anterior ao index
        auto it = head;
        for (auto i = 1u; i <= index; ++i) {
            it = it->next();
        }
        return it;
    }

    void insert(const T& data, Node* current);

    Node* head{nullptr};  //< head
    std::size_t size_{0u};  //< size
};

//! Title
//* Description
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() {}

//! Title
//* Description
template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

//! Title
//* Description
template<typename T>
void DoublyLinkedList<T>::clear() {
    while (!empty())
        pop_front();
}

//! Title
//* Description
template<typename T>
void DoublyLinkedList<T>::push_back(const T& data) {
    insert(data, size_);
}

//! Title
//* Description
template<typename T>
void DoublyLinkedList<T>::push_front(const T& data) {
    Node* new_node = new Node(data);
    if (new_node == nullptr)
        throw std::out_of_range("Full list!");

    if (empty()) {
      head = new_node;
    } else {
      new_node->next(head);
      head->prev(new_node);
      head = new_node;
    }
    size_++;
}

//! Title
//* Description
template<typename T>
void DoublyLinkedList<T>::insert(const T& data, std::size_t index) {
    if (index > size_)
        throw std::out_of_range("Invalid index!");

    if (index == 0) {
        push_front(data);
    } else {
        Node* new_node = new Node(data);
        if (new_node == nullptr)
            throw std::out_of_range("Full list!");

        if (index == size_) {
            Node* before = end();
            before->next(new_node);
        } else {
            Node* current = node_of_index(index);
            new_node->next(current);
            current->prev()->next(new_node);
        }
        size_++;
    }
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
void DoublyLinkedList<T>::insert(const T& data, Node* current) {
    Node* new_node = new Node(data);
    if (new_node == nullptr)
        throw std::out_of_range("Full list!");

    new_node->next(current);
    current->prev()->next(new_node);
    size_++;
}

//! Title
//* Description
template<typename T>
void DoublyLinkedList<T>::insert_sorted(const T& data) {
    if (empty()) {
        push_front(data);
    } else {
        auto current = head;
        std::size_t position = size_;
        for (auto i = 0u; i < size_; ++i) {
            if (!(data > current->data())) {
                position = i;
                break;
            }
            current = current->next();
        }
        position == 0? push_front(data) : insert(data, current);
    }
}

//! Title
//* Description
template<typename T>
T DoublyLinkedList<T>::pop(std::size_t index) {
    if (empty())
        throw std::out_of_range("Empty list");
    if (index >= size())
        throw std::out_of_range("Invalid index!");

    if (index == 0)
        return pop_front();

    auto out = node_of_index(index);
    T data = out->data();
    out->prev()->next(out->next());
    size_--;
    delete out;
    return data;
}

//! Title
//* Description
template<typename T>
T DoublyLinkedList<T>::pop_back() {
    return pop(size_ - 1u);
}

//! Title
//* Description
template<typename T>
T DoublyLinkedList<T>::pop_front() {
    if (empty())
        throw std::out_of_range("Empty list!");

    auto out = head;
    T data = out->data();
    head = out->next();
    size_--;
    delete out;
    return data;
}

//! Title
//* Description
template<typename T>
void DoublyLinkedList<T>::remove(const T& data) {
    pop(find(data));
}

//! Title
//* Description
template<typename T>
bool DoublyLinkedList<T>::empty() const {
    return size_ == 0u;
}

//! Title
//* Description
template<typename T>
bool DoublyLinkedList<T>::contains(const T& data) const {
    return find(data) != size_;
}

//! Title
//* Description
template<typename T>
T& DoublyLinkedList<T>::at(std::size_t index) {
    if (index >= size())
        throw std::out_of_range("Invalid index or empty list!");

    Node* current = index == 0? head : node_of_index(index);
    return current->data();
}

//! Title
//* Description
template<typename T>
const T& DoublyLinkedList<T>::at(std::size_t index) const {
    if (index >= size())
        throw std::out_of_range("Invalid index or empty list!");

    Node* current = index == 0? head : node_of_index(index);
    return current->data();
}

//! Title
//* Description
template<typename T>
std::size_t DoublyLinkedList<T>::find(const T& data) const {
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

//! Title
//* Description
template<typename T>
std::size_t DoublyLinkedList<T>::size() const {
    return size_;
}

}  // namespace structures

#endif
