//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_SYSTEM_H
#define STRUCTURES_SYSTEM_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include <string>

#include "./event.h"
#include "./entry_road.h"
#include "./exit_road.h"
#include "./semaphore.h"

#include "./structures/linked_list.h"
#include "./structures/array_list.h"

namespace structures {

  class System {
  public:
    System(std::size_t execution_time, std::size_t semaphore_time);
    ~System();

    void init();
    void run();
    void result();

  private:
    std::size_t _execution_time,
                _semaphore_time,
                _global_clock{0u},
                _input_counter{0u},
                _output_counter{0u};

    LinkedList<Event>* _events;  //< Estradas
    ArrayList<EntryRoad*> _entry_roads{8u};  //< Estradas aferentes
    ArrayList<ExitRoad*> _exit_roads{6u};  //< Estradas eferentes

    Semaphore* _semaphore;
  };

  //! Construtor padrão
  /*! Atribuindo os valores bases para o funcionamento do sistema.
   *  \param execution_time Tempo de execução
   *  \param semaphore_time Tempo de um semáforo
   */
  System::System(std::size_t execution_time, std::size_t semaphore_time):
  _execution_time{execution_time},
  _semaphore_time{semaphore_time}
  {
    _events = new LinkedList<Event>();
  }

  //! Destrutor
  /*! Deleta o sistema
   */
  System::~System() {
    delete _events;
    delete _semaphore;
  }

  //! Inícia todas as estradas e eventos iniciais
  /*! Executa uma série e passos antes de rodar o sistema.
   */
  void System::init() {

    // Criando as ruas
    // AFERENTES
    EntryRoad* N1_SUL = new EntryRoad(60, 500, 20, 5, 0.8, 0.1, 0.1);      //N1_S  (60, 500, 20+/-5)
    EntryRoad* S1_NORTE = new EntryRoad(60, 500, 30, 7, 0.1, 0.1, 0.8);    //S1_N  (60, 500, 30+/-7)
    EntryRoad* O1_LESTE = new EntryRoad(80, 2000, 10, 2, 0.1, 0.8, 0.1);   //O1_L  (80, 2000, 10+/-2)
    EntryRoad* L1_OESTE = new EntryRoad(30, 400, 10, 2, 0.3, 0.3, 0.4);    //L1_O  (30, 400, 10+/-2)
    EntryRoad* N2_SUL = new EntryRoad(40, 500, 20, 5, 0.4, 0.3, 0.3);      //N2_S  (40, 500, 20+/-5)
    EntryRoad* S2_NORTE = new EntryRoad(40, 500, 60, 15, 0.3, 0.3, 0.4);   //S2_N  (40, 500, 60+/-15)
    // CENTRAIS
    EntryRoad* C1_LESTE = new EntryRoad(60, 300, 0, 0, 0.3, 0.4, 0.3);     //C1_L  (60, 300)
    EntryRoad* C1_OESTE = new EntryRoad(60, 300, 0, 0, 0.3, 0.4, 0.3);     //C1_O  (60, 300)
    // EFERENTES
    ExitRoad* N1_NORTE = new ExitRoad(60, 500);  // N1_N  (60, 500)
    ExitRoad* N2_NORTE = new ExitRoad(40, 500);  // N2_N  (40, 500)
    ExitRoad* O1_OESTE = new ExitRoad(80, 2000); // O1_O  (80, 2000)
    ExitRoad* L1_LESTE = new ExitRoad(60, 500);  // L1_L  (30, 400)
    ExitRoad* S1_SUL = new ExitRoad(60, 500);    // S1_S  (60, 500)
    ExitRoad* S2_SUL = new ExitRoad(40, 500);    // S2_S  (40, 500)

    // Interligando os cruzamentos : estrada->cruzamento(left, front, right)
    N1_SUL->crossroads(C1_LESTE, S1_SUL, O1_OESTE);
    S1_NORTE->crossroads(O1_OESTE, N1_NORTE, C1_LESTE);
    O1_LESTE->crossroads(N1_NORTE, C1_LESTE, S1_SUL);
    L1_OESTE->crossroads(S2_SUL, C1_OESTE, N2_NORTE);
    N2_SUL->crossroads(L1_LESTE, S2_SUL, C1_OESTE);
    S2_NORTE->crossroads(C1_OESTE, N2_NORTE, L1_LESTE);
    C1_LESTE->crossroads(N2_NORTE, L1_LESTE, S2_SUL);
    C1_OESTE->crossroads(S1_SUL, O1_OESTE, N1_NORTE);


    // AFERENTES
    _entry_roads.push_back(N1_SUL);
    _entry_roads.push_back(S1_NORTE);
    _entry_roads.push_back(O1_LESTE);
    _entry_roads.push_back(L1_OESTE);
    _entry_roads.push_back(N2_SUL);
    _entry_roads.push_back(S2_NORTE);
    // CENTRAIS
    _entry_roads.push_back(C1_LESTE);
    _entry_roads.push_back(C1_OESTE);

    // EFERENTES
    _exit_roads.push_back(N1_NORTE);
    _exit_roads.push_back(N2_NORTE);
    _exit_roads.push_back(O1_OESTE);
    _exit_roads.push_back(L1_LESTE);
    _exit_roads.push_back(S1_SUL);
    _exit_roads.push_back(S2_SUL);

    // Inputs iniciais
    for (auto i = 0u; i<6; ++i) {
      std::size_t event_time = _global_clock + _entry_roads[i]->input_frequency();
      Event *input = new Event('i', event_time, _entry_roads[i]);
      _events->insert_sorted(*input);
      ++_input_counter;
    }

    // Primeiro evento de troca de semáforo
    _semaphore = new Semaphore(_semaphore_time, _entry_roads);
    std::size_t event_time = _global_clock + _semaphore_time;
    Event *change = new Event('s', event_time, _semaphore);
    _events->insert_sorted(*change);

  }

  void System::run() {

    while (_global_clock < _execution_time) {

      std::size_t last_clock = _global_clock;

      // Prioridades
      // semaforo
      // output
      // input
      // crossroads
      int i = 0;
      Event *current_event = &_events->at(i);
      while (current_event->event_time() < _global_clock) {

        switch (current_event->type()) {
          // semaforo
          case 's': {
            _semaphore->change();
            _global_clock = current_event->event_time();
            _events->pop(i);

            std::size_t event_time = _global_clock + _semaphore_time;
            Event *change = new Event('s', event_time, _semaphore);
            _events->insert_sorted(*change);
            break;
          }

          // output
          case 'o': {
            ExitRoad* road = (ExitRoad*) current_event->source();
            road->dequeue();
            _events->pop(i);
            break;
          }

          // input
          case 'i': {

            break;
          }

          // crossroads
          case 'c': {

            break;
          }

          default: {
            break;
          }
        }

        current_event = &_events->at(i);
      }

      if (last_clock == _global_clock)
        ++_global_clock;
    }

  }

  void System::result() {
    printf("Resultados:\n");
    printf("Quantos veículos entraram: %lu\n", _input_counter);
    printf("Quantos veículos saíram: %lu\n", _output_counter);
  }

}  //  namespace structures

#endif
