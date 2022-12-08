#include "common.hpp"
struct Compartments {
  std::string first;
  std::string second;
};

Compartments split_string(std::string line) {
  int length = line.length();
  std::string tmp = line.substr(0, length / 2);
  line.erase(0, length / 2);
  return Compartments{.first = tmp, .second = line};
}

int main() {
  auto parse_func = [](std::string line) { return split_string(line); };
  auto rucksacks = helpers::parse_input<Compartments>("test.txt", parse_func);
  auto parse_func2 = [](std::string line) { return line; };
  auto rucksacks_groups =
      helpers::parse_input<std::string>("input.txt", parse_func2, 3);
  int sum = 0;
  for (auto &rucksack : rucksacks) {
    std::string common = "";
    for (auto &c : rucksack.first) {
      if (rucksack.second.find(c) != std::string::npos &&
          common.find(c) == std::string::npos)
        common += c;
    }
    for (auto &c : common) {
      if (std::isupper(c))
        sum += c - 'A' + 27;
      else
        sum += c - 'a' + 1;
    }
  }
  std::cout << "1. " << sum << std::endl;

  sum = 0;
  for (auto &group : rucksacks_groups) {
    std::string common = "";
    for (auto &c : group.at(0)) {
      if (group.at(1).find(c) != std::string::npos &&
          group.at(2).find(c) != std::string::npos &&
          common.find(c) == std::string::npos) {
        common += c;
        if (std::isupper(c))
          sum += c - 'A' + 27;
        else
          sum += c - 'a' + 1;
      }
    }
  }

  std::cout << "2. " << sum << std::endl;
  return 0;
}