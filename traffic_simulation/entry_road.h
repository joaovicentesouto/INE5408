//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_ENTRY_ROAD_H
#define STRUCTURES_ENTRY_ROAD_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include <cstdlib>
#include "./car.h"
#include "./event.h"
#include "./array_list.h"
#include "./linked_list.h"
#include "./linked_queue_of_cars.h"

namespace structures {

  class EntryRoad : public LinkedQueueOfCars {
  public:
    EntryRoad(LinkedList<Event*> *events,
              ArrayList<LinkedQueueOfCars*> *roads,
              size_t max_size,
              size_t speed,
              float prob_left,
              float prob_front,
              float prob_right);
    ~EntryRoad();

    void enqueue(const Car* data);
    void change_road_car();
    size_t direction_probability();

  private:
    bool yesOrNo(float probabilityOfYes);

    typedef std::size_t size_t;
    float prob_left_, prob_front_, prob_right_;
  };

  EntryRoad::EntryRoad(LinkedList<Event*> *events,
                       ArrayList<LinkedQueueOfCars*> *roads,
                       size_t max_size,
                       size_t speed,
                       size_t &universal_clock,
                       float prob_left,
                       float prob_front,
                       float prob_right) :
  LinkedQueueOfCars::LinkedQueueOfCars(events, roads, max_size, speed, size_t &universal_clock),
  prob_left_{prob_left},
  prob_front_{prob_front},
  prob_right_{prob_right}
  {}

  void EntryRoad::enqueue(const Car* data)  {
    if (LinkedQueueOfCars::full(data))
      throw std::out_of_range("Full queue!");

    data->direction(direction_probability());
    LinkedQueueOfCars::enqueue(data);
    size_t time_event = this->universal_clock_+time_of_route();
    RoadExchangeEvent *event = new RoadExchangeEvent(time_event, this);
    this->events.insert_sorted(event);
  }

  void EntryRoad::change_road_car() {
      Car Car* = this->front();
      roads[car.direction()]->enqueue(car);
      this->dequeue();
  }

  size_t EntryRoad::direction_probability() {
    if (yesOrNo(prob_left_))
      return 0;
    else if (yesOrNo(prob_front_))
      return 1;
    else if (yesOrNo(prob_right_))
      return 2;
  }

  bool EntryRoad::yesOrNo(float probabilityOfYes) {
    //  fonte: http://stackoverflow.com/ ->
    //  -> questions/12885356/random-numbers-with-different-probabilities
    srand((unsigned)time(0));
    return rand()%100 < (probabilityOfYes * 100);
  }

}  // namespace structures

#endif
