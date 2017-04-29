//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_SEMAPHORE_EVENT_H
#define STRUCTURES_SEMAPHORE_EVENT_H

#include <cstdint>
#include <stdlib.h>
#include "./event.h"
#include "./structures/linked_list.h"
#include "./semaphore.h"

namespace structures {

  class semaphore;

  class SemaphoreEvent : public Event {
  public:
    SemaphoreEvent(size_t &global_clock,
                   size_t event_time,
                   Semaphore* semaphore);
    ~SemaphoreEvent();

    Semaphore* semaphore();
    virtual bool task(LinkedList<Event>& get_events);

  private:
    typedef std::size_t size_t;
    Semaphore* _semaphore;
  };

  SemaphoreEvent::SemaphoreEvent(
                  size_t &global_clock,
                  size_t event_time,
                  Semaphore* semaphore):
  Event::Event(global_clock, event_time),
  _semaphore{semaphore}
  {
    Event::type = 's';
  }

  SemaphoreEvent::~SemaphoreEvent() {
    Event::~Event();
  }

  Semaphore* SemaphoreEvent::semaphore() {
    return _semaphore;
  }

  bool SemaphoreEvent::task(LinkedList<Event>& get_events) {
    _semaphore->change();
    this->_global_clock = this->event_time();
    std::size_t event_time = this->_global_clock+_semaphore->semaphore_time();
    Event* event = new SemaphoreEvent(this->_global_clock, event_time, _semaphore);
    get_events.push_back(event);
    return true;
  }

}  // namespace structures

#endif
