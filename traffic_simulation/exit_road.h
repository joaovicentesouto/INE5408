//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_EXIT_ROAD_H
#define STRUCTURES_EXIT_ROAD_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include "./linked_queue_of_cars.h"
#include "./car.h"

namespace structures {

  class ExitRoad : public LinkedListOfCars {
  public:
    EntryRoad(LinkedList<Event> *events,
              ArrayList<LinkedListOfCars> *roads,
              size_t max_size,
              size_t speed);
    ~EntryRoad();

    virtual void enqueue(const Car& data);

  }

  EntryRoad::EntryRoad(
                   LinkedList<Event> *events,
                   ArrayList<LinkedListOfCars> *roads,
                   size_t max_size,
                   size_t speed) :
  LinkedListOfCars::LinkedListOfCars(events, roads, max_size, speed),
  {}

  void EntryRoad::enqueue(const Car& data)  {
    LinkedListOfCars::enqueue(data);
    size_t time_event = this->universal_clock_+time_of_route();
    OutputEvent *event = new OutputEvent(time_event, this);
    this->events.insert_sorted(event);
  }

}  // namespace structures
