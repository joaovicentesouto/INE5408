//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_ROAD_EXCHANGE_EVENT_H
#define STRUCTURES_ROAD_EXCHANGE_EVENT_H

#include <cstdint>
#include <stdlib.h>
#include "./event.h"

namespace structure {

  class RoadExchangeEvent : public Event {
  public:
    RoadExchangeEvent(std::size_t time, LinkedListOfCars* road);
    ~RoadExchangeEvent();

    virtual void task();
  }

  RoadExchangeEvent::RoadExchangeEvent(std::size_t time, LinkedListOfCars *road):
  Event::Event(time, road)
  {}

  RoadExchangeEvent::~RoadExchangeEvent() {
    Event::~Event();
  }

  void RoadExchangeEvent::task() {
    
  }

}  // namespace structure
