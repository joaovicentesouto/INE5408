//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_ROAD_EXCHANGE_EVENT_H
#define STRUCTURES_ROAD_EXCHANGE_EVENT_H

#include <cstdint>
#include <stdlib.h>
#include "./event.h"

namespace structure {

  class RoadExchangeEvent : public Event {
  public:
    RoadExchangeEvent(std::size_t time, LinkedListOfCars *road);
    ~RoadExchangeEvent();

    virtual void task();
    bool semaphore();
  }

  RoadExchangeEvent::RoadExchangeEvent(std::size_t time, LinkedListOfCars *road):
  Event::Event(time, road)
  {}

  RoadExchangeEvent::~RoadExchangeEvent() {
    Event::~Event();
  }

  std::size_t RoadExchangeEvent::task() {
    try {
      EntryRoad *road = (EntryRoad *) this->road;
      road->change_road_car();
    } catch(std::out_of_range error) {
      printf("Está congestionado onde quero ir.\n");
    }
    return  ;  //tempo do carro sair na road ...;
  }

  bool RoadExchangeEvent::semaphore() {
    return this->road->semaphore();
  }

}  // namespace structure
