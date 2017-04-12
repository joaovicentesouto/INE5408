#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>


namespace structures {

template<typename T>
class CircularList {
public:
    CircularList();
    ~CircularList();

    void clear(); // limpar lista

    void push_back(const T& data); // inserir no fim
    void push_front(const T& data); // inserir no início
    void insert(const T& data, std::size_t index); // inserir na posição
    void insert_sorted(const T& data); // inserir em ordem

    T& at(std::size_t index); // acessar em um indice (com checagem de limites)
    const T& at(std::size_t index) const; // versão const do acesso ao indice

    T pop(std::size_t index); // retirar da posição
    T pop_back(); // retirar do fim
    T pop_front(); // retirar do início
    void remove(const T& data); // remover dado específico

    bool empty() const; // lista vazia
    bool contains(const T& data) const; // lista contém determinado dado?
    std::size_t find(const T& data) const; // posição de um item na lista

    std::size_t size() const; // tamanho da lista
};

}

#endif
