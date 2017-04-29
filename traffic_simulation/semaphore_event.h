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

    virtual bool task(LinkedList<Event>& get_events);

  private:
    typedef std::size_t size_t;
    Semaphore* _semaphore;
  };

  SemaphoreEvent::SemaphoreEvent(
                  size_t &global_clock,
                  size_t event_time,
                  Semaphore* semaphore):
  Event::Event(global_clock, event_time, nullptr),
  _semaphore{semaphore}
  {
    Event::type = 's';
  }

  SemaphoreEvent::~SemaphoreEvent() {
    Event::~Event();
  }

  bool SemaphoreEvent::task(LinkedList<Event>& get_events) {
    _semaphore->change();
    std::size_t sem_time = _semaphore->semaphore_time()
    this->_global_clock = this->event_time();
    Event* event = new SemaphoreEvent(
                       this->_global_clock,
                       this->_global_clock+sem_time,
                       _semaphore);
    get_events.push_back(event);
    return true;
  }

}  // namespace structures

#endif
