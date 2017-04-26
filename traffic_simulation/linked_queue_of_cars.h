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
    LinkedListOfCars(std::size_t max_size, std::size_t speed);
    ~LinkedListOfCars();

    void enqueue(const Car& data);
    Car dequeue();

    std::size_t speed() const;
    std::size_t size() const;
    std::size_t max_size() const;

 private:
    std::size_t max_size_, speed_;
    std::size_t size_{0u};
};

LinkedListOfCars::LinkedListOfCars(std::size_t max_size, std::size_t speed) :
LinkedQueue<Car>::LinkedQueue(),
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

std::size_t LinkedListOfCars::speed() const {
    return speed_;
}

std::size_t LinkedListOfCars::size() const {
    return size_;
}

std::size_t LinkedListOfCars::max_size() const {
    return max_size_;
}

}  // namespace structures

#endif
