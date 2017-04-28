//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_LINKED_QUEUE_OF_CARS_H
#define STRUCTURES_LINKED_QUEUE_OF_CARS_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include "./car.h"
#include "./event.h"
#include "./linked_queue.h"
#include "./linked_list.h"
#include "./array_list.h"

namespace structures {

class LinkedQueueOfCars : private LinkedQueue<Car*> {
 public:
    LinkedQueueOfCars(size_t speed, size_t max_size);
    ~LinkedQueueOfCars();

    void clear();
    virtual void enqueue(Car* data);
    Car* dequeue();
    Car* front() const;
    Car* back() const;

    size_t time_of_route();

    size_t speed() const;
    size_t size() const;
    size_t max_size() const;

    bool empty() const;
    bool full(const Car* data) const;

 protected:
    typedef std::size_t size_t;
    size_t _speed, _max_size;
    size_t _size{0u};
};

LinkedQueueOfCars::LinkedQueueOfCars(size_t speed, size_t max_size) :
LinkedQueue<Car*>::LinkedQueue(),
_speed{speed},
_max_size{max_size}
{}

LinkedQueueOfCars::~LinkedQueueOfCars() {
    LinkedQueue<Car*>::~LinkedQueue();
}

void LinkedQueueOfCars::clear() {
    LinkedQueue<Car*>::clear();
}

void LinkedQueueOfCars::enqueue(Car* data) {
    if (full(data))
        throw std::out_of_range("Full queue!");
    _size += data->size();
    LinkedQueue<Car*>::enqueue(data);
}

Car* LinkedQueueOfCars::dequeue() {
    Car *out = LinkedQueue<Car*>::dequeue();
    _size -= out->size();
    return out;
}

Car* LinkedQueueOfCars::front() const {
    return LinkedQueue<Car*>::front();
}

Car* LinkedQueueOfCars::back() const {
    return LinkedQueue<Car*>::back();
}

size_t LinkedQueueOfCars::time_of_route() {
  return (size_t) _max_size/(_speed/3.6);  //< km/h => m/s
}

size_t LinkedQueueOfCars::speed() const {
    return _speed;
}

size_t LinkedQueueOfCars::size() const {
    return _size;
}

size_t LinkedQueueOfCars::max_size() const {
    return _max_size;
}

bool LinkedQueueOfCars::empty() const {
    return _size == 0u;
}

bool LinkedQueueOfCars::full(const Car* data) const {
  return data->size()+size() > max_size();
}

}  // namespace structures

#endif
