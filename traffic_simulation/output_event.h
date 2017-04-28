//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_OUTPUT_EVENT_H
#define STRUCTURES_OUTPUT_EVENT_H

#include <cstdint>
#include <stdlib.h>
#include "./event.h"
#include "./structures/linked_list.h"
#include "./linked_queue_of_cars.h"

namespace structures {

  class LinkedQueueOfCars;

  class OutputEvent : public Event {
  public:
    OutputEvent(size_t &global_clock,
                size_t event_time,
                LinkedQueueOfCars *road);
    ~OutputEvent();

    virtual bool task();

  private:
    typedef std::size_t size_t;
  };

  OutputEvent::OutputEvent(
               size_t &global_clock,
               size_t event_time,
               LinkedQueueOfCars *road):
  Event::Event(global_clock, event_time, road),
  {
    Event::_type = 'o';
  }

  OutputEvent::~OutputEvent() {
    Event::~Event();
  }

  bool OutputEvent::task(LinkedList<Event*>& events) {
    this->road()->dequeue();
    return true;
  }

}  // namespace structures

#endif
