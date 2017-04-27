//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_OUTPUT_EVENT_H
#define STRUCTURES_OUTPUT_EVENT_H

#include <cstdint>
#include <stdlib.h>
#include "./event.h"

namespace structure {

  class OutputEvent : public Event {
  public:
    OutputEvent(size_t time, LinkedQueueOfCars *road, size_t &output_counter);
    ~OutputEvent();

    virtual void task();

  private:
    typedef std::size_t size_t;
    size_t &output_counter_;
  }

  OutputEvent::OutputEvent(std::size_t time, LinkedQueueOfCars *road, size_t &output_counter):
  Event::Event(time, road),
  output_counter_{output_counter}
  {}

  OutputEvent::~OutputEvent() {
    Event::~Event();
  }

  size_t OutputEvent::task() {
    this->road->dequeue(); //< acessa assim a estrada???
    ++output_counter_;
    return 0u;
  }

}  // namespace structure
