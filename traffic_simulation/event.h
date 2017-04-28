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
    Event(size_t event_time, size_t &global_clock, LinkedQueueOfCars *road);
    ~Event();

    size_t execute_time() const;
    bool operator<(Event*& event);

    LinkedQueueOfCars* road() const;

    virtual bool task();

  protected:
    typedef std::size_t size_t;

    size_t event_time_{0u}, &global_clock_;
    LinkedQueueOfCars *road_{nullptr};
  };

  Event::Event() {}

  Event::Event(size_t event_time,
               size_t &global_clock,
               LinkedQueueOfCars *road) :
  event_time_{event_time},
  global_clock_{global_clock},
  road_{road}
  {}

  std::size_t Event::execute_time() const {
    return event_time_;
  }

  bool Event::operator<(Event*& event) {
    return this->execute_time() < event->execute_time();
  }

  LinkedQueueOfCars* Event::road() const {
    return road_;
  }

  bool Event::task() {
    return false;
  }

}  //  namespace structures

#endif
