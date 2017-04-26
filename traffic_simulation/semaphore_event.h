//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_SEMAPHORE_EVENT_H
#define STRUCTURES_SEMAPHORE_EVENT_H

#include <cstdint>
#include <stdlib.h>
#include "./event.h"

namespace structure {

  class SemaphoreEvent : public Event {
  public:
    SemaphoreEvent(std::size_t time, LinkedListOfCars *road);
    ~SemaphoreEvent();

    virtual void task();
  }

  SemaphoreEvent::SemaphoreEvent(std::size_t time, LinkedListOfCars *road):
  Event::Event(time, road)
  {}

  SemaphoreEvent::~SemaphoreEvent() {
    Event::~Event();
  }

  void SemaphoreEvent::task() {
    this->road->change_semaphore();
  }

}  // namespace structure
