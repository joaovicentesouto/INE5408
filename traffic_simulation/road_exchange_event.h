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
    RoadExchangeEvent(size_t event_time, EntryRoad *road);
    ~RoadExchangeEvent();

    EntryRoad* road() const;
    virtual bool task();

  private:
    typedef std::size_t size_t;
    EntryRoad *_road;
  };

  RoadExchangeEvent::RoadExchangeEvent(size_t event_time, EntryRoad *road):
  Event::Event(event_time),
  _road{road}
  {}

  RoadExchangeEvent::~RoadExchangeEvent() {
    Event::~Event();
  }

  EntryRoad* RoadExchangeEvent::road() const {
    return _road;
  }

  bool RoadExchangeEvent::task() {
    return true;
  }

}  // namespace structures

#endif
