//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_DOUBLY_LINKED_LIST_H
#define STRUCTURES_DOUBLY_LINKED_LIST_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

template<typename T>

//! Classe Lista Duplamente Encadeada
/*! Implementação de uma lista se baseando em alocação dinâmica de memória.
 *  Aspectos funcionais:
 *   - Colocar e retirar.
 *   - Testes de vazia, cheia ou que contenha um determinado dado.
 *   - Iniciar e garantir determinada ordem dos elementos.
 *  Características estruturais:
 *   - Através de um HEAD que guarda a referência do primeiro elemento é
 *     possível acessar qualquer outros elemento percorrendo de um elemento
 *     ao próximo.
 *   - Todo elemento sabe quem é seu próximo e seu anterior.
 *   - O tamanho da lista inicia em 0, indicando que a lista esta vazia.
 *
 *  \author João Vicente Souto.
 *  \since 04/04/17
 *  \version 1.0
 */
class DoublyLinkedList {
 public:
    DoublyLinkedList();
    ~DoublyLinkedList();
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
    std::size_t size() const;

 private:
    //! Subclasse Node
    /*! Elemento da minha lista que encapsula o dado,
     *  ponteiro para o próximo e para o anterior.
     */
    class Node {
     public:
        //! Construtor Padrão
        /*! Construtor com apenas o dado.
         *  \param data T& que será armazenado.
         */
        explicit Node(const T& data):
        data_{data}
        {}

        //! Construtor Secundário
        /*! Construtor com dado e o ponteiro para o próximo.
         *  \param data T& que será armazenado.
         *  \param next Node* para o próximo elemento.
         */
        Node(const T& data, Node* next):
        data_{data},
        next_{next}
        {}

        //! Construtor Padrão
        /*! Construtor completo.
         *  \param data T& que será armazenado.
         *  \param next Node* para o próximo elemento.
         *  \param prev Node* para o elemento anterior.
         */
        Node(const T& data, Node* prev, Node* next):
        data_{data},
        prev_{prev},
        next_{next}
        {}

        //! Retorna dado.
        /*! Retorna o dado armazenado.
         *  \sa data() const
         *  \return T& referência do dado armazenado.
         */
        T& data() {
            return data_;
        }

        //! Retorna dado.
        /*! Retorna o dado armazenado.
         *  \sa data()
         *  \return T& referência do dado armazenado.
         */
        const T& data() const {
            return data_;
        }

        //! Getter do node anterior.
        /*! Retorna o node node.
         *  \sa prev() const, prev(Node* node)
         *  \return Node* node anterior.
         */
        Node* prev() {
            return prev_;
        }

        //! Getter do node anterior.
        /*! Retorna o node node.
         *  \sa prev(), prev(Node* node)
         *  \return Node* node anterior.
         */
        const Node* prev() const {
            return prev_;
        }

        //! Setter o node anterior.
        /*! Altera o próximo node.
         *  \param Node* novo node anterior.
         *  \sa prev(), prev() const
         */
        void prev(Node* node) {
            prev_ = node;
        }

        //! Getter do próximo node.
        /*! Retorna o próximo node.
         *  \sa next() const, next(Node* node)
         *  \return Node* Próximo node.
         */
        Node* next() {
            return next_;
        }

        //! Getter constante do próximo node.
        /*! Retorna o próximo node.
         *  \sa next(), next(Node* node)
         *  \return Node* Próximo node.
         */
        const Node* next() const {
            return next_;
        }

        //! Setter o próximo node.
        /*! Altera o próximo node.
         *  \sa next(), next() const
         */
        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;  //!< data
        Node* prev_{nullptr};  //!< prev
        Node* next_{nullptr};  //!< next
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

    Node* head{nullptr};  //!< head
    std::size_t size_{0u};  //!< size
};

//! Construtor padrão
/*! Sem parâmetros, a lista já contém os valores padrões já na definição.
 */
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() {}

//! Destrutor
/*! Método para desalocar a memória utilizada pela lista.
 */
template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

//! Esvazia a lista.
/*! Retira todos os Nodes.
 */
template<typename T>
void DoublyLinkedList<T>::clear() {
    while (!empty())
        pop_front();
}

//! Inserção no fim da lista.
/*! Sempre será colocado no final da lista, caso não esteja vazia.
 *  Possíveis erros:
 *   - Se a lista estiver cheia.
 *  \param data Dado T que será inserido na fila.
 *  \sa push_front(), insert(), insert_sorted()
 */
template<typename T>
void DoublyLinkedList<T>::push_back(const T& data) {
    insert(data, size_);
}

//! Inserção no começo da lista.
/*! Sempre será colocado no início da fila.
 *  Possíveis erros:
 *   - Se a lista estiver cheia.
 *  \param data Dado T que será inserido na fila.
 *  \sa push_back(), insert(), insert_sorted()
 */
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

//! Inserção em qualquer lugar da lista.
/*! Verificando se a posição for válida, depois inserindo onde se deve.
 *  Possíveis erros:
 *   - Se o índice não existir.
 *   - Se a lista estiver cheia.
 *  \param data Dado T que será inserido na fila.
 *  \param index Size_t indicando a posição que será inserido o dado.
 *  \sa push_back(), push_front(), insert_sorted()
 */
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
            new_node->prev(before);
        } else {
            Node* current = node_of_index(index);
            new_node->next(current);
            current->prev()->next(new_node);
            new_node->prev(current->prev());
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
void DoublyLinkedList<T>::insert(const T& data, Node* previous) {
    Node* new_node = new Node(data);
    if (new_node == nullptr)
        throw std::out_of_range("Full list!");
    if (empty()) {
      head = new_node;
    } else {
      if (previous->next() != nullptr)
        previous->next()->prev(new_node);
      new_node->next(previous->next());
      previous->next(new_node);
      new_node->prev(previous);
    }
    size_++;
}

//! Inserção ordenada na lista.
/*! Será buscado a posição ordenada do dado passado por parâmetro. A forma de
 *  comparação utilizada será o operador ">" que deve ser sobrescrito por quem
 *  for utilizar a lista e este método.
 *  Possíveis erros:
 *   - Se a lista estiver cheia.
 *  \param data Dado T que será inserido na fila.
 *  \param Node* Ponteiro do elemento para inserir no próximo.
 *  \sa push_back(), push_front(), insert()
 */
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
            if (current->next() != nullptr)
                current = current->next();
        }
        position == 0? push_front(data) :
        position == size_? insert(data, current) :
                           insert(data, current->prev());
    }
}

//! Retira o dado de uma posição específica da lista.
/*! Verificando se a posição for válida, será removido e os ponteiros
 *  reorganizados, depois o dado retirado é retornado e o tamanho decrementado.
 *  Possíveis erros:
 *   - Se o índice não existir.
 *   - Se a lista estiver vazia.
 *  \param index Size_t sendo a posição do dado a ser retirado.
 *  \return T dado genérico retirado da lista.
 *  \sa pop_back(), pop_front(), remove()
 */
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
    if (out->next() != nullptr)
      out->next()->prev(out->prev());
    size_--;
    delete out;
    return data;
}

//! Retira o dado do final da lista
/*! Sempre será retirado no final da lista.
 *  Reuso do método pop().
 *  Possíveis erros:
 *   - Se a lista estiver vazia.
 *  \return T dado genérico retirado da lista.
 *  \sa pop(), pop_front(), remove()
 */
template<typename T>
T DoublyLinkedList<T>::pop_back() {
    return pop(size_ - 1u);
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
T DoublyLinkedList<T>::pop_front() {
    if (empty())
        throw std::out_of_range("Empty list!");

    auto out = head;
    T data = out->data();
    head = out->next();
    if (head != nullptr)
        head->prev(nullptr);
    size_--;
    delete out;
    return data;
}

//! Remoção de um dado da lista.
/*! Busca o índice do dado e remove ele da lista.
 *  Reuso do método pop() e find();
 *  Possíveis erros:
 *   - Se a lista estiver vazia.
 *   - O dado não foi encontrado.
 *  \param data Dado T que será removido da lista.
 *  \sa pop(), pop_back(), pop_front(), find()
 */
template<typename T>
void DoublyLinkedList<T>::remove(const T& data) {
    pop(find(data));
}

//! lista vazia
/*! Testa se a lista está vazia.
 *  \return um booleano.
 */
template<typename T>
bool DoublyLinkedList<T>::empty() const {
    return size_ == 0u;
}

//! Contém um dado
/*! Testa se um dado está na lista.
 *  \param data T& Dado que se deseja testar a sua existência.
 *  \return um booleano.
 *  \sa find()
 */
template<typename T>
bool DoublyLinkedList<T>::contains(const T& data) const {
    return find(data) != size_;
}

//! Referencia o dado na posição da lista.
/*! Retorna o dado que esta na posição index da lista para uso externo,
 *  caso exista.
 *  Possíveis erros:
 *   - Se o índice não existir.
 *   - Se a lista estiver vazia.
 *  \param index Size_t índice do node.
 *  \return T& Dado que será referenciado.
 */
template<typename T>
T& DoublyLinkedList<T>::at(std::size_t index) {
    if (index >= size())
        throw std::out_of_range("Invalid index or empty list!");

    Node* current = index == 0? head : node_of_index(index);
    return current->data();
}

//! Referencia o dado na posição da lista / CONSTANTE.
/*! Retorna o dado que esta na posição index da lista para uso externo,
 *  caso exista.
 *  Possíveis erros:
 *   - Se o índice não existir.
 *   - Se a lista estiver vazia.
 *  \param index Size_t índice do node.
 *  \return T& Dado que será referenciado.
 */
template<typename T>
const T& DoublyLinkedList<T>::at(std::size_t index) const {
    if (index >= size())
        throw std::out_of_range("Invalid index or empty list!");

    Node* current = index == 0? head : node_of_index(index);
    return current->data();
}

//! Procura dado.
/*! Procura o índice do dado, caso não achar retorna o tamanho da lista.
 *  \param data T& Dado que se deseja procurar.
 *  \return um booleano.
 *  \sa contains()
 */
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

//! Tamanho da lista.
/*! Retorna o tamanho (size_) da lista.
 *  \return size_t o tamanho da lista.
 */
template<typename T>
std::size_t DoublyLinkedList<T>::size() const {
    return size_;
}

}  // namespace structures

#endif
