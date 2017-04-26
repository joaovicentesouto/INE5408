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
    LinkedListOfCars(char type, size_t max_size, size_t speed);
    ~LinkedListOfCars();

    void enqueue(const Car& data);
    Car dequeue();

    size_t speed() const;
    size_t size() const;
    size_t max_size() const;

 private:
    typedef std::size_t size_t;
    char type;  //< 'a' : aferente / 'e' : eferente
    size_t max_size_, speed_;
    size_t size_{0u};
};

LinkedListOfCars::LinkedListOfCars(char type, size_t max_size, size_t speed):
LinkedQueue<Car>::LinkedQueue(),
type_{type},
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

}  // namespace structures

#endif
