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
    LinkedQueueOfCars(size_t max_size,
                      size_t speed,
                      size_t &global_clock);
    ~LinkedQueueOfCars();

    void road_left(LinkedQueueOfCars* left);
    void road_front(LinkedQueueOfCars* front);
    void road_right(LinkedQueueOfCars* right);

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
    typedef structures::Car Car;
    ArrayList<LinkedQueueOfCars*> roads_{3u};
    size_t max_size_, speed_, &global_clock_;
    size_t size_{0u};
};

LinkedQueueOfCars::LinkedQueueOfCars(
                   size_t max_size,
                   size_t speed,
                   size_t &global_clock) :
LinkedQueue<Car*>::LinkedQueue(),
max_size_{max_size},
speed_{speed},
global_clock_{global_clock}
{}

LinkedQueueOfCars::~LinkedQueueOfCars() {
    LinkedQueue<Car*>::clear();
}

void LinkedQueueOfCars::road_left(LinkedQueueOfCars* left) {
  roads_.insert(left, 0u);
}

void LinkedQueueOfCars::road_front(LinkedQueueOfCars* front) {
  roads_.insert(front, 1u);
}

void LinkedQueueOfCars::road_right(LinkedQueueOfCars* right) {
  roads_.insert(right, 2u);
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
  return data->size()+size() > max_size();
}

}  // namespace structures

#endif
