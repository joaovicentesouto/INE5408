//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_EXIT_ROAD_H
#define STRUCTURES_EXIT_ROAD_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include "./car.h"
#include "./event.h"
#include "./output_event.h"
#include "./structures/linked_list.h"

namespace structures {

  class OutputEvent;

  class ExitRoad : public LinkedQueueOfCars {
  public:
    ExitRoad(size_t &global_clock, size_t speed, size_t max_size);
    ~ExitRoad();

    virtual void enqueue(Car* data, LinkedList<Event*>& get_events);

  private:
    typedef std::size_t size_t;
  };

  ExitRoad::ExitRoad(size_t &global_clock, size_t speed, size_t max_size) :
  LinkedQueueOfCars::LinkedQueueOfCars(global_clock, speed, max_size)
  {}

  void ExitRoad::enqueue(Car* data, LinkedList<Event*>& get_events)  {
    LinkedQueueOfCars::enqueue(data, get_events);
    size_t time_event = this->_global_clock+time_of_route();
    Event *new_event = new OutputEvent(this->_global_clock, time_event, this);
    get_events.push_back(new_event);
  }

}  // namespace structures

#endif
