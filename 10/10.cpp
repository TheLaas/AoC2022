#include <boost/algorithm/string.hpp>
#include <map>

#include "common.hpp"
int cycle_check_points[6] = {20, 60, 100, 140, 180, 220};

int get_number(std::string line) {
  return std::stoi(line.substr(line.find(" ") + 1, line.length()));
};

char check_crt(int cycle, int rv) {
  return (rv - 1 <= ((cycle - 1) % 40) && ((cycle - 1) % 40) <= rv + 1) ? '#'
                                                                        : '.';
}

int main() {
  std::vector<int> signal_strength;
  std::string line;
  std::ifstream input_file("input.txt");
  int register_value = 1;
  std::vector<int> saved_rv;
  int cycle = 1;
  std::string row = "";
  std::vector<std::string> crt;
  while (getline(input_file, line)) {
    if (line[0] == 'a') {
      for (int j = 0; j < 2; j++) {
        saved_rv.push_back(register_value);

        row += check_crt(cycle, register_value);
        if (cycle % 40 == 0) {
          crt.push_back(row);
          row = "";
        }
        cycle++;
      }
      register_value += get_number(line);
    } else {
      saved_rv.push_back(register_value);

      row += check_crt(cycle, register_value);
      if (cycle % 40 == 0) {
        crt.push_back(row);
        row = "";
      }
      cycle++;
    }
  }

  int sum = 0;
  for (auto &k : cycle_check_points) {
    sum += k * saved_rv.at(k - 1);
  }
  std::cout << "1. " << sum << std::endl;

  for (auto crt_line : crt) {
    std::cout << crt_line << std::endl;
  }
  return 1;
}