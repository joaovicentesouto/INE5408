//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_EVENT_H
#define STRUCTURES_EVENT_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

  class Event {
  public:
    Event(size_t event_time, void* polymorph);
    ~Event();

    char type() const;
    size_t event_time() const;
    void* polymorph() const;

    bool operator<(const Event& other_event) const;
    bool operator>(const Event& other_event) const;

  protected:
    typedef std::size_t size_t;

    char _type;
    size_t _event_time{0u};
    void* _polymorph;
  };

  //! Construtor
  /*! Construtor usando apenas o dado recebido para a criação.
   *  \param global_clock Relógio global
   *  \param event_time hora da execução
   *  \param road estrada fonte do evento
   */
  Event::Event(char type, size_t event_time, void* polymorph):
  _type{type},
  _event_time{event_time},
  _polymorph{polymorph}
  {}

  //! Destrutor
  /*! Destrutor padrão
   */
  Event::~Event() {}

  //! Horário de execução
  /*! Retorna a hora que o evento deve ocorrer.
   *  \return size_t Horário de execução
   */
  char Event::type() const {
    return _type;
  }

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
  void* polymorph() const {
      return _polymorph;
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
