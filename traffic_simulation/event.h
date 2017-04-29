//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_EVENT_H
#define STRUCTURES_EVENT_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

#include "./linked_queue_of_cars.h"
#include "./structures/linked_list.h"

namespace structures {

  class Event {
  public:
    Event(size_t &global_clock, size_t event_time);
    ~Event();

    size_t event_time() const;
    virtual bool task(int &control);

    bool operator<(const Event& other_event) const;
    bool operator>(const Event& other_event) const;

  protected:
    typedef std::size_t size_t;

    size_t &_global_clock, _event_time{0u};
  };

  //! Construtor
  /*! Construtor usando apenas o dado recebido para a criação.
   *  \param global_clock Relógio global
   *  \param event_time hora da execução
   *  \param road estrada fonte do evento
   */
  Event::Event(size_t &global_clock,
               size_t event_time) :
  _global_clock{global_clock},
  _event_time{event_time}
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

  //! Tarefa que deve ser executada
  /*! Tarefa que cada tipo de evento irá executar
   *  \return bool Sucesso na hora de executar a tarefa.
   */
  bool Event::task(int &control) {
    return false;
  }

  //! Sobrecarga do operador <
  /*! Comparando dois eventos através do tempo para execução.
   *  \param Event& Evento externo para comparação.
   *  \return bool Comparação dos tempos de exec.
   */
  bool Event::operator<(const Event& other_event) const {
    return _event_time < other_event.event_time();
  }

  bool Event::operator>(const Event& other_event) const {
    return _event_time > other_event.event_time();
  }

}  //  namespace structures

#endif
