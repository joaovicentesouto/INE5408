//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_EVENT_H
#define STRUCTURES_EVENT_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

#include "./linked_queue_of_cars.h"
#include "./structures/linked_list.h"

namespace structures {

  class LinkedQueueOfCars;

  class Event {
  public:
    Event(size_t &global_clock, size_t event_time, LinkedQueueOfCars *road);
    ~Event();

    size_t event_time() const;
    LinkedQueueOfCars* road() const;
    char type() const;
    virtual bool task(LinkedList<Event*>& events);

    bool operator<(Event*& event);

  protected:
    typedef std::size_t size_t;

    size_t &_global_clock, _event_time{0u};
    LinkedQueueOfCars *_road{nullptr};
    char _type{'e'};
  };

  //! Construtor
  /*! Construtor usando apenas o dado recebido para a criação.
   *  \param global_clock Relógio global
   *  \param event_time hora da execução
   *  \param road estrada fonte do evento
   */
  Event::Event(size_t &global_clock,
               size_t event_time,
               LinkedQueueOfCars *road) :
  _global_clock{global_clock},
  _event_time{event_time},
  _road{road}
  {}

  //! Destrutor
  /*! Destrutor padrão
   */
  Event::~Event() {}

  //! Horário de execução
  /*! Retorna a hora que o evento deve ocorrer.
   *  \return size_t Horário de execução
   */
  size_t Event::event_time() const {
    return _event_time;
  }

  //! Estrada fonte do evento
  /*! Retorna a estrada que deve ser alterada pelo evento
   *  \return LinkedQueueOfCars* Estrada do evento
   */
  LinkedQueueOfCars* Event::road() const {
    return _road;
  }

  //! Tipo do evento
  /*! Retorna o tipo do evento
   *  \return char tipo do evento
   */
  char Event::type() const {
    return _type;
  }

  //! Tarefa que deve ser executada
  /*! Tarefa que cada tipo de evento irá executar
   *  \return bool Sucesso na hora de executar a tarefa.
   */
  bool Event::task(LinkedList<Event*>& events) {
    return false;
  }

  //! Sobrecarga do operador <
  /*! Comparando dois eventos através do tempo para execução.
   *  \param Event*& Evento externo para comparação.
   *  \return bool Comparação dos tempos de exec.
   */
  bool Event::operator<(Event*& event) {
    return this->event_time() < event->event_time();
  }

}  //  namespace structures

#endif
