//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_OUTPUT_EVENT_H
#define STRUCTURES_OUTPUT_EVENT_H

#include <cstdint>
#include <stdlib.h>
#include "./event.h"

namespace structure {

  class OutputEvent : public Event {
  public:
    OutputEvent();
    ~OutputEvent();

    virtual void task();
  }

}  // namespace structure
