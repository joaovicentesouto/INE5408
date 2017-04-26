//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_INPUT_EVENT_H
#define STRUCTURES_INPUT_EVENT_H

#include <cstdint>
#include <stdlib.h>
#include "./event.h"

namespace structure {

  class InputEvent : public Event {
  public:
    InputEvent();
    ~InputEvent();

    virtual void task();
  }

}  // namespace structure
