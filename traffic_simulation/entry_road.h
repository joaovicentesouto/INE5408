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
              size_t &global_clock,
              float prob_left,
              float prob_front,
              float prob_right);
    ~EntryRoad();

    virtual void enqueue(Car* data, Event*& event);
    void change_road_car();
    size_t direction_probability();

    bool semaphore();
    void semaphore(size_t semaphore);
    void exchange_semaphore();

  private:
    bool yesOrNo(float probabilityOfYes);

    typedef std::size_t size_t;
    float prob_left_, prob_front_, prob_right_;
    size_t semaphore_{0u}, input_range_, lower_input_;
  };

  EntryRoad::EntryRoad(size_t max_size,
                       size_t speed,
                       size_t input_range,
                       size_t lower_input,
                       size_t &global_clock,
                       float prob_left,
                       float prob_front,
                       float prob_right) :
  LinkedQueueOfCars::LinkedQueueOfCars(max_size, speed, global_clock),
  input_range_{input_range},
  lower_input_{lower_input},
  prob_left_{prob_left},
  prob_front_{prob_front},
  prob_right_{prob_right}
  {}

  void EntryRoad::enqueue(Car* data, Event*& event) {
    if (LinkedQueueOfCars::full(data))
      throw std::out_of_range("Full queue!");
      // preciso verificar pra mudar a direçao do carro

    data->direction(direction_probability());
    LinkedQueueOfCars::enqueue(data);
    size_t time_event = this->global_clock_+time_of_route();
    // cria um novo evento para quem chamou enqueue use
    event = new RoadExchangeEvent(time_event, this);
  }

  void EntryRoad::change_road_car() {
      Car* car = this->front();
      roads_[car->direction()]->enqueue(car); //pode dar erro
      LinkedQueueOfCars::dequeue();
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
    return rand()%100 < (probabilityOfYes * 100);
  }

  bool EntryRoad::semaphore() {
    return semaphore_ == 0u;
  }

  void EntryRoad::semaphore(size_t semaphore) {
    semaphore_ = semaphore;
  }

  void EntryRoad::exchange_semaphore() {
    semaphore_ = (semaphore_+1)%4;
  }

}  // namespace structures

#endif
