//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_INPUT_EVENT_H
#define STRUCTURES_INPUT_EVENT_H

#include <cstdint>
#include <stdlib.h>
#include "./car.h"
#include "./event.h"
#include "./entry_road.h"
#include "./linked_queue_of_cars.h"
#include "./structures/linked_list.h"

namespace structures {

  class EntryRoad;

  class InputEvent : public Event {
  public:
    InputEvent(size_t &global_clock,
               size_t event_time,
               EntryRoad *road);
    ~InputEvent();

    EntryRoad* road();
    virtual bool task(int &control);

  private:
    typedef std::size_t size_t;
    EntryRoad *_road;
  };

  InputEvent::InputEvent(
              size_t &global_clock,
              size_t event_time,
              EntryRoad *road):
  Event::Event(global_clock, event_time),
  _road{road}
  {}

  InputEvent::~InputEvent() {
    Event::~Event();
  }

  EntryRoad* InputEvent::road() {
    return _road;
  }

  bool InputEvent::task(int &control) {
    Car* car = new Car();
    try {
      _road->enqueue(car);
    } catch(std::out_of_range error) {
      delete car;
      return false;
    }
    return true;
  }

}  // namespace structures

#endif
