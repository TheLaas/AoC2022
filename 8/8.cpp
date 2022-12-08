#include "common.hpp"

int check_visible(std::vector<std::vector<int>> forest, int x_pos, int y_pos) {
  auto current_tree = forest.at(y_pos).at(x_pos);
  int check = 0;
  for (int y = y_pos; y < forest.size() - 1; y++) {
    auto next_tree = forest.at(y + 1).at(x_pos);
    if (current_tree <= next_tree) {
      check += 1;
      break;
    }
  }
  if (check == 0) return 1;
  for (int y = y_pos; y > 0; y--) {
    auto next_tree = forest.at(y - 1).at(x_pos);
    if (current_tree <= next_tree) {
      check += 1;
      break;
    }
  }
  if (check == 1) return 1;
  for (int x = x_pos; x < forest.size() - 1; x++) {
    auto next_tree = forest.at(y_pos).at(x + 1);
    if (current_tree <= next_tree) {
      check += 1;
      break;
    }
  }
  if (check == 2) return 1;
  for (int x = x_pos; x > 0; x--) {
    auto next_tree = forest.at(y_pos).at(x - 1);
    if (current_tree <= next_tree) {
      check += 1;
      break;
    }
  }
  return check == 3 ? 1 : 0;
}

int check_view(std::vector<std::vector<int>> forest, int x_pos, int y_pos) {
  auto current_tree = forest.at(y_pos).at(x_pos);
  bool check = true;
  int accum = 1;
  int sum = 0;
  for (int y = y_pos; y < forest.size() - 1; y++) {
    auto next_tree = forest.at(y + 1).at(x_pos);
    if (current_tree > next_tree)
      sum++;
    else {
      sum++;
      break;
    }
  }
  accum *= sum;
  sum = 0;
  for (int y = y_pos; y > 0; y--) {
    auto next_tree = forest.at(y - 1).at(x_pos);
    if (current_tree > next_tree)
      sum++;
    else {
      sum++;
      break;
    }
  }
  accum *= sum;
  sum = 0;
  for (int x = x_pos; x < forest.size() - 1; x++) {
    auto next_tree = forest.at(y_pos).at(x + 1);
    if (current_tree > next_tree)
      sum++;
    else {
      sum++;
      break;
    }
  }
  accum *= sum;
  sum = 0;
  for (int x = x_pos; x > 0; x--) {
    auto next_tree = forest.at(y_pos).at(x - 1);
    if (current_tree > next_tree)
      sum++;
    else {
      sum++;
      break;
    }
  }
  return accum * sum;
}

int main() {
  auto parse_func = [](std::string line) {
    std::vector<int> wood_line;
    for (auto tree : line) {
      wood_line.push_back(tree - 48);
    }
    return wood_line;
  };
  auto trees = helpers::parse_input<std::vector<int>>("input.txt", parse_func);
  int visible_trees = 0;
  for (int y = 1; y < trees.size() - 1; y++) {
    for (int x = 1; x < trees.at(0).size() - 1; x++) {
      visible_trees += check_visible(trees, x, y);
    }
  }
  visible_trees += 2 * trees.size() + 2 * trees.at(0).size() - 4;
  std::cout << "1: " << visible_trees << std::endl;

  int max = 0;
  int value;
  for (int y = 1; y < trees.size(); y++) {
    for (int x = 1; x < trees.at(0).size(); x++) {
      value = check_view(trees, x, y);
      if (value > max) max = value;
    }
  }
  std::cout << "2: " << max << std::endl;

  return 0;
}