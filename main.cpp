#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "common_functions.h"
#include "puzzle_position.h"

bool hasSolution(long long startpos[16]) {
  int inv = 0;
  for (int i = 0; i < gameSIZE; i++) {
    if (startpos[i] != 0)
      for (int j = 0; j < i; j++) {
        if (startpos[j] > startpos[i]) inv++;
      }
  }
  for (int i = 0; i < gameSIZE; i++) {
    if (startpos[i] == 0) inv += (1 + i / 4);
  }
  return (inv + 1) % 2;
}

int fastWaySearch(puzzle_position start, std::string& way);
int preciseWaySearch(puzzle_position start, std::string& way);

int main() {
  std::ifstream fin;
  fin.open("input.txt");
  // std::ofstream fout;
  // fout.open("output.txt");
  long long startpos[16];
  for (int i = 0; i < gameSIZE; i++) {
    fin >> startpos[i];
  }
  if (!hasSolution(startpos)) {
    std::cout << -1;
  } else {
    long long start = 0;
    unsigned char null = 0;
    for (unsigned char i = 0; i < gameSIZE; i++) {
      if (startpos[i] == 0) null = i;
      start = start | (startpos[i] << i * 4);
    }
    std::string way = "";
    puzzle_position start_puzzle_pos(start, null);
    int way_len = 0;
    way_len = fastWaySearch(start_puzzle_pos, way);
    std::cout << way_len << std::endl;
    std::cout << way << std::endl;
    way_len = preciseWaySearch(start_puzzle_pos, way);
    std::cout << way_len << std::endl;
    std::cout << way << std::endl;
  }
  return 0;
}