// "Copyright [2017] <João Vicente Souto>"
#include <iostream>
#include <fstream>
#include <cstdio>  // para gets()
#include <sys/stat.h>

using namespace std;

size_t file_size();

class Node {
public:
  Node() {}

  Node(char* primary_key, char* secondary_key) {
    strcpy(primary_key_, primary_key);
    strcpy(secondary_key_, secondary_key);
  }

  bool primary_key_less_than(char* primary_key) {
    return true;
  }

  bool secondary_key_less_than(char* secondary_key) {
    return true;
  }

  void print() {
    cout << "Chave 1: " << primary_key_ << endl;
    //cout << "Chave 2: " << secondary_key_ << endl;
  }

private:
  char primary_key_[100]{"\0"},
       secondary_key_[100]{"\0"};
  size_t depth_{0u};
};

int main() {

  size_t profundidade = 3u, quant_nodes = 0u;
  fstream f;
  f.open("file.dat", ios::in | ios::out | ios::binary | ios::trunc); // open or create

  if (!f.is_open()) {
    cout << "Erro ao abrir o arquivo." << endl;
    return 1;
  }

  char a;
  do {
    char pri[100], sec[100];
    cout << "\nChave primária: ";
    cin >> pri;
    cout << "Chave sedundária: ";
    cin >> sec;
    Node nod(pri, sec);

    //cout << "Ponto de leitura: " << f.tellg() << endl;
    cout << "Ponto de escrita: " << f.tellp() << endl;
    f.write(reinterpret_cast<char*>(&nod), sizeof(Node));
    cout << "Ponto de escrita: " << f.tellp() << endl;
    //cout << "Ponto de leitura: " << f.tellg() << endl;

    ++quant_nodes;

    cout << "Add novos nodes? (s/n): ";
    cin >> a;
  } while(a == 's');

  cout << "\nQuantidade de nodes criados: " << quant_nodes << endl;
  cout << "Tamanho do arquivo: " << file_size() << endl;

  // Pegando todos os filhos da esquerda
  int level = 0;
  f.seekg(0);
  Node temp;
  do {
    f.read(reinterpret_cast<char*>(&temp), sizeof(Node));
    temp.print();
    cout << "Ponto de leitura: " << f.tellg() << endl;
    f.seekg(2*f.tellg() - sizeof(Node)); // Pega filho da esquerda
    cout << "Ponto de leitura: " << f.tellg() << endl;
  } while(level++ < 3);

  f.close();
  return 0;
}

size_t file_size() {
  // Só funciona se eu chamar tellg ou p no main duas vezes...
  // ou da erro pq o arquivo está aberto, testar isso.
  struct stat st;
  if (stat("file.dat", &st) == 0)
    return st.st_size;
  return 0u;
}
