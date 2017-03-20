//!  Copyright [2017] <João Vicente Souto>

#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

    template<typename T>

    //! Classe Pilha
    /*! Implementação de uma pilha, um dos tipos de estruturas de dados vistos
     *  durante o sementre. Possui o comportamento de uma pilha de pratos, na
     *  qual todas as formas de acesso e modificação se dão pelo dado que está
     *  no topo da pilha.
     *  \author João Vicente Souto.
     *  \since 17/03/17
     *  \version 1.0
     */
    class ArrayStack {
    public:
        ArrayStack();
        explicit ArrayStack(std::size_t max);
        ~ArrayStack();
        void push(const T& data);
        T pop();
        T& top();
        void clear();
        std::size_t size();
        std::size_t max_size();
        bool empty();
        bool full();

    private:
        T* contents;  //!< Array de tipo genérico para armazenar a pilha.
        int top_;     //!< Topo da pilha.
        std::size_t max_size_;  //!< Tamanho máximo da pilha.
        static const auto DEFAULT_SIZE = 10u;  //!< Tamanho padrão da pilha.
    };

    //! Construtor padrão
    /*! Sem parâmetros, a pilha é inicializada com valores padrões.
     *  \sa ArrayStack(std::size_t max)
     */
    template<typename T>
    ArrayStack<T>::ArrayStack() {
        max_size_ = DEFAULT_SIZE;
        contents = new T[max_size_];
        top_ = -1;
    }

    //! Construtor passando o tamanho da pilha.
    /*! Usando parâmetro max o usuário pode criar uma pilha de qualquer tamanho.
     *  \param max um size_t contendo o tamanho da pilha que deve ser criada.
     *  \sa ArrayStack()
     */
    template<typename T>
    ArrayStack<T>::ArrayStack(std::size_t max) {
        max_size_ = max;
        contents = new T[max_size_];
        top_ = -1;
    }

    //! Destrutor
    /*! Método para desalocar a memória utilizada pela pilha.
     */
    template<typename T>
    ArrayStack<T>::~ArrayStack() {
        delete contents;
    }

    //! Inserção de um novo dado na pilha.
    /*! Se baseando no topo da pilha, será alocado na próxima posição o novo dado
     *  e atualizar o índice do topo.
     *  \param data un novo dado que será inserido na pilha.
     *  \sa pop(), top(), clear()
     */
    template<typename T>
    void ArrayStack<T>::push(const T& data) {
        if (full())
            throw std::out_of_range("Pilha cheia!");
        else
            contents[++top_] = data;
    }

    //! Remoção de um dado da pilha.
    /*! Retira o dado que está no topo da pilha e atualizar índice do topo.
     *  \sa push(), top(), clear()
     */
    template<typename T>
    T ArrayStack<T>::pop() {
        if (empty())
            throw std::out_of_range("Pilha vazia!");
        else
            return contents[top_--];
    }

    //! Referencia o dado no topo da pilha.
    /*! Retorna o dado do topo da pilha que será referenciado para uso externo,
     *  caso exista.
     *  \return T& um dado para ser referenciado.
     *  \sa push(), pop(), clear()
     */
    template<typename T>
    T& ArrayStack<T>::top() {
        if (empty())
            throw std::out_of_range("Pilha vazia!");
        else
            return contents[top_];
    }

    //! Esvazia a pilha.
    /*! Atualiza o índice do topo para -1, indicando que a pilha esta vazia.
     *  \sa push(), pop(), top()
     */
    template<typename T>
    void ArrayStack<T>::clear() {
        top_ = -1;
    }

    //! Quantidade de dados na pilha.
    /*! Retorna o tamanho da pilha convertido para size_t, seguindo a lógica
     *  do índice+1 considerando que o índice inicial em -1.
     *  \return size_t referente ao tamanho da pilha.
     *  \sa max_size()
     */
    template<typename T>
    std::size_t ArrayStack<T>::size() {
        return (std::size_t) (top_+1);
    }

    //! Maior tamanho possível.
    /*! Retorna o maior tamanho possível armazenado na variavel max_size_.
     *  \return size_t referente ao max_size_.
     *  \sa size()
     */
    template<typename T>
    std::size_t ArrayStack<T>::max_size() {
        return max_size_;
    }

    //! Pilha vazia
    /*! Testa se a pilha está vazia.
     *  \return valor booleano.
     *  \sa full()
     */
    template<typename T>
    bool ArrayStack<T>::empty() {
        return top_ == -1;
    }

    //! Pilha cheia
    /*! Testa se a pilha está cheia.
     *  \return valor booleano.
     *  \sa empty()
     */
    template<typename T>
    bool ArrayStack<T>::full() {
        return top_+1 == static_cast<int>(max_size_);
    }

}  // namespace structures

#endif
