//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_ENTRY_ROAD_H
#define STRUCTURES_ENTRY_ROAD_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include <cstdlib>
#include <stdlib.h>

// objects
#include "./car.h"
#include "./event.h"
#include "./road_exchange_event.h"
// structures
#include "./structures/array_list.h"
#include "./structures/linked_list.h"
#include "./linked_queue_of_cars.h"

namespace structures {

  class Event;

  class EntryRoad : public LinkedQueueOfCars {
  public:
    EntryRoad(size_t &global_clock,
              size_t speed,
              size_t max_size,
              size_t input_range,
              size_t lower_input,
              float prob_left,
              float prob_front,
              float prob_right);
    ~EntryRoad();

    void crossroads(LinkedQueueOfCars *left,
                    LinkedQueueOfCars *front,
                    LinkedQueueOfCars *right);

    virtual void enqueue(Car* data, LinkedList<Event*>& get_events);

    void change_road_car(LinkedList<Event*>& get_events);

    size_t direction_probability();
    size_t input_frequency();

  private:
    bool yesOrNo(float probabilityOfYes);

    typedef std::size_t size_t;

    size_t _input_range, _lower_input;
    float _prob_left, _prob_front, _prob_right;
    ArrayList<LinkedQueueOfCars*> _crossroads{3u};
  };

  EntryRoad::EntryRoad(size_t &global_clock,
                       size_t speed,
                       size_t max_size,
                       size_t input_range,
                       size_t lower_input,
                       float prob_left,
                       float prob_front,
                       float prob_right) :
  LinkedQueueOfCars::LinkedQueueOfCars(global_clock, speed, max_size),
  _input_range{input_range},
  _lower_input{lower_input},
  _prob_left{prob_left},
  _prob_front{prob_front},
  _prob_right{prob_right}
  {}

  void LinkedQueueOfCars::crossroads(LinkedQueueOfCars *left,
                                     LinkedQueueOfCars *front,
                                     LinkedQueueOfCars *right)
  {
   _crossroads[0] = left;
   _crossroads[1] = front;
   _crossroads[2] = right;
  }

  void EntryRoad::enqueue(Car* data, LinkedList<Event*>& get_events) {
    if (LinkedQueueOfCars::full(data))
      throw std::out_of_range("Full queue!");
      // preciso verificar pra mudar a direçao do carro
    data->direction(direction_probability());
    LinkedQueueOfCars::enqueue(data);
    size_t time_event = this->_global_time+time_of_route();
    Event *new_event = new RoadExchangeEvent(this->_global_time, time_event, this);
    get_events.push_back(new_event);
  }

  void EntryRoad::change_road_car(LinkedList<Event*>& get_events) {
      Car* car = this->front();
      _crossroads[car->direction()]->enqueue(car, get_events); //pode dar erro
      LinkedQueueOfCars::dequeue();
  }

  size_t EntryRoad::direction_probability() {
    if (yesOrNo(_prob_left))
      return 0;
    else if (yesOrNo(_prob_front))
      return 1;
    else if (yesOrNo(_prob_right))
      return 2;
  }

  size_t EntryRoad::size_t input_frequency() {
    double tmp = (double) rand()/RAND_MAX;
    return tmp*_input_range + _lower_input;
  }

  bool EntryRoad::yesOrNo(float probabilityOfYes) {
    //  fonte: http://stackoverflow.com/ ->
    //  -> questions/12885356/random-numbers-with-different-probabilities
    return rand()%100 < (probabilityOfYes * 100);
  }

}  // namespace structures

#endif
