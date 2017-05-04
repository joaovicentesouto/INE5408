//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_EXIT_ROAD_H
#define STRUCTURES_EXIT_ROAD_H

#include <cstdint>  // std::std::size_t
#include <stdexcept>  // C++ exceptions
#include "./vehicle.h"
#include "./structures/linked_list.h"
#include "./linked_queue_of_vehicles.h"

namespace structures {

//! Classe Estrada de saída
/*! Especialização da LinkedQueueOfVehicles.
 *  \author João Vicente Souto.
 *  \since 25/04/17
 *  \version 1.0
 */
class ExitRoad : public LinkedQueueOfVehicles {
 public:
    ExitRoad(char* name, std::size_t speed, std::size_t max_size);
    ~ExitRoad();

    virtual void enqueue(Vehicle* data);
};

//! Construtor
/*! Construtor padrão
 *  \param name Nome da estrada
 *  \param speed Velocidade
 *  \param max_size Tamanho máximo
 */
ExitRoad::ExitRoad(char* name, std::size_t speed, std::size_t max_size) :
LinkedQueueOfVehicles::LinkedQueueOfVehicles(speed, max_size)
{
    LinkedQueueOfVehicles::_name = name;
    LinkedQueueOfVehicles::_type = 'e';
}

//! Destrutor
/*! Nada alocado dinamicamente
 */
ExitRoad::~ExitRoad() {
    LinkedQueueOfVehicles::~LinkedQueueOfVehicles();
}

//! Método de enqueue
/*! Coloca um veículo no final da estrada
 *  \param data Veículo que será inserido.
 */
void ExitRoad::enqueue(Vehicle* data) {
    LinkedQueueOfVehicles::enqueue(data);
}

}  // namespace structures

#endif
