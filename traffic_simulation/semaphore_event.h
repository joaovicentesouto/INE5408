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

    virtual bool task(std::size_t &global_clock);
  };

  SemaphoreEvent::SemaphoreEvent(std::size_t time, LinkedQueueOfCars *road):
  Event::Event(time, road)
  {}

  SemaphoreEvent::~SemaphoreEvent() {
    Event::~Event();
  }

  bool SemaphoreEvent::task(std::size_t &global_clock) {
    this->road_->change_semaphore();
    // Gera outro evento de troca de semaforo.
    return true;
  }

}  // namespace structures

#endif
