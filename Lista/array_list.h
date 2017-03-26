//!  Copyright [2017] <João Vicente Souto>

#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions


namespace structures {

//! Classe Lista
/*! Implementação de uma lista. Ela possui o comportamento de uma lista normal,
 *  Aspectos funcionais:
 *   - Pode ser ordenada ou não.
 *   - É possível inserir ou retirar de qualquer lugar da lista, pelo índice ou
 *     pelo próprio dado.
 *  Características estruturais:
 *   - Implementada em um vetor unidimensional.
 *   - Índice será baseado no tamanho (size_) que terá comportamento de um
 *     "unsigned", assumindo o valor 0 quando a lista estivesse vázia.
 *  \author João Vicente Souto.
 *  \since 17/03/17
 *  \version 1.0
 */
template<typename T>
class ArrayList {
 public:
    ArrayList();
    explicit ArrayList(std::size_t max_size);
    ~ArrayList();

    void clear();
    void push_back(const T& data);
    void push_front(const T& data);
    void insert(const T& data, std::size_t index);
    void insert_sorted(const T& data);
    T pop(std::size_t index);
    T pop_back();
    T pop_front();
    void remove(const T& data);
    bool full() const;
    bool empty() const;
    bool contains(const T& data) const;
    std::size_t find(const T& data) const;
    std::size_t size() const;
    std::size_t max_size() const;
    T& at(std::size_t index);
    T& operator[](std::size_t index);
    const T& at(std::size_t index) const;
    const T& operator[](std::size_t index) const;

 private:
    T* contents;  //!< Vetor de tipo genérico para armazenar a lista.
    std::size_t size_;  //!< Tamanho atual da lista.
    std::size_t max_size_;  //!< Tamanho máximo da lista.

    static const auto DEFAULT_MAX = 10u;   //!< Tamanho padrão da lista.
};

//! Construtor padrão
/*! Sem parâmetros, a lista é inicializada com valores padrões.
 *  Obs.: Uso do construtor com parâmetro para reuso do código.
 *  \sa ArrayStack(std::size_t max)
 */
template<typename T>
ArrayList<T>::ArrayList() {
    ArrayList(DEFAULT_MAX);
}

//! Construtor passando o tamanho da lista.
/*! Usando parâmetro max_size o usuário pode criar uma fila de qualquer tamanho.
 *  \param max_size um size_t contendo o tamanho da fila que deve ser criada.
 *  \sa ArrayStack()
 */
template<typename T>
ArrayList<T>::ArrayList(std::size_t max_size) {
    max_size_ = max_size;
    contents = new T[max_size_];
    size_ = 0u;
}

//! Destrutor
/*! Método para desalocar a memória utilizada pela lista.
 */
template<typename T>
ArrayList<T>::~ArrayList() {
    delete[] contents;
}

//! Esvazia a fila.
/*! Atualiza o tamanho da lista para 0, indicando que a lista está vazia sem
 *  precisar remover os dados da mesma.
 */
template<typename T>
void ArrayList<T>::clear() {
    size_ = 0u;
}

//! Inserção no fim da lista.
/*! Sempre será colocado no final da fila, caso não esteja vazia.
 *  Possíveis erros:
 *   - Se a lista estiver cheia.
 *  \param data um dado T que será inserido na fila.
 *  \sa push_front(), insert(), insert_sorted()
 */
template<typename T>
void ArrayList<T>::push_back(const T& data) {
    if (full())
        throw std::out_of_range("Lista cheia!");
    insert(data, size());
}

//! Inserção no começo da lista.
/*! Sempre será colocado no início da fila.
 *  Possíveis erros:
 *   - Se a lista estiver cheia.
 *  \param data um dado T que será inserido na fila.
 *  \sa push_back(), insert(), insert_sorted()
 */
template<typename T>
void ArrayList<T>::push_front(const T& data) {
    if (full())
        throw std::out_of_range("Lista cheia!");
    insert(data, 0u);
}

//! Inserção em qualquer lugar da lista.
/*! Verificando se a posição for válida, será inserido e a lista reorganizada.
 *  Possíveis erros:
 *   - Se o índice não existir.
 *   - Se a lista estiver cheia.
 *  \param data um dado T que será inserido na fila.
 *  \param index um size_t indicando a posição que será inserido o dado.
 *  \sa push_back(), push_front(), insert_sorted()
 */
template<typename T>
void ArrayList<T>::insert(const T& data, std::size_t index) {
    if (index > size_)
        throw std::out_of_range("Posição não existe!");

    if (full())
        throw std::out_of_range("Lista cheia!");

    for (int atual = size_; atual > index; atual--)
        contents[atual] = contents[atual-1];
    size_++;
    contents[index] = data;
}

//! Inserção ordenada na lista.
/*! Será buscado a posição ordenada do dado passado por parâmetro. A forma de
 *  comparação utilizada será o operador "<" que deve ser sobrescrito por quem
 *  for utilizar a lista e este método.
 *  Possíveis erros:
 *   - Se a lista estiver cheia.
 *  \param data um dado T que será inserido na fila.
 *  \sa push_back(), push_front(), insert()
 */
template<typename T>
void ArrayList<T>::insert_sorted(const T& data) {
    if (full())
        throw std::out_of_range("Lista cheia!");

    std::size_t index = 0u;
    while (index < size_ && data > contents[index])
        index++;
    insert(data, index);
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
T ArrayList<T>::pop(std::size_t index) {
    if (index >= size_)
        throw std::out_of_range("Posição não existe!");
    if (empty())
        throw std::out_of_range("Lista vazia!");

    size_--;
    T tmp = contents[index];
    for (auto atual = index; atual < size_; atual++)
        contents[atual] = contents[atual+1];
    return tmp;
}

//! Coleta o dado do final da lista
/*! Sempre será retirado no início da fila.
 *  Reuso do método pop().
 *  Possíveis erros:
 *   - Se a lista estiver vazia.
 *  \return T dado genérico retirado da lista.
 *  \sa pop(), pop_front(), remove()
 */
template<typename T>
T ArrayList<T>::pop_back() {
    if (empty())
        throw std::out_of_range("Lista vazia!");
    return pop(size_-1);
}

//! Coleta o dado do início da lista.
/*! Sempre será retirado o primeiro dado da fila, caso não esteja vazia.
 *  Reuso do método pop().
 *  Possíveis erros:
 *   - Se a lista estiver vazia.
 *  \return T dado genérico retirado da lista.
 *  \sa pop(), pop_back(), remove()
 */
template<typename T>
T ArrayList<T>::pop_front() {
    if (empty())
        throw std::out_of_range("Lista vazia!");
    return pop(0u);
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
void ArrayList<T>::remove(const T& data) {
    if (empty())
        throw std::out_of_range("Lista vazia!");
    if (!contains(data))
        throw std::out_of_range("Dado não encontrado!");

    std::size_t index = find(data);
    pop(index);
}

//! Fila cheia
/*! Testa se a fila está cheia.
 *  \return um booleano.
 *  \sa empty()
 */
template<typename T>
bool ArrayList<T>::full() const {
    return size_ == max_size_;
}

//! Fila vazia
/*! Testa se a fila está vazia.
 *  \return um booleano.
 *  \sa full()
 */
template<typename T>
bool ArrayList<T>::empty() const {
    return size_ == 0u;
}

//! Contém um dado
/*! Testa se um dado está na lista.
 *  \return um booleano.
 *  \sa find()
 */
template<typename T>
bool ArrayList<T>::contains(const T& data) const {
    return find(data) != size_;
}

//! Fila vazia
/*! Testa se a fila está vazia.
 *  \return um booleano.
 *  \sa find()
 */
template<typename T>
std::size_t ArrayList<T>::find(const T& data) const {
    std::size_t index = 0u;
    while (index < size_) {
        if (contents[index] == data)
            break;
        index++;
    }
    return index;
}

//! Tamanho da lista.
/*! Retorna o tamanho (size_) da fila.
 *  \return size_t referente ao tamanho da lista.
 *  \sa max_size()
 */
template<typename T>
std::size_t ArrayList<T>::size() const {
    return size_;
}

//! Tamanho máximo da lista.
/*! Retorna o maior tamanho possível da lista (max_size_).
 *  \return size_t referente ao max_size_.
 *  \sa size()
 */
template<typename T>
std::size_t ArrayList<T>::max_size() const {
    return max_size_;
}

//! Referencia o dado no final da fila.
/*! Retorna o dado que esta no final da fila para uso externo, caso exista.
 *  Possíveis erros:
 *   - Se o índice não existir.
 *   - Se a lista estiver vazia.
 *  \return T& um dado que será referenciado.
 *  \sa operator[](), at() const, operator[]() const
 */
template<typename T>
T& ArrayList<T>::at(std::size_t index) {
    if (index >= size_)
        throw std::out_of_range("Posição não existe!");
    if (empty())
        throw std::out_of_range("Lista Vazia!");
    return contents[index];
}

//! Referencia o dado no final da fila.
/*! Retorna o dado que esta no final da fila para uso externo, caso exista.
 *  Possíveis erros:
 *   - Se o índice não existir.
 *   - Se a lista estiver vazia.
 *  \return T& um dado que será referenciado.
 *  \sa at(), at() const, operator[]() const
 */
template<typename T>
T& ArrayList<T>::operator[](std::size_t index) {
    if (index >= size_)
        throw std::out_of_range("Posição não existe!");
    if (empty())
        throw std::out_of_range("Lista Vazia!");
    return contents[index];
}

//! Referencia o dado no final da fila.
/*! Retorna o dado que esta no final da fila para uso externo, caso exista.
 *  Possíveis erros:
 *   - Se o índice não existir.
 *   - Se a lista estiver vazia.
 *  \return T& um dado que será referenciado.
 *  \sa at(), operator[](), operator[]() const
 */
template<typename T>
const T& ArrayList<T>::at(std::size_t index) const {
    if (index >= size_)
        throw std::out_of_range("Posição não existe!");
    if (empty())
        throw std::out_of_range("Lista Vazia!");
    return contents[index];
}

//! Referencia o dado no final da fila.
/*! Retorna o dado que esta no final da fila para uso externo, caso exista.
 *  Possíveis erros:
 *   - Se o índice não existir.
 *   - Se a lista estiver vazia.
 *  \return T& um dado que será referenciado.
 *  \sa at(), operator[](), at() const
 */
template<typename T>
const T& ArrayList<T>::operator[](std::size_t index) const {
    if (index >= size_)
        throw std::out_of_range("Posição não existe!");
    if (empty())
        throw std::out_of_range("Lista Vazia!");
    return contents[index];
}

}  // namespace structures

#endif
