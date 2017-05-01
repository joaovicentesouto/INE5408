//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_EXIT_ROAD_H
#define STRUCTURES_EXIT_ROAD_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include "./vehicle.h"
#include "./structures/linked_list.h"
#include "./linked_queue_of_vehicles.h"

namespace structures {

  class ExitRoad : public LinkedQueueOfVehicles {
  public:
    ExitRoad(char* name, size_t speed, size_t max_size);
    ~ExitRoad();

    virtual void enqueue(Vehicle* data);

  private:
    typedef std::size_t size_t;
  };

  ExitRoad::ExitRoad(char* name, size_t speed, size_t max_size) :
  LinkedQueueOfVehicles::LinkedQueueOfVehicles(speed, max_size)
  {
    LinkedQueueOfVehicles::_name = name;
    LinkedQueueOfVehicles::_type = 'e';
  }

  void ExitRoad::enqueue(Vehicle* data) {
    LinkedQueueOfVehicles::enqueue(data);
  }

}  // namespace structures

#endif
