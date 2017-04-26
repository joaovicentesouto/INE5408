//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_CAR_H
#define STRUCTURES_CAR_H

#include <cstdint>
#include <stdlib.h>
#include <time.h>

namespace structure {

  class Car {
  public:
    Car();
    ~Car();

    std::size_t size() const;
    std::size_t direction() const;
    void decides_the_direction();

  private:

    std::size_t size_, direction_;
  };

  //! Construtor padrão
  /*  Construtor onde se define o tamanho do veículo em sua criação.
   *  Tamanho: tamanho do carro [2:6] metros + 2 metros a frente e 1 atrás.
   */
  Car::Car() {
    srand(time(NULL));
    size_ = rand()/RAND_MAX*5 + 5;
    decides_the_direction();
  }

  //! Destrutor padrão
  /*  Nada alocado dinamicamente.
   */
  Car::~Car() {}

  std::size_t Car::direction() const {
    return direction_;
  }

  void Car::decides_the_direction() {
    direction_ = rand()/RAND_MAX*2;
  }

  std::size_t Car::size() {
    return size_;
  }

}
