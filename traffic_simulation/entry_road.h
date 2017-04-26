//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_ENTRY_ROAD_H
#define STRUCTURES_ENTRY_ROAD_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include "./linked_queue.h"
#include "./car.h"

namespace structures {

  class EntryRoad : public LinkedListOfCars {
  public:
    EntryRoad(LinkedList<Event> *events,
              ArrayList<LinkedListOfCars> *roads,
              size_t max_size,
              size_t speed,
              float prob_left,
              float prob_front,
              float prob_right);
    ~EntryRoad();

    virtual void enqueue(const Car& data);
    void change_road_car();
    size_t direction_probability();

  private:
    typedef std::size_t size_t;
    float prob_left_, prob_front_, prob_right_;
  }

  EntryRoad::EntryRoad(LinkedList<Event> *events,
                       ArrayList<LinkedListOfCars> *roads,
                       size_t max_size,
                       size_t speed,
                       size_t &universal_clock,
                       float prob_left,
                       float prob_front,
                       float prob_right) :
  LinkedListOfCars::LinkedListOfCars(events, roads, max_size, speed, size_t &universal_clock),
  prob_left_{prob_left},
  prob_front_{prob_front},
  prob_right_{prob_right}
  {}

  void EntryRoad::enqueue(const Car& data)  {
    if (full())
      throw std::out_of_range("Full queue!")

    data.direction(direction_probability());
    LinkedListOfCars::enqueue(data);
    size_t time_event = this->universal_clock_+time_of_route();
    RoadExchangeEvent *event = new RoadExchangeEvent(time_event, this);
    this->events.insert_sorted(event);
  }

  void EntryRoad::change_road_car() {
      Car &car = this->road.front();
      roads[car.direction()].enqueue(car);
      this->road.dequeue();
  }

  size_t EntryRoad::direction_probability() {
    return probabilidade de virar pra qual rua;
  }

}  // namespace structures
