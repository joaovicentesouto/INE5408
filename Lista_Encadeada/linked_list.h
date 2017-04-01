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
    LinkedList();  // construtor padrão
    ~LinkedList();  //  destrutor
    void clear();  //  limpar lista
    void push_back(const T& data);  // inserir no fim
    void push_front(const T& data);  // inserir no início
    void insert(const T& data, std::size_t index);  // inserir na posição
    void insert_sorted(const T& data);  // inserir em ordem
    T& at(std::size_t index);  // acessar um elemento na posição index
    T pop(std::size_t index);  // retirar da posição
    T pop_back();  // retirar do fim
    T pop_front();  // retirar do início
    void remove(const T& data);  // remover específico
    bool empty() const;  // lista vazia
    bool contains(const T& data) const;  // contém
    std::size_t find(const T& data) const;  // posição do dado
    std::size_t size() const;  // tamanho da lista
    void desenha_arvore() const;

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

    void insert(const T& data, Node* last);  // inserir na posicao polimorfico

    Node* head{nullptr};  // head
    std::size_t size_{0u};  // size_
};

//! Construtor padrão
/*! Sem parâmetros, a lista já contém os valores inicializados já na definição.
 */
template<typename T>
LinkedList<T>::LinkedList() {}

//! Destrutor
/*! Método para desalocar a memória utilizada pela lista.
 */
template<typename T>
LinkedList<T>::~LinkedList() {}

//! Esvazia a lista.
/*! Retira todos os Nodes e atualiza o tamanho para 0.
 */
template<typename T>
void LinkedList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

//! Inserção no fim da lista.
/*! Sempre será colocado no final da lista, caso não esteja vazia.
 *  Possíveis erros:
 *   - Se a lista estiver cheia.
 *  \param data um dado T que será inserido na fila.
 *  \sa push_front(), insert(), insert_sorted()
 */
template<typename T>
void LinkedList<T>::push_back(const T& data) {
    try {
        insert(data, size());
    } catch(std::out_of_range error) {
        throw error;
    }
}

//! Inserção no começo da lista.
/*! Sempre será colocado no início da fila.
 *  Possíveis erros:
 *   - Se a lista estiver cheia.
 *  \param data um dado T que será inserido na fila.
 *  \sa push_back(), insert(), insert_sorted()
 */
template<typename T>
void LinkedList<T>::push_front(const T& data) {
    try {
        std::size_t i = 0u;
        insert(data, i);
    } catch(std::out_of_range error) {
        throw error;
    }
}

//! Inserção em qualquer lugar da lista.
/*! Verificando se a posição for válida, será inserido nas seguintes possíveis
 *  condições:
 *   - Começo: antes do primeiro Node.
 *   - Final: depois do último Node.
 *   - No meio: entre dois Nodes.
 *  Possíveis erros:
 *   - Se o índice não existir.
 *   - Se a lista estiver cheia.
 *  \param data um dado T que será inserido na fila.
 *  \param index um size_t indicando a posição que será inserido o dado.
 *  \sa push_back(), push_front(), insert_sorted()
 */
template<typename T>
void LinkedList<T>::insert(const T& data, std::size_t index) {
    if (index > size_)
        throw std::out_of_range("Posição não existe!");

    Node* fresh = new Node(data);
    if (fresh == nullptr)
        throw std::out_of_range("Full list!");

    if (index == 0) {
      fresh->next(head);
      head = fresh;
    } else {
      Node* last = before_index(index);
      Node* next = last->next();
      fresh->next(next);
      last->next(fresh);
    }
    size_++;
}

//! Inserção em qualquer lugar da lista recebendo um ponteiro de um Node.
/*! Polimorfismo do insert() para uso no insert_sorted().
 *  Verificando se a posição for válida, será inserido nas seguintes possíveis
 *  condições:
 *   - Começo: antes do primeiro Node.
 *   - Final: depois do último Node.
 *   - No meio: entre dois Nodes.
 *  Possíveis erros:
 *   - Se o índice não existir.
 *   - Se a lista estiver cheia.
 *  \param data um dado T que será inserido na fila.
 *  \param index um size_t indicando a posição que será inserido o dado.
 *  \sa push_back(), push_front(), insert_sorted()
 */
template<typename T>
void LinkedList<T>::insert(const T& data, Node* last) {
    last->next(new Node(data, last->next()));
    size_++;
}

//! Inserção ordenada na lista.
/*! Será buscado a posição ordenada do dado passado por parâmetro. A forma de
 *  comparação utilizada será o operador ">" que deve ser sobrescrito por quem
 *  for utilizar a lista e este método.
 *  Possíveis erros:
 *   - Se a lista estiver cheia.
 *  \param data um dado T que será inserido na fila.
 *  \param Node* um ponteiro do elemento para inserir no próximo.
 *  \sa push_back(), push_front(), insert()
 */
template<typename T>
void LinkedList<T>::insert_sorted(const T& data) {
    if (empty()) {
      push_front(data);
    } else {
      Node* current = head;
      std::size_t posicao = size();
      /*while (current->next() != nullptr && data > current->data()) {
        current = current->next();
        posicao++;
      }*/
      for (auto i = 0u; i < size(); ++i) {
        if (!(data > current->data())) {
          posicao = i;
          break;
        }
        current = current->next();
      }
      insert(data, posicao);
    }
    /* if (empty()) {
        push_front(data);
    } else {
        Node* actual = head;
        Node* last = head;

        do {
          last = actual;
          actual = actual->next();
        } while (actual != nullptr && data > last->data());

        while (actual->next() != nullptr && data > actual->data()) {
            printf("ac=%p , last=%p\n", actual, last);
            last = actual;
            printf("last=%p\n", last);
            actual = actual->next();
            printf("ac=%p\n", actual);
        }
        if (last == head) {
          if (data > last->data())
            insert(data, last);
          else
            push_front(data);
        } else {
          insert(data, last);
        }
    } */
}

//! Referencia o dado na posição da lista.
/*! Retorna o dado que esta na posição index da lista para uso externo,
 *  caso exista.
 *  Possíveis erros:
 *   - Se o índice não existir.
 *   - Se a lista estiver vazia.
 *  \return T& um dado que será referenciado.
 *  \sa operator[](), at() const, operator[]() const
 */
template<typename T>
T& LinkedList<T>::at(std::size_t index) {
    if (index >= size())
      throw std::out_of_range("Invalid index!");

    Node* current = index == 0? head : before_index(index)->next();
    return current->data();
}

//! Coleta o dado de uma posição específica da lista.
/*! Verificando se a posição for válida, será removido e a lista reorganizada,
 *  depois o dado retirado é retornado e o tamanho decrementado.
 *  Possíveis erros:
 *   - Se o índice não existir.
 *   - Se a lista estiver vazia.
 *  \param index um size_t sendo a posição do dado a ser retirado.
 *  \return T dado genérico retirado da lista.
 *  \sa pop_back(), pop_front(), remove()
 */
template<typename T>
T LinkedList<T>::pop(std::size_t index) {
    if (empty())
        throw std::out_of_range("Empty list");
    if (index >= size())
        throw std::out_of_range("Invalid index!");

    Node* before_out = before_index(index);
    Node* out = size() <= 1 || index == 0? head : before_out->next();
    T& data = out->data();

    if (out == head) {
        data = out->data();
        head = out->next();
    } else {
        before_out->next(out->next());
    }
    delete out;
    size_--;

    return data;
}

//! Coleta o dado do final da lista
/*! Sempre será retirado no final da lista.
 *  Reuso do método pop().
 *  Possíveis erros:
 *   - Se a lista estiver vazia.
 *  \return T dado genérico retirado da lista.
 *  \sa pop(), pop_front(), remove()
 */
template<typename T>
T LinkedList<T>::pop_back() {
    try {
        return pop(size()-1u);
    } catch(std::out_of_range error) {
        throw error;
    }
}

//! Coleta o dado do início da lista.
/*! Sempre será retirado o primeiro dado da lista, caso não esteja vazia.
 *  Reuso do método pop().
 *  Possíveis erros:
 *   - Se a lista estiver vazia.
 *  \return T dado genérico retirado da lista.
 *  \sa pop(), pop_back(), remove()
 */
template<typename T>
T LinkedList<T>::pop_front() {
    return pop(0u);
    /*try {
        return pop(0u);
    } catch(std::out_of_range error) {
        throw error;
    }*/
}

//! Remoção de um dado da lista.
/*! Busca o índice do dado e remove ele da lista.
 *  Reuso do método pop();
 *  Possíveis erros:
 *   - Se a lista estiver vazia.
 *   - O dado não foi encontrado.
 *  \param data um dado T que será removido da lista.
 *  \sa pop(), pop_back(), pop_front()
 */
template<typename T>
void LinkedList<T>::remove(const T& data) {
    pop(find(data));
}

//! lista vazia
/*! Testa se a lista está vazia.
 *  \return um booleano.
 */
template<typename T>
bool LinkedList<T>::empty() const {
    return size() == 0u;
}

//! Contém um dado
/*! Testa se um dado está na lista.
 *  \return um booleano.
 *  \sa find()
 */
template<typename T>
bool LinkedList<T>::contains(const T& data) const {
    return find(data) != size();
}

//! lista vazia
/*! Testa se a lista está vazia.
 *  \return um booleano.
 *  \sa find()
 */
template<typename T>
std::size_t LinkedList<T>::find(const T& data) const {
    std::size_t index = 0u;
    Node* current = head;
    while (index < size()) {
        if (current->data() == data)
            break;
        current = current->next();
        index++;
    }
    return index;
}

//! Tamanho da lista.
/*! Retorna o tamanho (size_) da lista.
 *  \return size_t o tamanho da lista.
 *  \sa max_size()
 */
template<typename T>
std::size_t LinkedList<T>::size() const {
    return size_;
}

//! Tamanho da lista.
/*! Retorna o tamanho (size_) da lista.
 *  \return size_t o tamanho da lista.
 *  \sa max_size()
 */
template<typename T>
void LinkedList<T>::desenha_arvore() const {
  if (size() > 1) {
    auto current = head;
    for (auto i = 0u; i < size()-1u; ++i) {
      printf("%d -> ", current->data());
      current = current->next();
    }
    printf("%d -> %p ....... t%lu\n", current->data(), current->next(), size());
  } else {
    if (size() == 1)
        printf("valor=%d e ac=%p e po=%p\n", head->data(), head, head->next());
  }
}

}  // namespace structures

#endif