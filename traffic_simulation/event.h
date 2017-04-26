//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_EVENT_H
#define STRUCTURES_EVENT_H

#include <cstdint>
#include <stdlib.h>

namespace structure {

  class Event {
  public:
    Event(std::size_t time, Semaphore semaphore);
    ~Event();

    std::size_t time() const;
    virtual void task();

  private:
    std::size_t time_;
    Semaphore *semaphore_;
  }

  Event::Event(std::size_t time, Semaphore semaphore) :
  time_{time},
  semaphore_{semaphore}
  {}

  std::size_t time() const {
    return time_;
  }

}  //  namespace structure
