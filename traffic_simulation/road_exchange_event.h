//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_ROAD_EXCHANGE_EVENT_H
#define STRUCTURES_ROAD_EXCHANGE_EVENT_H

#include <cstdint>
#include <stdlib.h>
#include "./event.h"

namespace structure {

  class RoadExchangeEvent : public Event {
  public:
    RoadExchangeEvent();
    ~RoadExchangeEvent();

    virtual void task();
  }

}  // namespace structure
