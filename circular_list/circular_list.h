#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>  //  std::size_t
#include <stdexcept>  //  C++ exceptions

namespace structures {

template<typename T>
class CircularList {
public:
    CircularList();
    ~CircularList();

    void clear(); //  limpar lista

    void push_back(const T& data); //  inserir no fim
    void push_front(const T& data); //  inserir no início
    void insert(const T& data, std::size_t index); //  inserir na posição
    void insert_sorted(const T& data); //  inserir em ordem

    T& at(std::size_t index); //  acessar em um indice (com checagem de limites)
    const T& at(std::size_t index) const; //  versão const do acesso ao indice

    T pop(std::size_t index); //  retirar da posição
    T pop_back(); //  retirar do fim
    T pop_front(); //  retirar do início
    void remove(const T& data); //  remover dado específico

    bool empty() const; //  lista vazia
    bool contains(const T& data) const; //  lista contém determinado dado?
    std::size_t find(const T& data) const; //  posição de um item na lista

    std::size_t size() const; //  tamanho da lista
    void draw_connection();

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
         *  \sa data() const, data(const T& data)
         *  \return T& referência do dado armazenado.
         */
        T& data() {
            return data_;
        }

        //! Getter constante do dado
        /*! Retorna o dado armazenado.
         *  \sa data(), data(const T& data)
         *  \return T& referência do dado armazenado.
         */
        const T& data() const {
            return data_;
        }

        //! Setter do dado
        /*! Retorna o dado armazenado.
         *  \sa data() const, data()
         *  \return T& referência do dado armazenado.
         */
        void data(const T& data) {
            data_ = data;
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
    Node* before_index(std::size_t index) const {  // node anterior ao index
        auto it = head;
        for (auto i = 1u; i < index; ++i) {
            it = it->next();
        }
        return it;
    }

    void insert(const T& data, Node* before);  // inserir na posicao polimorfico

    Node* head{nullptr};  //< head
    std::size_t size_{0u};  //< size_
};

template<typename T>
CircularList<T>::CircularList() {}

template<typename T>
CircularList<T>::~CircularList() {
  clear();
}

template<typename T>
void CircularList<T>::push_back(const T& data) {
  if (empty()) {
    push_front(data);
    head->next(LinkedList<T>::head);
  } else {
    Node* novoHead = new Node(head->data(), head->next());
    head->next(novoHead);
    head->data() = data;
    head = novoHead;
    size_++;
  }
}

template<typename T>
void CircularList<T>::push_front(const T& data);

template<typename T>
void CircularList<T>::insert(const T& data, std::size_t index);

template<typename T>
void CircularList<T>::insert_sorted(const T& data);

template<typename T>
T& CircularList<T>::at(std::size_t index);

template<typename T>
const T& CircularList<T>::at(std::size_t index) const;

template<typename T>
T CircularList<T>::pop(std::size_t index);

template<typename T>
T CircularList<T>::pop_back();

template<typename T>
T CircularList<T>::pop_front();

template<typename T>
void CircularList<T>::remove(const T& data);

template<typename T>
bool CircularList<T>::empty() const;

template<typename T>
bool CircularList<T>::contains(const T& data) const;

template<typename T>
std::size_t CircularList<T>::find(const T& data) const;

template<typename T>
std::size_t CircularList<T>::size() const;

template<typename T>
void CircularList<T>::draw_connection() {
  auto temp = head;
  for (auto i = 0; i < size_+2; ++i) {
    printf("%d -> ", temp->data());
    temp = temp->next();
  }
  printf("%d -> \n", temp->data());
}


}  //  namespace structures

#endif
