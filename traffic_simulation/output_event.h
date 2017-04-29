//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_OUTPUT_EVENT_H
#define STRUCTURES_OUTPUT_EVENT_H

#include <cstdint>
#include <stdlib.h>
#include "./event.h"
#include "./structures/linked_list.h"
#include "./exit_road.h"

namespace structures {

  class ExitRoad;
  //class LinkedList;

  class OutputEvent : public Event {
  public:
    OutputEvent(size_t event_time, ExitRoad *road);
    ~OutputEvent();

    ExitRoad* road();
    virtual bool task();

  private:
    typedef std::size_t size_t;
    ExitRoad *_road;
  };

  OutputEvent::OutputEvent(size_t event_time, ExitRoad *road):
  Event::Event(event_time),
  _road{road}
  {}

  OutputEvent::~OutputEvent() {
    Event::~Event();
  }

  ExitRoad* OutputEvent::road() {
    return _road;
  }

  bool OutputEvent::task() {
    _road->dequeue();
    return true;
  }

}  // namespace structures

#endif
