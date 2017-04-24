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
    void leaving(std::size_t left);

  private:
    std::size_t size_;
  };

  //! Construtor padrão
  /*  Construtor onde se define o tamanho do veículo em sua criação.
   *  Tamanho: tamanho do carro [2:6] metros + 2 metros a frente e 1 atrás.
   */
  Car::Car() {
    srand(time(NULL));
    size_ = rand()/RAND_MAX*5 + 5;
  }

  //! Destrutor padrão
  /*  Nada alocado dinamicamente.
   */
  Car::~Car() {}

  std::size_t Car::size() {
    return size_;
  }

  void Car::leaving(std::size_t left) {
    size_ -= left;
  }

}
