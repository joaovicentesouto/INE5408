//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_EVENT_H
#define STRUCTURES_EVENT_H

#include <cstdint>
#include <stdlib.h>
#include "./linked_queue_of_cars.h"

namespace structures {

  class Event {
  public:
    Event(std::size_t event_time, LinkedQueueOfCars *road);
    ~Event();

    std::size_t time() const;
    LinkedQueueOfCars* road() const;

    virtual std::size_t task();

  protected:
    std::size_t event_time_;
    LinkedQueueOfCars *road_;
  };

  Event::Event(std::size_t event_time, LinkedQueueOfCars *road) :
  event_time_{event_time},
  road_{road}
  {}

  std::size_t Event::time() const {
    return event_time_;
  }

  LinkedQueueOfCars* Event::road() const {
    return road_;
  }

}  //  namespace structures

#endif
