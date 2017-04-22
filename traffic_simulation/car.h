
#include <cstdint>
#include <stdlib.h>
#include <time.h>

namespace structure {

  class Car {
  public:
    Car();
    ~Car();

    std::size_t size() const;
    void leaving(std::size_t left);

  private:
    std::size_t size_;
  };

  Car::Car() {
    srand(time(NULL));
    size_ = rand()/RAND_MAX*5 + 2;
  }

  Car::~Car() {}

  std::size_t Car::size() {
    return size_;
  }

  void Car::leaving(std::size_t left) {
    size_ -= left;
  }

}
