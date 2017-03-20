//!  Copyright [2017] <João Vicente Souto>

#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions

namespace structures {

    template<typename T>

    //! Classe Fila
    /*! Implementação de uma fila, um dos tipos de estruturas de dados vistos
     *  durante o sementre. A fila possui o comportamento de uma fila normal,
     *  onde o primeiro que entre é o primeiro a sair.
     *  \author João Vicente Souto.
     *  \since 17/03/17
     *  \version 1.0
     */
    class ArrayQueue {
    public:
        ArrayQueue();
        explicit ArrayQueue(std::size_t max);
        ~ArrayQueue();
        void enqueue(const T& data);
        T dequeue();
        T& back();
        void clear();
        std::size_t size();
        std::size_t max_size();
        bool empty();
        bool full();

    private:
        T* contents;  //!< Array de tipo genérico para armazenar a fila.
        std::size_t size_;  //!< Tamanho atual da fila.
        std::size_t max_size_;  //!< Tamanho máximo da fila.
        static const auto DEFAULT_SIZE = 10u;   //!< Tamanho padrão da fila.
    };

    //! Construtor padrão
    /*! Sem parâmetros, a fila é inicializada com valores padrões.
     *  \sa ArrayStack(std::size_t max)
     */
    template<typename T>
    ArrayQueue<T>::ArrayQueue() {
        max_size_ = DEFAULT_SIZE;
        contents = new T[max_size_];
        size = -1;
    }

    //! Construtor passando o tamanho da fila.
    /*! Usando parâmetro max o usuário pode criar uma fila de qualquer tamanho.
     *  \param max um size_t contendo o tamanho da fila que deve ser criada.
     *  \sa ArrayStack()
     */
    template<typename T>
    ArrayQueue<T>::ArrayQueue(std::size_t max) {
        max_size_ = max;
        contents = new T[max_size_];
        size_ = -1;
    }

    //! Destrutor
    /*! Método para desalocar a memória utilizada pela fila.
     */
    template<typename T>
    ArrayQueue<T>::~ArrayQueue() {
        delete contents;
    }

    //! Inserção de um novo dado na fila.
    /*! Sempre será colocado no final da fila, caso não esteja vazia.
     *  \param data um novo dado que será inserido na fila.
     *  \sa dequeue(), back(), clear()
     */
    template<typename T>
    void ArrayQueue<T>::enqueue(const T& data) {
        if (full())
            throw std::out_of_range("Fila cheia!");
        else
            contents[++size_] = data;
    }

    //! Remoção de um dado da fila.
    /*! Sempre será removido o primeiro dado da fila, caso não esteja vazia,
     *  e em seguida os dados são reorganizados uma posição a frente da atual.
     *  \sa enqueue(), back(), clear()
     */
    template<typename T>
    T ArrayQueue<T>::dequeue() {
        if (empty())
            throw std::out_of_range("Fila vazia!");
        else {
            T tmp = contents[0];
            for (int i = 0; i < static_cast<int>(size_); i++)
                contents[i] = contents[i+1];
            size_--;
            return tmp;
        }
    }

    //! Referencia o dado no final da fila.
    /*! Retorna o dado que esta no final da fila para uso externo, caso exista.
     *  \return T7 um dado que será referenciado.
     *  \sa enqueue(), dequeue(), clear()
     */
    template<typename T>
    T& ArrayQueue<T>::back() {
        if (empty())
            throw std::out_of_range("Fila vazia!");
        else
            return contents[size_];
    }

    //! Esvazia a fila.
    /*! Atualiza o tamanho da fila para -1, indicando que a fila esta vazia.
     *  \sa enqueue(), dequeue(), back()
     */
    template<typename T>
    void ArrayQueue<T>::clear() {
        size_ = -1;
    }

    //! Quantidade de dados na fila.
    /*! Retorna o tamanho da fila somando-se 1 porque a lógica do tamanho da
     *  fila inicia em -1.
     *  \return um size_t referente ao tamanho da fila.
     *  \sa max_size()
     */
    template<typename T>
    std::size_t ArrayQueue<T>::size() {
        return size_+1;
    }

    //! Maior tamanho possível.
    /*! Retorna o maior tamanho possível armazenado na variavel max_size_.
     *  \return um size_t referente ao max_size_.
     *  \sa size()
     */
    template<typename T>
    std::size_t ArrayQueue<T>::max_size() {
        return max_size_;
    }

    //! Fila vazia
    /*! Testa se a fila está vazia.
     *  \return um booleano.
     *  \sa full()
     */
    template<typename T>
    bool ArrayQueue<T>::empty() {
        return static_cast<int>(size_) == -1;
    }

    //! Fila cheia
    /*! Testa se a fila está cheia.
     *  \return um booleano.
     *  \sa empty()
     */
    template<typename T>
    bool ArrayQueue<T>::full() {
        return size_ == max_size_-1;
    }

}  // namespace structures

#endif
