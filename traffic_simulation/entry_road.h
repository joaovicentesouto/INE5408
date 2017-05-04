//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_ENTRY_ROAD_H
#define STRUCTURES_ENTRY_ROAD_H

#include <cstdint>  // std::std::size_t
#include <stdexcept>  // C++ exceptions
#include <cstdlib>
#include <stdlib.h>
#include "./vehicle.h"
#include "./structures/array_list.h"
#include "./linked_queue_of_vehicles.h"

namespace structures {

//! Classe Estrada de entrada
/*! Especialização da LinkedQueueOfVehicles com características
 *  especiais de uma estrada de entrada na simulação.
 *  \author João Vicente Souto.
 *  \since 25/04/17
 *  \version 1.0
 */
class EntryRoad : public LinkedQueueOfVehicles {
 public:
    EntryRoad(char* name,
              std::size_t speed,
              std::size_t max_size,
              std::size_t average,
              std::size_t variation,
              std::size_t prob_left,
              std::size_t prob_front,
              std::size_t prob_right);
    ~EntryRoad();

    void crossroads(void *left, void *front, void *right);
    void* crossroads(std::size_t index);

    virtual void enqueue(Vehicle* data);

    std::size_t direction_probability();
    std::size_t input_frequency();

 private:
    std::size_t _average,      //!< Tamanho do intervalo de tempo de entrada
           _variation,  //!< Menor valor no intervalo
           _prob_left,    //!< Probabilidade de virar a esquerda
           _prob_front,   //!< Probabilidade de seguir em frente
           _prob_right;   //!< Probabilidade de virar a direita
    ArrayList<void*> _crossroads{3u};  //!< Possíveis destinos
};

//! Construtor
/*! Construtor padrão
 *  \param name Nome da estrada
 *  \param speed Velocidade
 *  \param max_size Tamanho máximo
 *  \param average Tamanho do intervalo de entrada
 *  \param variation Menor valor no intervalo
 *  \param prob_left Probabilidade de virar a esquerda
 *  \param prob_front Probabilidade de seguir em frente
 *  \param prob_right Probabilidade de virar a direita
 */
EntryRoad::EntryRoad(char* name,
                     std::size_t speed,
                     std::size_t max_size,
                     std::size_t average,
                     std::size_t variation,
                     std::size_t prob_left,
                     std::size_t prob_front,
                     std::size_t prob_right) :
LinkedQueueOfVehicles::LinkedQueueOfVehicles(speed, max_size),
_average{average},
_variation{variation},
_prob_left{prob_left},
_prob_front{prob_front},
_prob_right{prob_right}
{
    LinkedQueueOfVehicles::_name = name;
    LinkedQueueOfVehicles::_type = 'a';
}

//! Destrutor
/*! Nada alocado dinamicamente
 */
EntryRoad::~EntryRoad(){
    LinkedQueueOfVehicles::~LinkedQueueOfVehicles();
}

//! Resolvendo o cruzamento
/*! Conexões da estradas com seus possíveis destinos
 *  \param left Estrada para a esquerda
 *  \param front Estrada para a frente
 *  \param right Estrada para a direita
 */
void EntryRoad::crossroads(void *left, void *front, void *right) {
    _crossroads.insert(left, 0u);
    _crossroads.insert(front, 1u);
    _crossroads.insert(right, 2u);
}

//! Estrada segundo a destino
/*! Conexões da estradas com seus possíveis destinos
 *  Destino:
 *    - 0 : esquerda
 *    - 1 : frente
 *    - 2 : direita
 *  \return void* estrada do destino
 */
void* EntryRoad::crossroads(std::size_t destination) {
    return _crossroads[destination];
}

//! Sobrescrita do método enqueue
/*! Coloca um veículo no final da estrada e decide para onde ele
 *  quer ir em seguida.
 *  \param data Veículo que será inserido.
 */
void EntryRoad::enqueue(Vehicle* data) {
    if (LinkedQueueOfVehicles::full(data))
        throw std::out_of_range("Full road!");

    data->direction(direction_probability());
    LinkedQueueOfVehicles::enqueue(data);
}

//! Probabilidade de destino
/*! Gera o destino segundo a probabilidade da estrada.
 *  \return std::size_t Destino
 */
std::size_t EntryRoad::direction_probability() {
    std::size_t prob = rand()%100;
    if (prob < _prob_left)
        return 0u;
    else if (prob-_prob_left < _prob_front)
        return 1u;
    else
        return 2u;
}

//! Tempo de entrada variável
/*! Gera um tempo aleatório de entrada na estrada.
 *  \return std::size_t Tempo de entrada
 */
std::size_t EntryRoad::input_frequency() {
    double tmp = ((double) rand() / (RAND_MAX));
    return (std::size_t) tmp*(2*_variation+1) + _average-_variation;
}

}  // namespace structures

#endif
