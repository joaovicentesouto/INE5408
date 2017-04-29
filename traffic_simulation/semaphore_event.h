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
    SemaphoreEvent(size_t event_time, Semaphore* semaphore);
    ~SemaphoreEvent();

    Semaphore* semaphore();
    virtual bool task();

  private:
    typedef std::size_t size_t;
    Semaphore* _semaphore;
  };

  SemaphoreEvent::SemaphoreEvent(size_t event_time, Semaphore* semaphore):
  Event::Event(event_time),
  _semaphore{semaphore}
  {}

  SemaphoreEvent::~SemaphoreEvent() {
    Event::~Event();
  }

  Semaphore* SemaphoreEvent::semaphore() {
    return _semaphore;
  }

  bool SemaphoreEvent::task() {
    _semaphore->change();
    return true;
  }

}  // namespace structures

#endif
