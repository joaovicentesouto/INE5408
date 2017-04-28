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

    virtual bool task(size_t &global_clock);

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

  bool InputEvent::task(size_t &global_clock) {
    try {
      Car* car = new Car();
      this->road()->enqueue(car); //< acessa assim a estrada???
      ++input_counter_;
      //gerar outro evento input
      global_clock += 0; // tempo do evento ocorrer.
      return true;
    } catch(std::out_of_range error) {
      delete car;
      global_clock+=0; // tempo do evento ocorrer.
      return false;
    }
  }

}  // namespace structures

#endif
