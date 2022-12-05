#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../common/common.hpp"

using std::ifstream;

int main() {
  std::vector<std::vector<int>> elf_buffer = {};
  ifstream stream("input1.txt");
  std::string row;
  std::vector<int> current_elf = {};

  while (getline(stream, row)) {
    if (helpers::is_number(row)) {
      current_elf.push_back(std::stoi(row));
    } else {
      elf_buffer.push_back(current_elf);
      current_elf = {};
    }
  }
  int max = 0;
  for (auto &elf : elf_buffer) {
    int sum = 0;
    for (auto &calories : elf) {
      sum += calories;
    }
    if (sum > max) {
      max = sum;
    }
  }
  std::cout << "Highest calories" << std::endl;
  std::cout << max << std::endl;

  stream.close();
  return 0;
}
