//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_EVENT_H
#define STRUCTURES_EVENT_H

#include <cstdint>
#include <stdlib.h>
#include "./linked_queue_of_cars.h"

namespace structures {

  class LinkedQueueOfCars;

  class Event {
  public:
    Event();
    Event(std::size_t event_time, LinkedQueueOfCars *road);
    ~Event();

    std::size_t time() const;
    //std::size_t time(std::size_t event_time_);

    LinkedQueueOfCars* road() const;
    //void road(LinkedQueueOfCars* road);

    virtual bool task();

  protected:
    std::size_t event_time_{0u};
    LinkedQueueOfCars *road_{nullptr};
  };

  Event::Event() {}

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

  bool Event::task() {
    return false;
  }

}  //  namespace structures

#endif
