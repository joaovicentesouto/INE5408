//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_CAR_H
#define STRUCTURES_CAR_H

#include <cstdint>
#include <stdlib.h>

namespace structures {

  class Car {
  public:
    Car();
    ~Car();

    std::size_t size() const;
    char direction() const;
    void direction(char direction);

  private:
    std::size_t size_;
    char direction_{'l'};
  };

  //! Construtor padrão
  /*  Construtor onde se define o tamanho do veículo em sua criação.
   *  Tamanho: tamanho do carro [2:6] metros + 2 metros a frente e 1 atrás.
   */
  Car::Car() {
    double tmp = (double) rand()/RAND_MAX;
    size_ = tmp*5 + 5;
  }

  //! Destrutor padrão
  /*  Nada alocado dinamicamente.
   */
  Car::~Car() {}

  std::size_t Car::size() const {
    return size_;
  }

  char Car::direction() const {
    return direction_;
  }

  void Car::direction(char direction) {
    direction_ = direction;
  }

}  //  namespace structures

#endif
