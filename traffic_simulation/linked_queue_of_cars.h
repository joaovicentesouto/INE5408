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
                     size_t speed);
    ~LinkedListOfCars();

    virtual void enqueue(const Car& data);
    Car dequeue();

    size_t speed() const;
    size_t size() const;
    size_t max_size() const;

    bool semaphore();
    void change_semaphore();

    virtual size_t result_probability();

 private:
    typedef std::size_t size_t;
    LinkedList<Event> *events_;
    ArrayList<LinkedListOfCars> *roads_;
    size_t max_size_, speed_;
    size_t size_{0u};
    bool semaphore_{false};
};

LinkedListOfCars::LinkedListOfCars(
                 LinkedList<Event> events,
                 ArrayList<LinkedListOfCars> roads,
                 size_t max_size,
                 size_t speed) :
LinkedQueue<Car>::LinkedQueue(),
events_{events},
roads_{roads},
max_size_{max_size},
speed_{speed}
{}

LinkedListOfCars::~LinkedListOfCars() {
    LinkedQueue<Car>::~LinkedQueue();
}

void LinkedListOfCars::enqueue(const Car& data) {
    if (data.size()+size_ > max_size_)
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

bool LinkedListOfCars::semaphore() {
    return semaphore_;
}

void LinkedListOfCars::change_semaphore() {
    semaphore_ = !semaphore_;
}

}  // namespace structures

#endif
