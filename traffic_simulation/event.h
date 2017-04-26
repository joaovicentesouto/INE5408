//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_EVENT_H
#define STRUCTURES_EVENT_H

#include <cstdint>
#include <stdlib.h>

namespace structure {

  class Event {
  public:
    Event(std::size_t time);
    ~Event();

    std::size_t time() const;

  private:
    std::size_t time_;
  }

  Event::Event(std::size_t time) :
  time_{time;}
  {}

  std::size_t time() const {
    return time_;
  }

}  //  namespace structure
