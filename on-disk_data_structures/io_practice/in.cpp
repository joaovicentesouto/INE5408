// "Copyright [2017] <João Vicente Souto>"
#include <iostream>
#include <fstream>
#include <cstdio>  // para gets()
#include <sys/stat.h>

using namespace std;

int main() {

    ifstream is("in.dat", ifstream::binary | ifstream::in);
    if (is) {

      struct stat results;

      int length;
      if (stat("in.dat", &results) == 0) {
        // Opção 1
        length = results.st_size;
        cout << "Reading " << length << " characters...stat ";
      } else {
        // Maneira feita em C
        is.seekg (0, is.end);
        length = is.tellg();
        is.seekg (0, is.beg);
        cout << "Reading " << length << " characters... ";
      }

      char * buffer = new char [length];

      // read data as a block:
      is.read(buffer,length);

      if (is)
        cout << "\nall characters read successfully.\n";
      else
        cout << "\nerror: only " << is.gcount() << " could be read";
      is.close();

      cout << buffer;

      delete[] buffer;
    }

    return 0;
}
