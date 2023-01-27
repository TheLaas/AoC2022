#include <sstream>

#include "common.hpp"
#include "stopwatch.h"

using Vec = std::vector<int>;
#define ORE 0
#define CLAY 1
#define OBS 2
#define GEO 3

#define ID 0
#define C_ORE_ORE 1
#define C_CLAY_ORE 2
#define C_OBS_ORE 3
#define C_OBS_CLAY 4
#define C_GEO_ORE 5
#define C_GEO_OBS 6

#define TIME_CAP 24  // 1
// #define TIME_CAP 32  // 2

class Strategy {
 public:
  Strategy(Vec blueprint) : blueprint(blueprint) {}

  int run() { return build_new({1, 0, 0, 0}, {0, 0, 0, 0}, 0, 0); }
  Vec blueprint = {0, 0, 0, 0, 0, 0, 0};

 private:
  int single_resource_spawn(const Vec setup, const Vec resources, int ind_s,
                            int ind_r, int ind_c_r, int minutes, int max_g) {
    if (max_g >= calc_potential(setup, resources, minutes)) {
      return 0;
    }
    int add_minutes = calc_add_time(ind_r, ind_c_r, setup, resources);

    if (minutes + add_minutes > TIME_CAP) {
      auto updated_resources =
          increase_resources(minutes - TIME_CAP, setup, resources);
      return updated_resources.at(GEO);
    }
    auto updated_resources = increase_resources(add_minutes, setup, resources);
    updated_resources.at(ind_r) -= blueprint.at(ind_c_r);
    auto updated_setup = add_at(ind_s, setup);
    return build_new(updated_setup, updated_resources, minutes + add_minutes,
                     max_g);
  }

  int double_resource_spawn(Vec setup, Vec resources, int ind_s, int ind_r1,
                            int ind_c_r1, int ind_r2, int ind_c_r2, int minutes,
                            int max_g) {
    if (max_g >= calc_potential(setup, resources, minutes) ||
        setup.at(ind_s - 1) == 0) {
      return 0;
    }

    int add_minutes_ore = calc_add_time(ind_r1, ind_c_r1, setup, resources);
    int add_minutes_clay = calc_add_time(ind_r2, ind_c_r2, setup, resources);
    int add_minutes = std::max(add_minutes_ore, add_minutes_clay);
    if (minutes + add_minutes > TIME_CAP) {
      auto updated_resources =
          increase_resources(TIME_CAP - minutes, setup, resources);
      return updated_resources.at(GEO);
    }
    auto updated_resources = increase_resources(add_minutes, setup, resources);
    updated_resources.at(ind_r1) -= blueprint.at(ind_c_r1);
    updated_resources.at(ind_r2) -= blueprint.at(ind_c_r2);
    auto updated_setup = add_at(ind_s, setup);
    return build_new(updated_setup, updated_resources, minutes + add_minutes,
                     max_g);
  }

  int build_new(const Vec setup, const Vec resources, int minutes, int max_g) {
    auto ore = single_resource_spawn(setup, resources, ORE, ORE, C_ORE_ORE,
                                     minutes, max_g);
    max_g = std::max(max_g, ore);
    auto clay = single_resource_spawn(setup, resources, CLAY, ORE, C_CLAY_ORE,
                                      minutes, max_g);
    max_g = std::max(max_g, clay);
    auto obs = double_resource_spawn(setup, resources, OBS, ORE, C_OBS_ORE,
                                     CLAY, C_OBS_CLAY, minutes, max_g);
    max_g = std::max(max_g, obs);
    auto geo = double_resource_spawn(setup, resources, GEO, ORE, C_GEO_ORE, OBS,
                                     C_GEO_OBS, minutes, max_g);
    return std::max(max_g, geo);
  }

  int calc_add_time(int resource_ind, int cost_ind, const Vec setup,
                    const Vec resources) {
    int diff = std::max(blueprint.at(cost_ind) - resources.at(resource_ind), 0);
    return diff % setup.at(resource_ind) == 0
               ? diff / setup.at(resource_ind) + 1
               : diff / setup.at(resource_ind) + 2;
  }

  Vec add_at(int index, const Vec setup) {
    Vec new_vec = {0, 0, 0, 0};
    for (int i = 0; i < 4; ++i) {
      new_vec.at(i) = i == index ? setup.at(i) + 1 : setup.at(i);
    }
    return new_vec;
  }
  Vec increase_resources(int add_minutes, Vec setup, Vec resources) {
    Vec new_vec = {0, 0, 0, 0};
    for (int i = 0; i < 4; ++i) {
      new_vec.at(i) = resources.at(i) + add_minutes * setup.at(i);
    }
    return new_vec;
  }

  int calc_potential(Vec setup, Vec resources, int minutes) {
    int t = TIME_CAP - minutes;

    return t * (t - 1) / 2 + setup.at(GEO) * t + resources.at(GEO);
  };
};

std::vector<int> extractIntegers(std::string line) {
  std::stringstream ss;
  std::vector<int> result;
  ss << line;

  std::string word;
  int number;
  while (!ss.eof()) {
    ss >> word;
    if (std::stringstream(word) >> number) {
      result.push_back(number);
    }
    word = "";
  }
  return result;
}

int main() {
  auto sw = StopWatch();
  auto blueprints =
      helpers::parse_input<std::vector<int>>("input.txt", extractIntegers);

  Vec points;
  int counter = 0;

  // 2
  // blueprints.resize(3);
  //
  for (auto &b : blueprints) {
    auto strategy = Strategy(b);
    sw.Restart();
    auto score = strategy.run();

    // 1
    score *= b.at(ID);
    // 2
    points.push_back(score);
    std::cout << "Current: " << ++counter << " Score: " << score
              << " Time: " << sw.ElapsedSec() << std::endl;
  }
  int sum = 0;
  int product = 1;
  for (auto p : points) {
    sum += p;
    product *= p;
  }
  std::cout << "1. " << sum << std::endl;
  // std::cout << "2. " << product << std::endl;

  return 0;
}
