//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_LINKED_QUEUE_OF_CARS_H
#define STRUCTURES_LINKED_QUEUE_OF_CARS_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include "./car.h"
#include "./linked_queue.h"
#include "./linked_list.h"
#include "./array_list.h"

namespace structures {

class LinkedQueueOfCars : private LinkedQueue<Car*> {
 public:
    LinkedQueueOfCars(ArrayList<LinkedQueueOfCars*> *roads,
                     size_t max_size,
                     size_t speed);
    ~LinkedQueueOfCars();

    void clear();
    void enqueue(Car* data);
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
    typedef structures::Car Car;
    ArrayList<LinkedQueueOfCars*> *roads_;
    size_t max_size_, speed_;
    size_t size_{0u};
};

LinkedQueueOfCars::LinkedQueueOfCars(
                 ArrayList<LinkedQueueOfCars*> *roads,
                 size_t max_size,
                 size_t speed) :
LinkedQueue<Car*>::LinkedQueue(),
roads_{roads},
max_size_{max_size},
speed_{speed}
{}

LinkedQueueOfCars::~LinkedQueueOfCars() {
    LinkedQueue<Car*>::clear();
}

void LinkedQueueOfCars::clear() {
    LinkedQueue<Car*>::clear();
}

void LinkedQueueOfCars::enqueue(Car* data) {
    if (full(data))
        throw std::out_of_range("Full queue!");
    size_ += data->size();
    LinkedQueue<Car*>::enqueue(data);
}

Car* LinkedQueueOfCars::dequeue() {
    Car *out = LinkedQueue<Car*>::dequeue();
    size_ -= out->size();
    return out;
}

Car* LinkedQueueOfCars::front() const {
    return LinkedQueue<Car*>::front();
}

Car* LinkedQueueOfCars::back() const {
    return LinkedQueue<Car*>::back();
}

size_t LinkedQueueOfCars::time_of_route() {
  return (size_t) max_size_/(speed_/3.6);  //< km/h => m/s
}

size_t LinkedQueueOfCars::speed() const {
    return speed_;
}

size_t LinkedQueueOfCars::size() const {
    return size_;
}

size_t LinkedQueueOfCars::max_size() const {
    return max_size_;
}

bool LinkedQueueOfCars::empty() const {
    return size_ == 0u;
}

bool LinkedQueueOfCars::full(const Car* data) const {
  return data->size()+size_ > max_size_;
}

}  // namespace structures

#endif
