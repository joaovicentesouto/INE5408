//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_EXIT_ROAD_H
#define STRUCTURES_EXIT_ROAD_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include <cstdlib>
#include <stdlib.h>
#include "./car.h"
#include "./event.h"
#include "./array_list.h"
#include "./linked_list.h"
#include "./linked_queue_of_cars.h"

namespace structures {

  class ExitRoad : public LinkedQueueOfCars {
  public:
    ExitRoad(size_t max_size, size_t speed);
    ~ExitRoad();

    virtual void enqueue(Car* data, LinkedList<Event*>& events);

  private:
    typedef std::size_t size_t;
  };

  ExitRoad::ExitRoad(size_t max_size, size_t speed) :
  LinkedQueueOfCars::LinkedQueueOfCars(max_size, speed)
  {}

  void ExitRoad::enqueue(Car* data, LinkedList<Event*>& events)  {
    LinkedQueueOfCars::enqueue(data);
    size_t time_event = this->universal_clock_+time_of_route();
    Event *event = new OutputEvent(time_event, this);
    events.push_back(event);
  }

}  // namespace structures

#endif
