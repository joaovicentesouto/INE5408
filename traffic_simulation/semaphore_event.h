//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_SEMAPHORE_EVENT_H
#define STRUCTURES_SEMAPHORE_EVENT_H

#include <cstdint>
#include <stdlib.h>
#include "./event.h"

namespace structures {

  class SemaphoreEvent : public Event {
  public:
    SemaphoreEvent(std::size_t time, LinkedQueueOfCars *road);
    ~SemaphoreEvent();

    virtual void task();
  }

  SemaphoreEvent::SemaphoreEvent(std::size_t time, LinkedQueueOfCars *road):
  Event::Event(time, road)
  {}

  SemaphoreEvent::~SemaphoreEvent() {
    Event::~Event();
  }

  std::size_t SemaphoreEvent::task() {
    this->road_->change_semaphore();
    return 0u;
  }

}  // namespace structure

#endif
