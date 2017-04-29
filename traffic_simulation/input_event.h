//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_INPUT_EVENT_H
#define STRUCTURES_INPUT_EVENT_H

#include <cstdint>
#include <stdlib.h>
#include "./event.h"
#include "./car.h"
#include "./input_event.h"
#include "./entry_road.h"
#include "./linked_list_of_cars.h"
#include "./structures/linked_list.h"

namespace structures {

  class InputEvent : public Event {
  public:
    InputEvent(size_t &global_clock,
               size_t event_time,
               EntryRoad *road);
    ~InputEvent();

    EntryRoad* road();
    virtual bool task(LinkedList<Event*>& get_events);

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
  {
    Event::_type = 'i';
  }

  InputEvent::~InputEvent() {
    Event::~Event();
  }

  EntryRoad* InputEvent::road() {
    return _road;
  }

  bool InputEvent::task(LinkedList<Event*>& get_events) {
    Car* car = new Car();
    try {
      _road->enqueue(car, get_events);
    } catch(std::out_of_range error) {
      delete car;
      return false;
    }
    size_t event_time = this->_global_clock + _road->input_frequency();
    Event *new_event = new InputEvent(this->_global_clock, event_time, _road);
    get_events.push_back(new_event);
    return true;
  }

}  // namespace structures

#endif
