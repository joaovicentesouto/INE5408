//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_INPUT_EVENT_H
#define STRUCTURES_INPUT_EVENT_H

#include <cstdint>
#include <stdlib.h>
#include "./event.h"
#include "./car.h"
#include "linked_list_of_cars.h"

namespace structures {

  class InputEvent : public Event {
  public:
    InputEvent(size_t event_time,
               size_t &global_clock,
               size_t &input_counter,
               LinkedQueueOfCars *road);
    ~InputEvent();

    virtual bool task();

  private:
    typedef std::size_t size_t;
    size_t &input_counter_;
  };

  InputEvent::InputEvent(
              size_t event_time,
              size_t &global_clock,
              size_t &input_counter,
              LinkedQueueOfCars *road):
  Event::Event(event_time, global_clock, road),
  input_counter_{input_counter}
  {}

  InputEvent::~InputEvent() {
    Event::~Event();
  }

  bool InputEvent::task() {
    try {
      Car* car = new Car();
      Event::road()->enqueue(car); //< acessa assim a estrada???
      ++input_counter_;
      //gerar outro evento input
      this->global_clock_ += 0; // tempo do evento ocorrer.
      return true;
    } catch(std::out_of_range error) {
      delete car;
      this->global_clock_ += 0; // tempo do evento ocorrer.
      return false;
    }
  }

}  // namespace structures

#endif
