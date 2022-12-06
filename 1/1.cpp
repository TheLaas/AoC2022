#include "common.hpp"

int main() {
  std::vector<std::vector<int> > elf_buffer;
  std::ifstream stream("input1.txt");
  std::string row;
  std::vector<int> current_elf;

  while (getline(stream, row)) {
    if (helpers::is_number(row)) {
      current_elf.push_back(std::stoi(row));
    } else {
      elf_buffer.push_back(current_elf);
      current_elf.clear();
    }
  }
  int max = 0;
  std::vector<int> calory_total;
  for (auto &elf : elf_buffer) {
    int sum = 0;
    for (auto &calories : elf) {
      sum += calories;
    }
    if (sum > max) {
      // 1:
      max = sum;
    }
    // 2:
    calory_total.push_back(sum);
  }
  std::sort(calory_total.begin(), calory_total.end(), std::greater<int>());
  std::cout << "1. Highest calories" << std::endl;
  std::cout << max << std::endl;

  std::cout << "2. Total 3 highest calories:" << std::endl;
  std::cout << calory_total.at(0) + calory_total.at(1) + calory_total.at(2)
            << std::endl;

  stream.close();
  return 0;
}
