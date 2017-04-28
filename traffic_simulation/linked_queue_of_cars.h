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

class LinkedQueueOfCars : public LinkedQueue<Car*> {
 public:
    LinkedQueueOfCars(ArrayList<LinkedQueueOfCars*> *roads,
                     size_t max_size,
                     size_t speed,
                     size_t &universal_clock);
    ~LinkedQueueOfCars();

    void enqueue(const Car* data);
    Car* dequeue();

    size_t speed() const;
    size_t size() const;
    size_t max_size() const;
    bool full(const Car* data) const;

    size_t time_of_route();

    bool semaphore();
    void change_semaphore();

 protected:
    typedef std::size_t size_t;
    typedef structures::Car Car;
    ArrayList<LinkedQueueOfCars*> *roads_;
    size_t max_size_, speed_;
    size_t size_{0u};
    size_t &universal_clock_;
    bool semaphore_{false};
};

LinkedQueueOfCars::LinkedQueueOfCars(
                 ArrayList<LinkedQueueOfCars*> *roads,
                 size_t max_size,
                 size_t speed,
                 size_t &universal_clock) :
LinkedQueue<Car*>::LinkedQueue(),
roads_{roads},
max_size_{max_size},
speed_{speed},
universal_clock_{universal_clock}
{}

LinkedQueueOfCars::~LinkedQueueOfCars() {
    LinkedQueue<Car*>::clear();
}

void LinkedQueueOfCars::enqueue(const Car* data) {
    //void enqueue(const T& data);
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

size_t LinkedQueueOfCars::speed() const {
    return speed_;
}

size_t LinkedQueueOfCars::size() const {
    return size_;
}

size_t LinkedQueueOfCars::max_size() const {
    return max_size_;
}

bool LinkedQueueOfCars::full(const Car* data) const {
  return data->size()+size_ > max_size_;
}

size_t LinkedQueueOfCars::time_of_route() {
  return (size_t) max_size_/(speed_/3.6);  //< km/h => m/s
}

bool LinkedQueueOfCars::semaphore() {
    return semaphore_;
}

void LinkedQueueOfCars::change_semaphore() {
    semaphore_ = !semaphore_;
}

}  // namespace structures

#endif
