//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_LINKED_QUEUE_OF_VEHICLES_H
#define STRUCTURES_LINKED_QUEUE_OF_VEHICLES_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

#include "./vehicle.h"
#include "./structures/linked_queue.h"

namespace structures {

class LinkedQueueOfVehicles : private LinkedQueue<Vehicle*> {
 public:
    LinkedQueueOfVehicles(size_t speed, size_t max_size);
    ~LinkedQueueOfVehicles();

    void clear();
    virtual void enqueue(Vehicle* data);
    Vehicle* dequeue();
    Vehicle* front() const;
    Vehicle* back() const;

    size_t time_of_route();

    char type() const;
    char* name() const;
    size_t speed() const;
    size_t size() const;
    size_t max_size() const;
    size_t input_counter() const;
    size_t output_counter() const;

    bool empty() const;
    bool full(const Vehicle* data) const;

 protected:
    typedef std::size_t size_t;
    char _type{'b'};
    char* _name{(char*)"base\0"};
    size_t _speed, _max_size;
    size_t _size{0u}, _input_counter{0u}, _output_counter{0u};
};

LinkedQueueOfVehicles::LinkedQueueOfVehicles(size_t speed, size_t max_size) :
LinkedQueue<Vehicle*>::LinkedQueue(),
_speed{speed},
_max_size{max_size}
{}

LinkedQueueOfVehicles::~LinkedQueueOfVehicles() {
    LinkedQueue<Vehicle*>::~LinkedQueue();
}

void LinkedQueueOfVehicles::clear() {
    LinkedQueue<Vehicle*>::clear();
}

void LinkedQueueOfVehicles::enqueue(Vehicle* data) {
    if (full(data))
        throw std::out_of_range("Full queue!");
    LinkedQueue<Vehicle*>::enqueue(data);
    _size += data->size();
    ++_input_counter;
}

Vehicle* LinkedQueueOfVehicles::dequeue() {
    Vehicle* out = LinkedQueue<Vehicle*>::dequeue();
    _size -= out->size();
    ++_output_counter;
    return out;
}

Vehicle* LinkedQueueOfVehicles::front() const {
    return LinkedQueue<Vehicle*>::front();
}

Vehicle* LinkedQueueOfVehicles::back() const {
    return LinkedQueue<Vehicle*>::back();
}

size_t LinkedQueueOfVehicles::time_of_route() {
  return (size_t) _max_size/(_speed/3.6);  //< km/h => m/s
}

char LinkedQueueOfVehicles::type() const {
  return _type;
}

char* LinkedQueueOfVehicles::name() const {
  return _name;
}

size_t LinkedQueueOfVehicles::speed() const {
    return _speed;
}

size_t LinkedQueueOfVehicles::size() const {
    return _size;
}

size_t LinkedQueueOfVehicles::max_size() const {
    return _max_size;
}

size_t LinkedQueueOfVehicles::input_counter() const {
  return _input_counter;
}
size_t LinkedQueueOfVehicles::output_counter() const {
  return _output_counter;
}

bool LinkedQueueOfVehicles::empty() const {
    return _size == 0u;
}

bool LinkedQueueOfVehicles::full(const Vehicle* data) const {
  return max_size() < data->size()+size();
}

}  // namespace structures

#endif
