#include <boost/algorithm/string.hpp>
#include <map>

#include "common.hpp"
int cycle_check_points[6] = {20, 60, 100, 140, 180, 220};

int get_number(std::string line) {
  return std::stoi(line.substr(line.find(" ") + 1, line.length()));
};

int main() {
  std::vector<int> signal_strength;
  std::string line;
  std::ifstream input_file("input.txt");
  int register_value = 1;
  // int i = 0;
  std::vector<int> saved_rv;
  // std::map<int, int> buffered_rv;
  while (getline(input_file, line)) {
    if (line[0] == 'a') {
      for (int j = 0; j < 2; j++) {
        saved_rv.push_back(register_value);
      }
      register_value += get_number(line);
      // saved_rv.push_back(register_value);
    } else {
      saved_rv.push_back(register_value);
    }
  }

  int sum = 0;
  for (auto &k : cycle_check_points) {
    sum += k * saved_rv.at(k - 1);
  }
  std::cout << "1. " << sum << std::endl;
  return 1;
}