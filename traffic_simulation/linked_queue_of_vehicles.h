//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_LINKED_QUEUE_OF_VEHICLES_H
#define STRUCTURES_LINKED_QUEUE_OF_VEHICLES_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

#include "./vehicle.h"
#include "./structures/linked_queue.h"

namespace structures {

  //! Classe LinkedQueueOfVehicles
  /*! Classe pai com as características básicas das estradas da
   *  simulação.
   *  \author João Vicente Souto.
   *  \since 25/04/17
   *  \version 1.0
   */
class LinkedQueueOfVehicles : private LinkedQueue<Vehicle*> {
 public:
    LinkedQueueOfVehicles(size_t speed, size_t max_size);
    ~LinkedQueueOfVehicles();

    void clear();
    virtual void enqueue(Vehicle* data);
    Vehicle* dequeue();
    Vehicle* front() const;
    Vehicle* back() const;

    size_t time_of_route();

    char type() const;
    char* name() const;
    size_t speed() const;
    size_t size() const;
    size_t max_size() const;
    size_t input_counter() const;
    size_t output_counter() const;

    bool empty() const;
    bool full(const Vehicle* data) const;

 protected:
    typedef std::size_t size_t;    //!< Conveniência
    char _type{'b'};    //!< Tipo da rua
    char* _name{(char*)"base\0"};    //!< Nome da rua
    size_t _speed,  //!< Velocidade
           _max_size,    //!< Tamanho máximo
           _size{0u},  //!< Tamanho atual
           _input_counter{0u},  //!< Entrada de veículos
           _output_counter{0u};  //!< Saída de veículos
};

//! Construtor
/*! Construtor padrão
 *  \param speed Velocidade
 *  \param max_size Tamanho máximo
 */
LinkedQueueOfVehicles::LinkedQueueOfVehicles(size_t speed, size_t max_size) :
LinkedQueue<Vehicle*>::LinkedQueue(),
_speed{speed},
_max_size{max_size}
{}

  //! Destrutor
  /*! Nada alocado dinamicamente
   */
LinkedQueueOfVehicles::~LinkedQueueOfVehicles() {
    LinkedQueue<Vehicle*>::~LinkedQueue();
}

//! Limpa estrada
/*! Limpa fila
 */
void LinkedQueueOfVehicles::clear() {
    LinkedQueue<Vehicle*>::clear();
}

//! Insere veículo
/*! Coloca um veículo no final da estrada.
 *  \param data Veículo que será inserido.
 */
void LinkedQueueOfVehicles::enqueue(Vehicle* data) {
    if (full(data))
        throw std::out_of_range("Full queue!");
    LinkedQueue<Vehicle*>::enqueue(data);
    _size += data->size();
    ++_input_counter;
}

//! Retira veículo
/*! Retira o veículo na frente da fila.
 *  \return Vehicle* primeiro veículo da estrada.
 */
Vehicle* LinkedQueueOfVehicles::dequeue() {
    Vehicle* out = LinkedQueue<Vehicle*>::dequeue();
    _size -= out->size();
    ++_output_counter;
    return out;
}

//! Primeiro veículo.
/*! Mostra o primeiro veículo da estrada.
 *  \return Vehicle* primeiro veículo da estrada.
 */
Vehicle* LinkedQueueOfVehicles::front() const {
    return LinkedQueue<Vehicle*>::front();
}

//! Segundo veículo.
/*! Mostra o segundo veículo da estrada.
 *  \return Vehicle* segundo veículo da estrada.
 */
Vehicle* LinkedQueueOfVehicles::back() const {
    return LinkedQueue<Vehicle*>::back();
}

//! Tempo de percurso
/*! Baseado no tamanho máximo e Velocidade.
 *  \return size_t Tempo de percurso
 */
size_t LinkedQueueOfVehicles::time_of_route() {
  return (size_t) _max_size/(_speed/3.6);  //< km/h => m/s
}

//! Tipo da estrada
/*! Retorna o tipo da estrada:
 *    - 'b' : base
 *    - 'a' : aferente / EntryRoad
 *    - 'e' : eferente / ExitRoad
 *  \return char Tipo da estrada.
 */
char LinkedQueueOfVehicles::type() const {
  return _type;
}

//! O nome da estrada
/*! Retorna o nome da estrada.
 *  \return char* nome da estrada
 */
char* LinkedQueueOfVehicles::name() const {
  return _name;
}

//! Velocidade da estrada
/*! Retorna a velocidade da estrada
 *  \return size_t velocidade
 */
size_t LinkedQueueOfVehicles::speed() const {
    return _speed;
}

//! Tamanho atual
/*! Retorna o tamanho atual da estrada.
 *  \return size_t tamanho
 */
size_t LinkedQueueOfVehicles::size() const {
    return _size;
}

//! Tamanho máximo
/*! Retorna o tamanho máximo da estrada.
 *  \return size_t Tamanho máximo
 */
size_t LinkedQueueOfVehicles::max_size() const {
    return _max_size;
}

//! Contador de entradas
/*! Retorna a quantidade de entradas que ocorreram
 *  \return size_t quantidade de entradas
 */
size_t LinkedQueueOfVehicles::input_counter() const {
  return _input_counter;
}

//! Contador de saídas
/*! Retorna a quantidade de saídas que ocorreram
 *  \return size_t quantidade de saídas
 */
size_t LinkedQueueOfVehicles::output_counter() const {
  return _output_counter;
}

//! Estrada vazia?
/*! Retorna verdadeiro se a estrada está vazia
 *  \return size_t Verifica se está vazia
 */
bool LinkedQueueOfVehicles::empty() const {
    return _size == 0u;
}

//! Estrada cheia?
/*! Retorna verdadeiro se a estrada está vazia se baseando
 *  no tamanho do veículo e se ele consegue entrar na estrada.
 *  \return size_t Verifica se tem espaço pra outro carro.
 */
bool LinkedQueueOfVehicles::full(const Vehicle* data) const {
  return max_size() < data->size()+size();
}

}  // namespace structures

#endif
