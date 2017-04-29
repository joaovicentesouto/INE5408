//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_ROAD_EXCHANGE_EVENT_H
#define STRUCTURES_ROAD_EXCHANGE_EVENT_H

#include <cstdint>
#include <stdlib.h>
#include "./event.h"
#include "./entry_road.h"
#include "./linked_queue_of_cars.h"
#include "./structures/linked_list.h"

namespace structures {

  class EntryRoad;

  class RoadExchangeEvent : public Event {
  public:
    RoadExchangeEvent(size_t &global_clock, size_t event_time, EntryRoad *road);
    ~RoadExchangeEvent();

    EntryRoad* road();
    virtual bool task(LinkedList<Event*>& get_events);

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
  {
    Event::_type = 'r';
  }

  RoadExchangeEvent::~RoadExchangeEvent() {
    Event::~Event();
  }

  EntryRoad* RoadExchangeEvent::road() {
    return _road;
  }

  bool RoadExchangeEvent::task(LinkedList<Event*>& get_events) {
    Car* car = _road->front();
    size_t wait == car->size()/(_road->speed()/3.6);
    this->_global_clock += wait > 0? wait : 1;
    try {
      _road->change_road_car(get_events);
      return true;
    } catch(std::out_of_range error) {
      return false;
    }
  }

}  // namespace structures

#endif
