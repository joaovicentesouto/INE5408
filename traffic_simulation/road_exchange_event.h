//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_ROAD_EXCHANGE_EVENT_H
#define STRUCTURES_ROAD_EXCHANGE_EVENT_H

#include <cstdint>
#include <stdlib.h>
#include "./car.h"
#include "./event.h"
#include "./entry_road.h"
#include "./linked_queue_of_cars.h"
#include "./structures/linked_list.h"

namespace structures {

  class EntryRoad;

  class RoadExchangeEvent : public Event {
  public:
    RoadExchangeEvent(size_t &global_clock,
                      size_t event_time,
                      EntryRoad *road);
    ~RoadExchangeEvent();

    EntryRoad* road();
    virtual bool task(int &control);

  private:
    typedef std::size_t size_t;
    EntryRoad *_road;
  };

  RoadExchangeEvent::RoadExchangeEvent(
                     size_t &global_clock,
                     size_t event_time,
                     EntryRoad *road):
  Event::Event(global_clock, event_time),
  _road{road}
  {}

  RoadExchangeEvent::~RoadExchangeEvent() {
    Event::~Event();
  }

  EntryRoad* RoadExchangeEvent::road() {
    return _road;
  }

  bool RoadExchangeEvent::task(int &control) {
    try {
      //_road->change_road_car();
      return true;
    } catch(std::out_of_range error) {
      return false;
    }
  }

}  // namespace structures

#endif
