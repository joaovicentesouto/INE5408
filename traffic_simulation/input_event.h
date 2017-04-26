//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_INPUT_EVENT_H
#define STRUCTURES_INPUT_EVENT_H

#include <cstdint>
#include <stdlib.h>
#include "./event.h"

namespace structure {

  class InputEvent : public Event {
  public:
    InputEvent(size_t time, LinkedListOfCars *road, size_t &input_counter);
    ~InputEvent();

    virtual void task();

  private:
    typedef std::size_t size_t;
    size_t &input_counter_;
  }

  InputEvent::InputEvent(size_t time, LinkedListOfCars *road, size_t &input_counter):
  Event::Event(time, road),
  input_counter_{input_counter}
  {}

  InputEvent::~InputEvent() {
    Event::~Event();
  }

  void InputEvent::task() {
    Car car = new Car();
    this->road->enqueue(car); //< acessa assim a estrada???
    ++input_counter_;
  }

}  // namespace structure
