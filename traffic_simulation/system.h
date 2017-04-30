//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_SYSTEM_H
#define STRUCTURES_SYSTEM_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include <cstdlib>
#include <stdlib.h>
#include <string>

#include "./car.h"
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
                _output_counter{0u},
                _semaphore_change_counter{0u},
                _change_road_counter{0u};

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
    EntryRoad* N1_SUL = new EntryRoad((char*)"N1_SUL\0", 60, 500, 20, 5, 80, 10, 10);      //N1_S  (60, 500, 20+/-5)
    EntryRoad* S1_NORTE = new EntryRoad((char*)"S1_NORTE\0", 60, 500, 30, 7, 10, 10, 80);    //S1_N  (60, 500, 30+/-7)
    EntryRoad* O1_LESTE = new EntryRoad((char*)"O1_LESTE\0", 80, 2000, 10, 2, 10, 80, 10);   //O1_L  (80, 2000, 10+/-2)
    EntryRoad* L1_OESTE = new EntryRoad((char*)"L1_OESTE\0", 30, 400, 10, 2, 30, 30, 40);    //L1_O  (30, 400, 10+/-2)
    EntryRoad* N2_SUL = new EntryRoad((char*)"N2_SUL\0", 40, 500, 20, 5, 40, 30, 30);      //N2_S  (40, 500, 20+/-5)
    EntryRoad* S2_NORTE = new EntryRoad((char*)"S2_NORTE\0", 40, 500, 60, 15, 30, 30, 40);   //S2_N  (40, 500, 60+/-15)
    // CENTRAIS
    EntryRoad* C1_LESTE = new EntryRoad((char*)"C1_LESTE\0", 60, 300, 0, 0, 30, 40, 30);     //C1_L  (60, 300)
    EntryRoad* C1_OESTE = new EntryRoad((char*)"C1_OESTE\0", 60, 300, 0, 0, 30, 40, 30);     //C1_O  (60, 300)
    // EFERENTES
    ExitRoad* N1_NORTE = new ExitRoad((char*)"N1_NORTE\0", 60, 500);  // N1_N  (60, 500)
    ExitRoad* N2_NORTE = new ExitRoad((char*)"N2_NORTE\0", 40, 500);  // N2_N  (40, 500)
    ExitRoad* O1_OESTE = new ExitRoad((char*)"O1_OESTE\0", 80, 2000); // O1_O  (80, 2000)
    ExitRoad* L1_LESTE = new ExitRoad((char*)"L1_LESTE\0", 60, 500);  // L1_L  (30, 400)
    ExitRoad* S1_SUL = new ExitRoad((char*)"S1_SUL\0", 60, 500);    // S1_S  (60, 500)
    ExitRoad* S2_SUL = new ExitRoad((char*)"S2_SUL\0", 40, 500);    // S2_S  (40, 500)

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
      Event input('i', event_time, _entry_roads[i]);
      _events->insert_sorted(input);
    }

    // Primeiro evento de troca de semáforo
    _semaphore = new Semaphore(_semaphore_time, _entry_roads);
    std::size_t event_time = _global_clock + _semaphore_time;
    Event semaphore('s', event_time, _semaphore);
    _events->insert_sorted(semaphore);

  }

  void System::run() {

    while (_global_clock < _execution_time) {
      std::size_t count_events = 0;

      // Prioridades
      // semaforo
      // output
      // input
      // crossroads
      int i = 0;
      Event current_event = _events->at(i);
      while (current_event.event_time() <= _global_clock) {

        switch (current_event.type()) {
          // semaforo
          case 's': {
            count_events++;
            _semaphore->change();
            ++_semaphore_change_counter;

            std::size_t event_time = _global_clock + _semaphore_time;
            Event semaphore('s', event_time, _semaphore);
            _events->insert_sorted(semaphore);

            // Elimina evento completado
            _events->pop(i);
            break;
          }

          // output
          case 'o': {
            count_events++;
            ExitRoad* road = (ExitRoad*) current_event.source();
            road->dequeue();
            ++_output_counter;

            // Elimina evento completado
            _events->pop(i);
            break;
          }

          // input
          case 'i': {
            count_events++;
            Car* new_car = new Car();
            EntryRoad* road = (EntryRoad*) current_event.source();

            try {
              road->enqueue(new_car);
              ++_input_counter;

              std::size_t event_time = _global_clock + road->time_of_route();
              Event change('c', event_time, road);
              _events->insert_sorted(change);

              event_time = current_event.event_time() + road->input_frequency();
              Event input('i', event_time, road);
              _events->insert_sorted(input);

              // Elimina evento completado
              _events->pop(i);

            } catch(std::out_of_range error) {
              printf("Entrada falhou: Rua: %s engarrafada.\n", road->name());
              ++i;
            }
            break;
          }

          // crossroads
          case 'c': {
            count_events++;
            EntryRoad* road = (EntryRoad*) current_event.source();
            if (!_semaphore->open(road)) {
              ++i;
              break;  // semaforo fechado;
            }

            Car* first_car = road->front();
            std::size_t direction = first_car->direction();
            LinkedQueueOfCars* temp = (LinkedQueueOfCars*) road->crossroads(direction);

            if (temp->type() == 'a') {
              EntryRoad* aferente = (EntryRoad*) road->crossroads(direction);
              try {
                aferente->enqueue(first_car);
                road->dequeue();
                ++_change_road_counter;

                std::size_t event_time = _global_clock + aferente->time_of_route();
                Event change('c', event_time, aferente);
                _events->insert_sorted(change);

                // Elimina evento completado
                _events->pop(i);

              } catch(std::out_of_range error) {
                printf("Troca de pista falhou: Rua: %s engarrafada.\n", aferente->name());
                ++i;
              }
            } else {
              ExitRoad* eferente = (ExitRoad*) road->crossroads(direction);
              try {
                eferente->enqueue(first_car);
                road->dequeue();
                ++_change_road_counter;

                std::size_t event_time = _global_clock + eferente->time_of_route();
                Event out('o', event_time, eferente);
                _events->insert_sorted(out);

                // Elimina evento completado
                _events->pop(i);

              } catch(std::out_of_range error) {
                printf("Troca de pista falhou: Rua: %s engarrafada.\n", eferente->name());
                ++i;
              }
            }

            break;
          }

          default: {
            break;
          }
        }
        current_event = _events->at(i);
      }

      ++_global_clock;
      if (count_events == 0)
        _global_clock = current_event.event_time();
    }

  }

  void System::result() {
    printf("\nResultados gerais:\n");
    printf("Operação             |  Quant.\n");
    printf("Entrada de veículos  |  %lu\n", _input_counter);
    printf("Saída de  veíulos    |  %lu\n", _output_counter);
    printf("Troca de pista       |  %lu\n", _change_road_counter);
    printf("Troca de semáforo    |  %lu\n", _semaphore_change_counter);

    printf("\nResultados por rua:\n");
    printf("Rua / input / output\n");
    printf("\nEntradas e centrais:\n");
    for(auto i = 0; i < _entry_roads.size(); ++i) {
      auto in = _entry_roads[i]->input_counter();
      auto out = _entry_roads[i]->output_counter();
      printf("%s / %lu / %lu\n", _entry_roads[i]->name(), in, out);
    }
    printf("\nSaídas:\n");
    for(auto i = 0; i < _exit_roads.size(); ++i) {
      auto in = _exit_roads[i]->input_counter();
      auto out = _exit_roads[i]->output_counter();
      printf("%s / %lu / %lu\n", _exit_roads[i]->name(), in, out);
    }
  }

}  //  namespace structures

#endif
