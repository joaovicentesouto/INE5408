//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_SEMAPHORE_H
#define STRUCTURES_SEMAPHORE_H

namespace structures {

  class Semaphore {
  public:
    Semaphore(ArrayList<EntryRoad*> roads);
    ~Semaphore();

    void change();
    bool open(EntryRoad*& road) const;

  private:
    std::size_t _semaphore{0u};
    EntryRoad* _S1, _S2;
    ArrayList<EntryRoad*> _roads;
  };

  Semaphore::Semaphore(ArrayList<EntryRoad*> roads):
  _roads{roads},
  _S1{roads[0]},
  _S2{roads[4]}
  {}

  Semaphore::~Semaphore() {}

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
