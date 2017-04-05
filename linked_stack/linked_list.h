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

 private:
    class Node {  // Elemento
     public:
        //! Construtor usando apenas o dado.
        /*! Construtor usando apenas o dado recebido para a criação.
         *  \param data dado T armazenado pelo node.
         *  \sa Node(const T& data, Node* next)
         */
        explicit Node(const T& data):
        data_{data}
        {}

        //! Construtor de um node completo.
        /*! Construtor de um node com dado e o ponteiro ao próximo node.
         *  \param data dado T armazenado pelo node.
         *  \sa Node(const T& data)
         */
        explicit Node(const T& data, Node* next):
        data_{data},
        next_{next}
        {}

        //! Getter do dado
        /*! Retorna o dado armazenado.
         *  \sa data() const
         *  \return T& referência do dado armazenado.
         */
        T& data() {
            return data_;
        }

        //! Getter constante do dado
        /*! Retorna o dado armazenado.
         *  \sa data() const
         *  \return T& referência do dado armazenado.
         */
        const T& data() const {
            return data_;
        }

        //! Getter do próximo node.
        /*! Retorna o próximo node.
         *  \sa next() const, next(Node* node)
         *  \return Node* Próximo node.
         */
        Node* next() {  // getter: próximo
            return next_;
        }

        //! Getter constante do próximo node.
        /*! Retorna o próximo node.
         *  \sa next(), next(Node* node)
         *  \return Node* Próximo node.
         */
        const Node* next() const {  // getter const: próximo
            return next_;
        }

        //! Setter o próximo node.
        /*! Altera o próximo node.
         *  \sa next(), next() const
         */
        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;  // data_
        Node* next_{nullptr};  // next_
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

    //! Passa pelos nodes até o anterior ao índice procurado.
    /*! Retorna o node anterior ao que se procura.
     *  \sa end()
     *  \return Node* O node anterior ao índice.
     */
    Node* before_index(std::size_t index) {  // node anterior ao index
        auto it = head;
        for (auto i = 1u; i < index; ++i) {
            it = it->next();
        }
        return it;
    }

    void insert(const T& data, Node* before);  // inserir na posicao polimorfico

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
LinkedList<T>::~LinkedList() {
    clear();
}

//! Esvazia a lista.
/*! Retira todos os Nodes.
 */
template<typename T>
void LinkedList<T>::clear() {
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
void LinkedList<T>::push_back(const T& data) {
    try {
        insert(data, size_);
    } catch(std::out_of_range error) {
        throw error;
    }
}

//! Inserção no começo da lista.
/*! Sempre será colocado no início da fila.
 *  Possíveis erros:
 *   - Se a lista estiver cheia.
 *  \param data Dado T que será inserido na fila.
 *  \sa push_back(), insert(), insert_sorted()
 */
template<typename T>
void LinkedList<T>::push_front(const T& data) {
    Node* new_node = new Node(data);
    if (new_node == nullptr)
        throw std::out_of_range("Full list!");

    new_node->next(head);
    head = new_node;
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
void LinkedList<T>::insert(const T& data, std::size_t index) {
    if (index > size_)
        throw std::out_of_range("Invalid index!");

    if (index == 0) {
        push_front(data);
    } else {
        Node* new_node = new Node(data);
        if (new_node == nullptr)
            throw std::out_of_range("Full list!");

        Node* before = before_index(index);
        Node* next = before->next();
        new_node->next(next);
        before->next(new_node);
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
void LinkedList<T>::insert(const T& data, Node* before) {
    Node* new_node = new Node(data);
    if (new_node == nullptr)
        throw std::out_of_range("Full list!");

    new_node->next(before->next());
    before->next(new_node);
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
void LinkedList<T>::insert_sorted(const T& data) {
    if (empty()) {
        push_front(data);
    } else {
        Node* current = head;
        Node* before = head;
        std::size_t position = size();
        for (auto i = 0u; i < size(); ++i) {
            if (!(data > current->data())) {
                position = i;
                break;
            }
            before = current;
            current = current->next();
        }
        position == 0? push_front(data) : insert(data, before);
    }
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
T& LinkedList<T>::at(std::size_t index) {
    if (index >= size())
        throw std::out_of_range("Invalid index or empty list!");

    Node* current = index == 0? head : before_index(index)->next();
    return current->data();
}

//! Coleta o dado de uma posição específica da lista.
/*! Verificando se a posição for válida, será removido e a lista reorganizada,
 *  depois o dado retirado é retornado e o tamanho decrementado.
 *  Possíveis erros:
 *   - Se o índice não existir.
 *   - Se a lista estiver vazia.
 *  \param index Size_t sendo a posição do dado a ser retirado.
 *  \return T dado genérico retirado da lista.
 *  \sa pop_back(), pop_front(), remove()
 */
template<typename T>
T LinkedList<T>::pop(std::size_t index) {
    if (empty())
        throw std::out_of_range("Empty list");
    if (index >= size())
        throw std::out_of_range("Invalid index!");

    if (index == 0)
        return pop_front();

    Node* before_out = before_index(index);
    Node* out = before_out->next();
    T data = out->data();
    before_out->next(out->next());
    size_--;
    delete out;
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
        return pop(size_ - 1u);
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
    if (empty())
        throw std::out_of_range("Empty list!");

    auto out = head;
    T data = out->data();
    head = out->next();
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
 *  \param data T& Dado que se deseja testar a sua existência.
 *  \return um booleano.
 *  \sa find()
 */
template<typename T>
bool LinkedList<T>::contains(const T& data) const {
    return find(data) != size();
}

//! Procura dado.
/*! Procura o índice do dado, caso não achar retorna o tamanho da lista.
 *  \param data T& Dado que se deseja procurar.
 *  \return um booleano.
 *  \sa contains()
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
 */
template<typename T>
std::size_t LinkedList<T>::size() const {
    return size_;
}

}  // namespace structures

#endif
