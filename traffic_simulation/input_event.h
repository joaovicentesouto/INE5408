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

  class car;

  class InputEvent : public Event {
  public:
    InputEvent(size_t &global_clock,
               size_t event_time,
               LinkedQueueOfCars *road);
    ~InputEvent();

    virtual bool task();

  private:
    typedef std::size_t size_t;
  };

  InputEvent::InputEvent(
              size_t &global_clock,
              size_t event_time,
              LinkedQueueOfCars *road):
  Event::Event(global_clock, event_time, road),
  {
    Event::_type = 'i';
  }

  InputEvent::~InputEvent() {
    Event::~Event();
  }

  bool InputEvent::task(LinkedList<Event*>& events) {
    Car* car = new Car();
    EntryRoad* road = (EntryRoad*) Event::road();
    try {
      road->enqueue(car, events);
    } catch(std::out_of_range error) {
      delete car;
      return false;
    }
    size_t event_time = this->_global_clock+road->input_frequency();
    events.push_back(new InputEvent(_global_clock, event_time, road));
    return true;
  }

}  // namespace structures

#endif
