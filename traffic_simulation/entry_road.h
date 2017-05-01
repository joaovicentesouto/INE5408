//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_ENTRY_ROAD_H
#define STRUCTURES_ENTRY_ROAD_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include <cstdlib>
#include <stdlib.h>

#include "./vehicle.h"
#include "./structures/array_list.h"
#include "./linked_queue_of_vehicles.h"

namespace structures {

  class EntryRoad : public LinkedQueueOfVehicles {
  public:
    EntryRoad(char* name,
              size_t speed,
              size_t max_size,
              size_t average,
              size_t lower_input,
              size_t prob_left,
              size_t prob_front,
              size_t prob_right);
    ~EntryRoad();

    void crossroads(void *left, void *front, void *right);
    void* crossroads(size_t index);

    virtual void enqueue(Vehicle* data);

    size_t direction_probability();
    size_t input_frequency();

  private:
    bool yesOrNo(float probabilityOfYes);

    typedef std::size_t size_t;

    size_t _average, _lower_input, _prob_left, _prob_front, _prob_right;
    ArrayList<void*> _crossroads{3u};
  };

  EntryRoad::EntryRoad(char* name,
                       size_t speed,
                       size_t max_size,
                       size_t average,
                       size_t lower_input,
                       size_t prob_left,
                       size_t prob_front,
                       size_t prob_right) :
  LinkedQueueOfVehicles::LinkedQueueOfVehicles(speed, max_size),
  _average{average},
  _lower_input{lower_input},
  _prob_left{prob_left},
  _prob_front{prob_front},
  _prob_right{prob_right}
  {
    LinkedQueueOfVehicles::_name = name;
    LinkedQueueOfVehicles::_type = 'a';
  }

  void EntryRoad::crossroads(void *left, void *front, void *right) {
   _crossroads.insert(left, 0u);
   _crossroads.insert(front, 1u);
   _crossroads.insert(right, 2u);
  }

  void* EntryRoad::crossroads(size_t index) {
    return _crossroads[index];
  }

  void EntryRoad::enqueue(Vehicle* data) {
      if (LinkedQueueOfVehicles::full(data))
          throw std::out_of_range("Full queue!");
      data->direction(direction_probability());
      LinkedQueueOfVehicles::enqueue(data);
  }

  size_t EntryRoad::direction_probability() {
    size_t prob = rand()%100;
    if (prob < _prob_left)
      return 0u;
    else if (prob < _prob_left+_prob_front)
      return 1u;
    else
      return 0u;
  }

  size_t EntryRoad::input_frequency() {
    double tmp = (double) rand()/RAND_MAX;
    return tmp*(_average-_lower_input) + _lower_input;
  }

}  // namespace structures

#endif
