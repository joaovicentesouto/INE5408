//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_EVENT_H
#define STRUCTURES_EVENT_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

  //! Classe Event
  /*! Classe base para o funcionamento de uma simulação contendo um tipo,
   *  um horário de execução e a fonte, onde será feita a execução de tal
   *  evento.
   *  \author João Vicente Souto.
   *  \since 25/04/17
   *  \version 1.0
   */
  class Event {
  public:
    Event(char type, size_t event_time, void* source);
    ~Event();

    char type() const;
    size_t event_time() const;
    void* source() const;

    bool operator<(const Event& other_event) const;
    bool operator==(const Event& other_event) const;

  protected:
    typedef std::size_t size_t;

    char _type;  //!< Tipo do evento
    size_t _event_time{0u};  //!< Hora da execução do evento.
    void* _source;  //!< Fonte do evento.
  };

  //! Construtor
  /*! Construtor usando apenas o dado recebido para a criação.
   *  \param type Tipo do evento
   *  \param event_time hora da execução
   *  \param source fonte do evento
   */
  Event::Event(char type, size_t event_time, void* source):
  _type{type},
  _event_time{event_time},
  _source{source}
  {}

  //! Destrutor
  /*! Nada alocado dinamicamente
   */
  Event::~Event() {}

  //! Tipo do evento
  /*! Retorna o tipo do evento:
   *    - 's' : semáforo
   *    - 'i' : entrada de veículo
   *    - 'o' : saída de veículo
   *    - 'c' : troca de pista
   *  \return char Tipo do evento
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

  //! Fonte do evento
  /*! Quem sofrerá o evento
   *  \return void* Fonte do evento.
   */
  void* Event::source() const {
      return _source;
  }

  //! Sobrecarga do operador <
  /*! Comparando dois eventos através do tempo para execução.
   *  \param Event& Evento externo para comparação.
   *  \return bool Comparação dos tempos de exec.
   */
  bool Event::operator<(const Event& other_event) const {
    return _event_time < other_event.event_time();
  }

  //! Sobrecarga do operador ==
  /*! Comparando dois eventos se tem o mesmo endereço de memória.
   *  \param Event& Evento externo para comparação.
   *  \return bool Comparação
   */
  bool Event::operator==(const Event& other_event) const {
    return this == &other_event;
  }

}  //  namespace structures

#endif
