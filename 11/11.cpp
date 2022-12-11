#include <iostream>
#include <vector>

using I_TYPE = unsigned long;
class Monkey {
 public:
  Monkey(std::vector<I_TYPE> items, I_TYPE test_factor,
         std::function<I_TYPE(I_TYPE)> operation)
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

  void inspect_and_throw2(I_TYPE common_factor) {
    for (auto &item : items) {
      item = operation(item) % common_factor;
      if (item % test_factor == 0) {
        if_true->items.push_back(item);
      } else {
        if_false->items.push_back(item);
      }
      inspected_items++;
    }
    items.clear();
  }

  std::vector<I_TYPE> items;
  I_TYPE inspected_items;

 private:
  Monkey *if_true;
  Monkey *if_false;
  std::function<I_TYPE(I_TYPE)> operation;
  int test_factor;
};

std::vector<Monkey *> test = {
    new Monkey(std::vector<I_TYPE>{79, 98}, 23,
               [](I_TYPE worry) { return worry * 19; }),
    new Monkey(std::vector<I_TYPE>{54, 65, 75, 74}, 19,
               [](I_TYPE worry) { return worry + 6; }),
    new Monkey(std::vector<I_TYPE>{79, 60, 97}, 13,
               [](I_TYPE worry) { return worry * worry; }),
    new Monkey(std::vector<I_TYPE>{74}, 17,
               [](I_TYPE worry) { return worry + 3; }),
};

std::vector<Monkey *> input = {
    new Monkey(std::vector<I_TYPE>{63, 57}, 7,
               [](I_TYPE worry) { return worry * 11; }),
    new Monkey(std::vector<I_TYPE>{82, 66, 87, 78, 77, 92, 83}, 11,
               [](I_TYPE worry) { return worry + 1; }),
    new Monkey(std::vector<I_TYPE>{97, 53, 53, 85, 58, 54}, 13,
               [](I_TYPE worry) { return worry * 7; }),
    new Monkey(std::vector<I_TYPE>{50}, 3,
               [](I_TYPE worry) { return worry + 3; }),
    new Monkey(std::vector<I_TYPE>{64, 69, 52, 65, 73}, 17,
               [](I_TYPE worry) { return worry + 6; }),
    new Monkey(std::vector<I_TYPE>{57, 91, 65}, 2,
               [](I_TYPE worry) { return worry + 5; }),
    new Monkey(std::vector<I_TYPE>{67, 91, 84, 78, 60, 69, 99, 83}, 5,
               [](I_TYPE worry) { return worry * worry; }),
    new Monkey(std::vector<I_TYPE>{58, 78, 69, 65}, 19,
               [](I_TYPE worry) { return worry + 7; }),
};

I_TYPE common_test = 23 * 19 * 13 * 17;
I_TYPE common_input = 7 * 11 * 13 * 3 * 17 * 2 * 5 * 19;

int main() {
  // test
  // std::vector<Monkey *> monkeys = test;
  // monkeys.at(0)->add_throwers(monkeys.at(2), monkeys.at(3));
  // monkeys.at(1)->add_throwers(monkeys.at(2), monkeys.at(0));
  // monkeys.at(2)->add_throwers(monkeys.at(1), monkeys.at(3));
  // monkeys.at(3)->add_throwers(monkeys.at(0), monkeys.at(1));
  // I_TYPE common_factor = common_test;
  // input
  std::vector<Monkey *> monkeys = input;
  monkeys.at(0)->add_throwers(monkeys.at(6), monkeys.at(2));
  monkeys.at(1)->add_throwers(monkeys.at(5), monkeys.at(0));
  monkeys.at(2)->add_throwers(monkeys.at(4), monkeys.at(3));
  monkeys.at(3)->add_throwers(monkeys.at(1), monkeys.at(7));
  monkeys.at(4)->add_throwers(monkeys.at(3), monkeys.at(7));
  monkeys.at(5)->add_throwers(monkeys.at(0), monkeys.at(6));
  monkeys.at(6)->add_throwers(monkeys.at(2), monkeys.at(4));
  monkeys.at(7)->add_throwers(monkeys.at(5), monkeys.at(1));
  I_TYPE common_factor = common_input;

  // 1:
  //  for (int i = 0; i < 20; i++) {
  //    for (auto *monkey : monkeys) {
  //      monkey->inspect_and_throw();
  //    }
  //  }

  // 2:
  for (int i = 1; i <= 10000; i++) {
    for (auto *monkey : monkeys) {
      monkey->inspect_and_throw2(common_factor);
    }
  }

  std::sort(monkeys.begin(), monkeys.end(),
            [](const Monkey *lhs, const Monkey *rhs) {
              return lhs->inspected_items > rhs->inspected_items;
            });
  I_TYPE product =
      monkeys.at(0)->inspected_items * monkeys.at(1)->inspected_items;
  std::cout << "1 & 2. " << product << std::endl;
  for (auto *monkey : monkeys) {
    delete monkey;
  }
  return 0;
}