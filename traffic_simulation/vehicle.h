//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_CAR_H
#define STRUCTURES_CAR_H

#include <cstdint>
#include <stdlib.h>

namespace structures {

  class Vehicle {
  public:
    Vehicle();
    ~Vehicle();

    std::size_t size() const;
    std::size_t direction() const;
    void direction(std::size_t direction);

  private:
    std::size_t size_;
    std::size_t direction_{0u};
  };

  //! Construtor padrão
  /*  Construtor onde se define o tamanho do veículo em sua criação.
   *  Tamanho: tamanho do carro [2:6] metros + 2 metros a frente e 1 atrás.
   */
  Vehicle::Vehicle() {
    double tmp = (double) rand()/RAND_MAX;
    size_ = tmp*5 + 5;
  }

  //! Destrutor padrão
  /*  Nada alocado dinamicamente.
   */
  Vehicle::~Vehicle() {}

  std::size_t Vehicle::size() const {
    return size_;
  }

  std::size_t Vehicle::direction() const {
    return direction_;
  }

  void Vehicle::direction(std::size_t direction) {
    direction_ = direction;
  }

}  //  namespace structures

#endif
