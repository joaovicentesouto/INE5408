//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_LINKED_LIST_OF_CARS_H
#define STRUCTURES_LINKED_LIST_OF_CARS_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include "./linked_queue.h"
#include "./car.h"

namespace structures {
    
class LinkedListOfCars {
 public:
    LinkedListOfCars(std::size_t max_size);
    ~LinkedListOfCars();
    void clear();
    void enqueue(const Car& data);
    Car dequeue();
    Car& front() const;
    Car& back() const;
    bool empty() const;
    std::size_t size() const;
    std::size_t max_size() const;

 private:
    std::size_t max_size_;
    std::size_t size_{0u};
    LinkedQueue<Car> queue{new LinkedQueue<Car>()};
};

LinkedListOfCars::LinkedListOfCars(std::size_t max_size) :
max_size_{max_size}
{}

LinkedListOfCars::~LinkedListOfCars() {
    delete queue;
}

LinkedListOfCars::void clear() {
    queue.clear();
}

void LinkedListOfCars::enqueue(const Car& data) {
    if (data.size()+size_ > max_size_)
        throw std::out_of_range("Full queue!");
    queue.enqueue(data);
    size_ += data.size();
}

Car LinkedListOfCars::dequeue() {
    Car out = queue.dequeue();
    size_ -= out.size();
    return out;
}

Car& LinkedListOfCars::front() const {
    return queue.front();
}

Car& LinkedListOfCars::back() const {
    return queue.back();
}

bool LinkedListOfCars::empty() const {
    return size() == 0u;
}

std::size_t LinkedListOfCars::size() const {
    return size_;
}

std::size_t LinkedListOfCars::max_size() const {
    return max_size_;
}

}  // namespace structures

#endif
