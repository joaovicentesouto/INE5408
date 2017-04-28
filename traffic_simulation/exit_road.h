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
    EntryRoad(LinkedList<Event*> *events,
              ArrayList<LinkedQueueOfCars*> *roads,
              size_t max_size,
              size_t speed);
    ~EntryRoad();

    void enqueue(const Car* data);

  private:
    typedef std::size_t size_t;
  };

  EntryRoad::EntryRoad(
                   LinkedList<Event*> *events,
                   ArrayList<LinkedQueueOfCars*> *roads,
                   size_t max_size,
                   size_t speed) :
  LinkedQueueOfCars::LinkedQueueOfCars(events, roads, max_size, speed),
  {}

  void EntryRoad::enqueue(const Car* data)  {
    LinkedQueueOfCars::enqueue(data);
    size_t time_event = this->universal_clock_+time_of_route();
    OutputEvent *event = new OutputEvent(time_event, this);
    this->events.insert_sorted(event);
  }

}  // namespace structures

#endif