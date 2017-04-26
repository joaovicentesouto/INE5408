//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_LINKED_LIST_OF_CARS_H
#define STRUCTURES_LINKED_LIST_OF_CARS_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include "./linked_queue.h"
#include "./car.h"

namespace structures {

class LinkedListOfCars : virtual public LinkedQueue<Car> {
 public:
    LinkedListOfCars(LinkedList<Event> *events,
                     ArrayList<LinkedListOfCars> *roads,
                     size_t max_size,
                     size_t speed,
                     size_t &universal_clock);
    ~LinkedListOfCars();

    virtual void enqueue(const Car& data);
    Car dequeue();

    size_t speed() const;
    size_t size() const;
    size_t max_size() const;
    bool full() const;

    size_t time_of_route();

    bool semaphore();
    void change_semaphore();

 protected:
    typedef std::size_t size_t;
    LinkedList<Event> *events_;
    ArrayList<LinkedListOfCars> *roads_;
    size_t max_size_, speed_;
    size_t size_{0u};
    size_t &universal_clock_;
    bool semaphore_{false};
};

LinkedListOfCars::LinkedListOfCars(
                 LinkedList<Event> *events,
                 ArrayList<LinkedListOfCars> *roads,
                 size_t max_size,
                 size_t speed,
                 size_t &universal_clock) :
LinkedQueue<Car>::LinkedQueue(),
events_{events},
roads_{roads},
max_size_{max_size},
speed_{speed},
universal_clock_{universal_clock}
{}

LinkedListOfCars::~LinkedListOfCars() {
    LinkedQueue<Car>::~LinkedQueue();
}

void LinkedListOfCars::enqueue(const Car& data) {
    if (full(data))
        throw std::out_of_range("Full queue!");
    LinkedQueue<Car>::enqueue(data);
    size_ += data.size();
}

Car LinkedListOfCars::dequeue() {
    Car out = LinkedQueue<Car>::dequeue();
    size_ -= out.size();
    return out;
}

size_t LinkedListOfCars::speed() const {
    return speed_;
}

size_t LinkedListOfCars::size() const {
    return size_;
}

size_t LinkedListOfCars::max_size() const {
    return max_size_;
}

bool LinkedListOfCars::full(const Car& data) const {
  return data.size()+size_ > max_size_;
}

size_t LinkedListOfCars::time_of_route() {
  return (size_t) max_size_/(speed_/3.6);  //< km/h => m/s
}

bool LinkedListOfCars::semaphore() {
    return semaphore_;
}

void LinkedListOfCars::change_semaphore() {
    semaphore_ = !semaphore_;
}

}  // namespace structures

#endif
