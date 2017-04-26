//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_SEMAPHORE_H
#define STRUCTURES_SEMAPHORE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include "./linked_queue_of_cars.h"
#include "./car.h"

namespace structures {

  /* Algumas idéias básicas para a interface de um semáforo
   */
  class Semaphore {
  public:
    Semaphore();  //< Construtor
    ~Semaphore();  //< Destrutor

    void road_to_the_left(Semaphore *sem);  //< Define qual é a estrada a esquerda
    void road_to_the_front(Semaphore *sem);  //< Define qual é a estrada a frente
    void road_to_the_right(Semaphore *sem);  //< Define qual é a estrada a direita

    void change_of_vehicle_road();  //< Tenta mudar o 1º carro de pista.
    void vehicle_input(Car &data); //< Insere novo veiculo
    void vehicle_output(); //< Retira carro, saiu pelo sumidouro.

  private:
    LinkedQueueOfCars* aferente, eferente, left, front, right;  //< Estradas
    LinkedListOfEvents* events;
  };

}  // namespace structures
