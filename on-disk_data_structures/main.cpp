//!  Copyright [2017] <João Vicente Souto>
#include "./system.h"

using namespace structures;

//! Função main
/*! Funcao inicial do executável
 *
 *  \author João Vicente Souto.
 *  \since 20/06/17
 *  \version 1.0
 */
int main(int argc, char const *argv[]) {

  System sys;
  sys.init(argc, argv);
  sys.run();

  return 0;
}
