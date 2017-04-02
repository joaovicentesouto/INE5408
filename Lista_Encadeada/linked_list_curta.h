//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions


namespace structures {

//! Classe Lista Encadeada
/*! Implementação de uma lista se baseando em alocação dinâmica de memória.
 *  Aspectos funcionais:
 *   - Colocar e retirar.
 *   - Testes de vazia, cheia ou que contenha um determinado dado.
 *   - Iniciar e garantir determinada ordem dos elementos.
 *  Características estruturais:
 *   - Através de um HEAD que guarda a referência do primeiro elemento é
 *     possível acessar qualquer outros elemento percorrendo de um elemento
 *     ao próximo.
 *   - O tamanho da lista inicia em 0, indicando que a lista esta vazia.
 *
 *  \author João Vicente Souto.
 *  \since 17/03/17
 *  \version 1.0
 */
template<typename T>
class LinkedList {
 public:
    //! Comt
    /*! Comt
     */
    LinkedList() {}  // construtor padrão

    //! Comt
    /*! Comt
     */
    ~LinkedList() {
        clear();
        head = nullptr;
    }

    //! Comt
    /*! Comt
     */
    void clear() {
        while (!empty())
            pop_front();
    }

    //! Comt
    /*! Comt
     */
    void push_back(const T& data) {
        insert(data, size_);
    }

    //! Comt
    /*! Comt
     */
    void push_front(const T& data) {
        Node* new_node = new Node(data);
        if (new_node == nullptr)
            throw std::out_of_range("Full list!");

        new_node->next(head);
        head = new_node;
        size_++;
    }

    //! Comt
    /*! Comt
     */
    void insert(const T& data, std::size_t index) {
        if (index > size_+1u)
            throw std::out_of_range("Invalid index!");
        if (index == 0) {
            push_front(data);
        } else {
            Node* new_node = new Node(data);
            if (new_node == nullptr)
                throw std::out_of_range("Full list!");

            Node* last = head;
            for (auto i = 1u; i < index; ++i) {
                last = last->next();
            }
            new_node->next(last->next());
            last->next(new_node);
            size_++;
        }
    }

    //! Comt
    /*! Comt
     */
    void insert_sorted(const T& data) {
        if (empty()) {
            push_front(data);
        } else {
            Node* actual = head;
            auto position = 0;
            while (actual->next() != nullptr && data > actual->data()) {
                actual = actual->next();
                position++;
            }
            if (data > actual->data())
                insert(data, position+1);
            else
                insert(data, position);
        }
    }

    //! Comt
    /*! Comt
     */
    T& at(std::size_t index) {
        if (empty())
            throw std::out_of_range("Empty list!");
        if (index >= size_)
            throw std::out_of_range("Invalid index!");

        auto current = head;
        for (auto i = 1u; i <= index; ++i)
            current = current->next();
        return current->data();
    }

    //! Comt
    /*! Comt
     */
    T pop(std::size_t index) {
        if (index > size_-1u)
            throw std::out_of_range("Invalid index!");

        if (index == 0) {
            return pop_front();
        } else {
            Node* last = head;
            for (auto i = 1u; i < index; ++i) {
                last = last->next();
            }
            Node* out = last->next();
            T& data = out->data();
            last->next(out->next());
            size_--;
            delete out;
            return data;
        }
    }

    //! Comt
    /*! Comt
     */
    T pop_back() {
        try {
            return pop(size_-1u);
        } catch(std::out_of_range error) {
            throw error;
        }
    }

    //! Comt
    /*! Comt
     */
    T pop_front() {
        if (empty())
            throw std::out_of_range("Empty list!");

        Node* out = head;
        T& data = out->data();
        head = out->next();
        size_--;
        delete out;
        return data;
    }

    //! Comt
    /*! Comt
     */
    void remove(const T& data) {
        pop(find(data));
    }

    //! Comt
    /*! Comt
     */
    bool empty() const {
        return size_ == 0u;
    }

    //! Comt
    /*! Comt
     */
    bool contains(const T& data) const {
        return find(data) != size_;
    }

    //! Comt
    /*! Comt
     */
    std::size_t find(const T& data) const {
        if (empty())
            throw std::out_of_range("Empty list!");
        auto current = head;
        for (auto i = 1u; i < size_; ++i) {
            if (data == current->data())
                return i;
            current = current->next();
        }
        return size_;
    }

    //! Comt
    /*! Comt
     */
    std::size_t size() const {
        return size_;
    }

    //! Comt
    /*! Comt
     */
    void draw_connection() const {
      if (size() > 1) {
        auto current = head;
        for (auto i = 0u; i < size()-1u; ++i) {
          printf("%d -> ", current->data());
          current = current->next();
        }
        printf("%d -> %p ....... t%lu\n", current->data(), current->next(), size());
      } else {
        if (size() == 1)
            printf("%d -> %p ....... t%lu\n", head->data(), head->next(), size());
        else
            printf("%p  ....... t%lu\n", head, size());
      }
    }

 private:
    class Node {  // Elemento
     public:
        //! Comt
        /*! Comt
         */
        explicit Node(const T& data):
        data_{data}
        {}

        //! Comt
        /*! Comt
         */
        explicit Node(const T& data, Node* next):
        data_{data},
        next_{next}
        {}

        //! Comt
        /*! Comt
         */
        T& data() {  // getter: dado
            return data_;
        }

        //! Comt
        /*! Comt
         */
        const T& data() const {  // getter const: dado
            return data_;
        }

        //! Comt
        /*! Comt
         */
        Node* next() {  // getter: próximo
            return next_;
        }

        //! Comt
        /*! Comt
         */
        const Node* next() const {  // getter const: próximo
            return next_;
        }

        //! Comt
        /*! Comt
         */
        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;  // data_
        Node* next_{nullptr};  // next_
    };

    //! Comt
    /*! Comt
     */
    Node* end() {  // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    //! Comt
    /*! Comt
     */
    Node* before_index(std::size_t index) {  // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < index; ++i) {
            it = it->next();
        }
        return it;
    }

    //  void insert(const T& data, Node* last);  // inserir

    Node* head{nullptr};  // head
    std::size_t size_{0u};  // size_
};

}  // namespace structures

#endif
