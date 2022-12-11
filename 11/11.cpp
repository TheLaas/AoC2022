#include <iostream>
#include <vector>

class Monkey {
 public:
  Monkey(std::vector<int> items, int test_factor,
         std::function<int(int)> operation)
      : items(items), test_factor(test_factor), operation(operation) {
    inspected_items = 0;
  };
  ~Monkey(){};
  void add_throwers(Monkey *if_t, Monkey *if_f) {
    if_true = if_t;
    if_false = if_f;
  }

  void inspect_and_throw() {
    for (auto &item : items) {
      item = operation(item) / 3;
      if (item % test_factor == 0) {
        if_true->items.push_back(item);
      } else {
        if_false->items.push_back(item);
      }
      inspected_items++;
    }
    items.clear();
  }

  void inspect_and_throw2() {
    for (auto &item : items) {
      item = operation(item);
      if (item % test_factor == 0) {
        if_true->items.push_back(item);
      } else {
        if_false->items.push_back(item);
      }
      inspected_items++;
    }
    items.clear();
  }

  std::vector<int> items;
  int inspected_items;

 private:
  Monkey *if_true;
  Monkey *if_false;
  std::function<int(int)> operation;
  int test_factor;
};

std::vector<Monkey *> test = {
    new Monkey(std::vector<int>{79, 98}, 23,
               [](int worry) { return worry * 19; }),
    new Monkey(std::vector<int>{54, 65, 75, 74}, 19,
               [](int worry) { return worry + 6; }),
    new Monkey(std::vector<int>{79, 60, 97}, 13,
               [](int worry) { return worry * worry; }),
    new Monkey(std::vector<int>{74}, 17, [](int worry) { return worry + 3; }),
};

std::vector<Monkey *> input = {
    new Monkey(std::vector<int>{63, 57}, 7,
               [](int worry) { return worry * 11; }),
    new Monkey(std::vector<int>{82, 66, 87, 78, 77, 92, 83}, 11,
               [](int worry) { return worry + 1; }),
    new Monkey(std::vector<int>{97, 53, 53, 85, 58, 54}, 13,
               [](int worry) { return worry * 7; }),
    new Monkey(std::vector<int>{50}, 3, [](int worry) { return worry + 3; }),
    new Monkey(std::vector<int>{64, 69, 52, 65, 73}, 17,
               [](int worry) { return worry + 6; }),
    new Monkey(std::vector<int>{57, 91, 65}, 2,
               [](int worry) { return worry + 5; }),
    new Monkey(std::vector<int>{67, 91, 84, 78, 60, 69, 99, 83}, 5,
               [](int worry) { return worry * worry; }),
    new Monkey(std::vector<int>{58, 78, 69, 65}, 19,
               [](int worry) { return worry + 7; }),
};

int main() {
  std::vector<Monkey *> monkeys = input;
  // test
  // monkeys.at(0)->add_throwers(monkeys.at(2), monkeys.at(3));
  // monkeys.at(1)->add_throwers(monkeys.at(2), monkeys.at(0));
  // monkeys.at(2)->add_throwers(monkeys.at(1), monkeys.at(3));
  // monkeys.at(3)->add_throwers(monkeys.at(0), monkeys.at(1));
  // input
  monkeys.at(0)->add_throwers(monkeys.at(6), monkeys.at(2));
  monkeys.at(1)->add_throwers(monkeys.at(5), monkeys.at(0));
  monkeys.at(2)->add_throwers(monkeys.at(4), monkeys.at(3));
  monkeys.at(3)->add_throwers(monkeys.at(1), monkeys.at(7));
  monkeys.at(4)->add_throwers(monkeys.at(3), monkeys.at(7));
  monkeys.at(5)->add_throwers(monkeys.at(0), monkeys.at(6));
  monkeys.at(6)->add_throwers(monkeys.at(2), monkeys.at(4));
  monkeys.at(7)->add_throwers(monkeys.at(5), monkeys.at(1));

  for (int i = 0; i < 20; i++) {
    for (auto *monkey : monkeys) {
      monkey->inspect_and_throw();
    }
  }

  std::sort(monkeys.begin(), monkeys.end(),
            [](const Monkey *lhs, const Monkey *rhs) {
              return lhs->inspected_items > rhs->inspected_items;
            });
  int product = monkeys.at(0)->inspected_items * monkeys.at(1)->inspected_items;
  std::cout << "1. " << product << std::endl;
  for (auto *monkey : monkeys) {
    delete monkey;
  }
  return 0;
}