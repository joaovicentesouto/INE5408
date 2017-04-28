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
    InputEvent(size_t time, LinkedQueueOfCars *road, size_t &input_counter);
    ~InputEvent();

    virtual void task();

  private:
    typedef std::size_t size_t;
    size_t &input_counter_;
  };

  InputEvent::InputEvent(size_t time, LinkedQueueOfCars *road, size_t &input_counter):
  Event::Event(time, road),
  input_counter_{input_counter}
  {}

  InputEvent::~InputEvent() {
    Event::~Event();
  }

  size_t InputEvent::task() {
    try {
      Car *car = new Car();
      this->road()->enqueue(car); //< acessa assim a estrada???
      ++input_counter_;
    } catch(std::out_of_range error) {
      delete car;
    }
    return 0u;
  }

}  // namespace structures

#endif
