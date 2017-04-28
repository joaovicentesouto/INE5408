//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_ENTRY_ROAD_H
#define STRUCTURES_ENTRY_ROAD_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include <cstdlib>
#include <stdlib.h>
#include "./car.h"
#include "./event.h"
#include "./road_exchange_event.h"
#include "./array_list.h"
#include "./linked_list.h"
#include "./linked_queue_of_cars.h"

namespace structures {

  class Event;

  class EntryRoad : public LinkedQueueOfCars {
  public:
    EntryRoad(size_t max_size,
              size_t speed,
              size_t input_range,
              size_t lower_input,
              float prob_left,
              float prob_front,
              float prob_right);
    ~EntryRoad();

    void crossroads(LinkedQueueOfCars *left,
                    LinkedQueueOfCars *front,
                    LinkedQueueOfCars *right);

    virtual void enqueue(Car* data);
    void change_road_car();

    size_t direction_probability();
    size_t input_frequency();

    bool semaphore();
    void semaphore(size_t semaphore);
    void exchange_semaphore();

  private:
    bool yesOrNo(float probabilityOfYes);

    typedef std::size_t size_t;
    float _prob_left, _prob_front, _prob_right;
    size_t _semaphore{0u}, _input_range, _lower_input;
    ArrayList<LinkedQueueOfCars*> crossroads{3u};
  };

  EntryRoad::EntryRoad(size_t max_size,
                       size_t speed,
                       size_t input_range,
                       size_t lower_input,
                       float prob_left,
                       float prob_front,
                       float prob_right) :
  LinkedQueueOfCars::LinkedQueueOfCars(max_size, speed),
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
   crossroads[0] = left;
   crossroads[1] = front;
   crossroads[2] = right;
  }

  void EntryRoad::enqueue(Car* data) {
    if (LinkedQueueOfCars::full(data))
      throw std::out_of_range("Full queue!");
      // preciso verificar pra mudar a direçao do carro

    data->direction(direction_probability());
    LinkedQueueOfCars::enqueue(data);
    size_t time_event = this->_global_time+time_of_route();
    // cria um novo evento para quem chamou enqueue use
    event = new RoadExchangeEvent(time_event, this);
  }

  void EntryRoad::change_road_car() {
      Car* car = this->front();
      roads_[car->direction()]->enqueue(car); //pode dar erro
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
    return (size_t) rand()/RAND_MAX*_input_range + _lower_input;
  }

  bool EntryRoad::yesOrNo(float probabilityOfYes) {
    //  fonte: http://stackoverflow.com/ ->
    //  -> questions/12885356/random-numbers-with-different-probabilities
    return rand()%100 < (probabilityOfYes * 100);
  }

  bool EntryRoad::semaphore() {
    return _semaphore == 0u;
  }

  void EntryRoad::semaphore(size_t semaphore) {
    _semaphore = semaphore;
  }

  void EntryRoad::exchange_semaphore() {
    _semaphore = (_semaphore+1)%4;
  }

}  // namespace structures

#endif
