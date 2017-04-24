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

    bool state();  //< Verifica se esta aberto ou fechado ??
    void change_state();  //< Muda estado

    void change_of_vehicle_road();  //< Tenta mudar o 1º carro de pista.
    void vehicle_input(Car &data); //< Insere novo veiculo
    void vehicle_output(); //< Retira carro, saiu pelo sumidouro.

  private:
    bool state_{false};  //< Estado: [true/aberto : false/fechado]
    LinkedQueueOfCars* eferente, aferente;  //< Estrada que entrar e que sai
  };

}  // namespace structures
