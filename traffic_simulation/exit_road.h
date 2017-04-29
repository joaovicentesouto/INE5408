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
    ExitRoad(size_t speed, size_t max_size);
    ~ExitRoad();

    virtual void enqueue(Car* data);

  private:
    typedef std::size_t size_t;
  };

  ExitRoad::ExitRoad(size_t speed, size_t max_size) :
  LinkedQueueOfCars::LinkedQueueOfCars(speed, max_size)
  {
    LinkedQueueOfCars::_type = 'e';
  }

  void ExitRoad::enqueue(Car* data) {
    LinkedQueueOfCars::enqueue(data);
  }

}  // namespace structures

#endif
