#include "common.hpp"
struct Tree {
  int height;
  bool visible;
};

std::vector<std::vector<Tree>> create_forest(
    std::vector<std::vector<int>> tree_heights) {
  std::vector<std::vector<Tree>> forest;
  for (auto row = tree_heights.begin(); row != tree_heights.end(); row++) {
    std::vector<Tree> tree_line;
    for (auto tree = row->begin(); tree != row->end(); tree++) {
      Tree new_tree = {.height = *tree};
      if (row == tree_heights.begin() || std::next(row) == tree_heights.end() ||
          tree == row->begin() || std::next(tree) == row->end()) {
        new_tree.visible = true;
      } else {
        new_tree.visible = false;
      }
      tree_line.push_back(new_tree);
    }
    forest.push_back(tree_line);
  }
  return forest;
}

bool check_visible(std::vector<std::vector<Tree>> forest, int x_pos,
                   int y_pos) {
  auto current_tree = forest.at(y_pos).at(x_pos);
  bool check = true;
  for (int y = y_pos; y < forest.size() - 1; y++) {
    auto next_tree = forest.at(y + 1).at(x_pos);
    // if (next_tree.visible && current_tree.height > next_tree.height) {
    //   // current_tree.visible = true;
    //   // return 1;
    //   // return true;
    // } else
    if (current_tree.height <= next_tree.height) {
      check = false;
      break;
    }
  }
  if (check) return check;
  check = true;
  for (int y = y_pos; y > 0; y--) {
    auto next_tree = forest.at(y - 1).at(x_pos);
    // if (next_tree.visible && current_tree.height > next_tree.height) {
    //   // current_tree.visible = true;
    //   // return 1;
    //   // return true;
    // } else
    if (current_tree.height <= next_tree.height) {
      check = false;
      break;
    }
  }
  if (check) return check;
  check = true;
  for (int x = x_pos; x < forest.size() - 1; x++) {
    auto next_tree = forest.at(y_pos).at(x + 1);
    // if (next_tree.visible && current_tree.height > next_tree.height) {
    //   // current_tree.visible = true;
    //   // return 1;
    //   // return true;
    // } else
    if (current_tree.height <= next_tree.height) {
      check = false;
      break;
    }
  }
  if (check) return check;
  check = true;
  for (int x = x_pos; x > 0; x--) {
    auto next_tree = forest.at(y_pos).at(x - 1);
    // if (next_tree.visible && current_tree.height > next_tree.height) {
    //   // current_tree.visible = true;
    //   // return 1;
    //   // return true;
    // } else
    if (current_tree.height <= next_tree.height) {
      check = false;
      break;
    }
  }
  return check;
}

void print_forest(std::vector<std::vector<Tree>> forest) {
  for (auto tree_line = forest.begin(); tree_line != forest.end();
       tree_line++) {
    for (auto tree = tree_line->begin(); tree != tree_line->end(); tree++) {
      std::cout << "[" << (tree->visible ? 1 : 0) << "," << tree->height
                << "] ";
    }
    std::cout << std::endl;
  }
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
  auto forest = create_forest(trees);
  int visible_trees = 0;
  for (int y = 1; y < forest.size() - 1; y++) {
    for (int x = 1; x < forest.at(0).size() - 1; x++) {
      forest.at(y).at(x).visible = check_visible(forest, x, y);
      if (forest.at(y).at(x).visible) visible_trees++;
    }
  }
  visible_trees += 2 * forest.size() + 2 * forest.at(0).size() - 4;
  print_forest(forest);
  std::cout << "1: " << visible_trees << std::endl;

  return 0;
}