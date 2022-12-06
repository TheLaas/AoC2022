#include <boost/algorithm/string.hpp>
#include <map>

#include "common.hpp"
/*
A,X = Rock
B,Y = Paper
C,Z = Scissors
*/
struct Pair {
  std::string first;
  std::string second;
};

std::map<std::string, int> play_value = {{"A", 1}, {"B", 2}, {"C", 3},
                                         {"X", 1}, {"Y", 2}, {"Z", 3}};
int game_result(Pair play) {
  if (play_value[play.first] == play_value[play.second]) {
    return 3;
  } else if (play.first == "A") {
    return play.second == "Y" ? 6 : 0;
  } else if (play.first == "B") {
    return play.second == "Z" ? 6 : 0;
  } else if (play.first == "C") {
    return play.second == "X" ? 6 : 0;
  }
  return -1;
}

int main() {
  auto parse_func = [](std::string line) {
    std::vector<std::string> pair;
    boost::split(pair, line, boost::is_any_of(" "));
    Pair p = {.first = pair.at(0), .second = pair.at(1)};
    return p;
  };
  std::vector<Pair> plays = helpers::parse_input<Pair>("input.txt", parse_func);

  int sum = 0;
  for (auto &play : plays) {
    sum += play_value[play.second] + game_result(play);
  }

  std::cout << "Result 1: " << sum << std::endl;
  return 0;
}