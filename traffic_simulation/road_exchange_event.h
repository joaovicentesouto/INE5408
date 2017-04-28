//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_ROAD_EXCHANGE_EVENT_H
#define STRUCTURES_ROAD_EXCHANGE_EVENT_H

#include <cstdint>
#include <stdlib.h>
#include "./event.h"
#include "./entry_road.h"

namespace structures {

  class EntryRoad;

  class RoadExchangeEvent : public Event {
  public:
    RoadExchangeEvent(std::size_t time, LinkedQueueOfCars *road);
    ~RoadExchangeEvent();

    virtual bool task(std::size_t &global_clock);
    bool semaphore();
  };

  RoadExchangeEvent::RoadExchangeEvent(std::size_t time, LinkedQueueOfCars *road):
  Event::Event(time, road)
  {}

  RoadExchangeEvent::~RoadExchangeEvent() {
    Event::~Event();
  }

  bool RoadExchangeEvent::task(std::size_t &global_clock) {
    try {
      EntryRoad *road = (EntryRoad *) Event::road();
      Car *car = road->front();
      std::size_t time_to_change = car->size()/(road->speed()/3.6);
      global_clock += time_to_change;
      road->change_road_car();
      return true;
    } catch(std::out_of_range error) {
      //printf("Está congestionado onde quero ir.\n");
      return false;
    }
  }

  bool RoadExchangeEvent::semaphore() {
    EntryRoad *road = (EntryRoad *) Event::road();
    return road->semaphore();
  }

}  // namespace structures

#endif
