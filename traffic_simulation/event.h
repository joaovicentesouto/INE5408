//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_EVENT_H
#define STRUCTURES_EVENT_H

#include <cstdint>
#include <stdlib.h>
#include "./linked_list_of_cars.h"

namespace structure {

  class Event {
  public:
    Event(std::size_t time, LinkedListOfCars* road);
    ~Event();

    std::size_t time() const;
    virtual std::size_t task();

  protected:
    std::size_t time_;
    LinkedListOfCars *road_;
  }

  Event::Event(std::size_t time, LinkedListOfCars *road) :
  time_{time},
  road_{road}
  {}

  std::size_t time() const {
    return time_;
  }

}  //  namespace structure
