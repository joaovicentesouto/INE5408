//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_EXIT_ROAD_H
#define STRUCTURES_EXIT_ROAD_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include "./car.h"
#include "./structures/linked_list.h"

namespace structures {

  class ExitRoad : public LinkedQueueOfCars {
  public:
    ExitRoad(size_t &global_clock, size_t speed, size_t max_size);
    ~ExitRoad();

  private:
    typedef std::size_t size_t;
  };

  ExitRoad::ExitRoad(size_t &global_clock, size_t speed, size_t max_size) :
  LinkedQueueOfCars::LinkedQueueOfCars(global_clock, speed, max_size)
  {}

}  // namespace structures

#endif
