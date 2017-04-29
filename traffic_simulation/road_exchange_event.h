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
    RoadExchangeEvent(size_t &global_clock, size_t event_time, LinkedQueueOfCars *road);
    ~RoadExchangeEvent();

    virtual bool task(LinkedList<Event>& get_events);
  };

  RoadExchangeEvent::RoadExchangeEvent(
                     size_t &global_clock,
                     size_t event_time,
                     LinkedQueueOfCars *road):
  Event::Event(global_clock, event_time, road)
  {
    Event::_type = 'r';
  }

  RoadExchangeEvent::~RoadExchangeEvent() {
    Event::~Event();
  }

  bool RoadExchangeEvent::task(LinkedList<Event>& get_events) {
    EntryRoad* road = (EntryRoad*) Event::road();
    Car* car = road->front();
    size_t wait == car->size()/(road->speed()/3.6);
    this->_global_clock += wait > 0? wait : 1;
    try {
      road->change_road_car(get_events);
      return true;
    } catch(std::out_of_range error) {
      return false;
    }
  }

}  // namespace structures

#endif
