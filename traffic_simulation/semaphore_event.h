//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_SEMAPHORE_EVENT_H
#define STRUCTURES_SEMAPHORE_EVENT_H

#include <cstdint>
#include <stdlib.h>
#include "./event.h"

namespace structure {

  class SemaphoreEvent : public Event {
  public:
    SemaphoreEvent();
    ~SemaphoreEvent();

    virtual void task();
  }

}  // namespace structure
