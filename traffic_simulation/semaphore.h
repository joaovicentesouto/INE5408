//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_SEMAPHORE_H
#define STRUCTURES_SEMAPHORE_H

#include <cstdint>
#include <stdlib.h>
#include "./entry_road.h"
#include "./structures/array_list.h"

namespace structures {

  class entry_road;

  class Semaphore {
  public:
    Semaphore(std:size_t semaphore_time, ArrayList<EntryRoad*> roads);
    ~Semaphore();

    std::size_t semaphore_time() const;

    void change();
    bool open(EntryRoad*& road) const;

  private:
    std::size_t _semaphore{0u}, _semaphore_time;
    EntryRoad* _S1, _S2;
    ArrayList<EntryRoad*> _roads;
  };

  Semaphore::Semaphore(std:size_t semaphore_time,
                       ArrayList<EntryRoad*> roads):
  _semaphore_time{semaphore_time},
  _roads{roads},
  _S1{roads[0]},
  _S2{roads[4]}
  {}

  Semaphore::~Semaphore() {}

  std::size_t Semaphore::semaphore_time() const {
    return _semaphore_time;
  }

  void Semaphore::change() {
    _semaphore = (_semaphore+1) % 4;
    _S1 = _roads[_semaphore];
    _S2 = _roads[_semaphore+4];
  }

  bool Semaphore::open(const EntryRoad*& road) const {
    return _S1 == road || _S2 == road;
  }

}  //  namespace structures

#endif
