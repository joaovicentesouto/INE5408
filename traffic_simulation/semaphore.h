//!  Copyright [2017] <João Vicente Souto>
#ifndef STRUCTURES_SEMAPHORE_H
#define STRUCTURES_SEMAPHORE_H

#include <cstdint>
#include <stdlib.h>
#include "./entry_road.h"
#include "./structures/array_list.h"

namespace structures {
    
//! Forward
/*! Para uso do tipo EntryRoad
 */
class entry_road;

//! Classe Semaphore
/*! Controle do semáforo das ruas impedindo estradas, que não estejam
 *  abertas, de retirar veículos saírem.
 *  \author João Vicente Souto.
 *  \since 25/04/17
 *  \version 1.0
 */
class Semaphore {
 public:
    Semaphore(std::size_t semaphore_time, ArrayList<EntryRoad*>& roads);
    ~Semaphore();

    std::size_t semaphore_time() const;
    void change();
    bool open(const EntryRoad* road) const;

 private:
    std::size_t _semaphore{0u},   //!< Controle de troca
    _semaphore_time;  //!< tempo para troca
    EntryRoad *_S1,  //!< Semáforo do primeiro cruzamento
    *_S2;  //!< Semáforo do segundo cruzamento
    ArrayList<EntryRoad*>& _roads;  //!< Estradas com semáforo
};

//! Construtor
/*! Construtor padrão
 *  \param semaphore_time tempo do semáforo
 *  \param roads estradas com semáforos
 */
Semaphore::Semaphore(std::size_t semaphore_time,
                     ArrayList<EntryRoad*>& roads):
_semaphore_time{semaphore_time},
_roads{roads},
_S1{roads[0]},
_S2{roads[4]}
{}

//! Destrutor
/*! Nada alocado dinamicamente
 */
Semaphore::~Semaphore() {}

//! Tempo para troca de sinal
/*! Tamanho do tempo para troca de sinal
 *  \return size_t Tempo para troca de sinal
 */
std::size_t Semaphore::semaphore_time() const {
    return _semaphore_time;
}

//! Troca de sinal
/*! Troca as estradas com sinais abertos
 *  \return size_t Tempo de entrada
 */
void Semaphore::change() {
    _semaphore = (_semaphore+1) % 4;
    _S1 = _roads[_semaphore];
    _S2 = _roads[_semaphore+4];
}

//! Sinal do semáforo
/*! Verifica se uma estrada está com o semáforo aberto
 *  \return bool Verifica se o semáforo está aberto.
 */
bool Semaphore::open(const EntryRoad* road) const {
    return _S1 == road || _S2 == road;
}

}  //  namespace structures

#endif
