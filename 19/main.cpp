#include <sstream>

#include "common.hpp"

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

#define TIME_CAP 24

class Strategy {
 public:
  Strategy(Vec blueprint, int minutes)
      : blueprint(blueprint), minutes(minutes) {}

  Strategy(Vec blueprint, Vec setup, Vec resources, int minutes)
      : blueprint(blueprint),
        setup(setup),
        resources(resources),
        minutes(minutes) {}

  std::vector<Strategy> spawn() {
    std::vector<Strategy> spawned;
    spawned.push_back(spawn_ore());
    spawned.push_back(spawn_clay());
    if (setup.at(CLAY) > 0) spawned.push_back(spawn_obsidian());
    if (setup.at(OBS) > 0) spawned.push_back(spawn_geode());
    return spawned;
  }

  Vec setup = {1, 0, 0, 0};
  Vec resources = {0, 0, 0, 0};
  Vec blueprint;
  int minutes;

 private:
  int calc_add_time(int resource_ind, int cost_ind) {
    int diff = std::max(blueprint.at(cost_ind) - resources.at(resource_ind), 0);
    return diff % setup.at(resource_ind) == 0
               ? diff / setup.at(resource_ind) + 1
               : diff / setup.at(resource_ind) + 2;
  }

  Strategy spawn_ore() {
    int add_minutes = calc_add_time(ORE, C_ORE_ORE);
    if (minutes + add_minutes > TIME_CAP) {
      add_minutes = TIME_CAP - minutes;
      return Strategy(blueprint, setup, increase_resources(add_minutes),
                      TIME_CAP);
    }
    auto updated_resources = increase_resources(add_minutes);
    updated_resources.at(ORE) -= blueprint.at(C_ORE_ORE);
    return Strategy(blueprint, add_at(ORE), updated_resources,
                    minutes + add_minutes);
  }

  Strategy spawn_clay() {
    int add_minutes = calc_add_time(ORE, C_CLAY_ORE);
    if (minutes + add_minutes > TIME_CAP) {
      add_minutes = TIME_CAP - minutes;
      return Strategy(blueprint, setup, increase_resources(add_minutes),
                      TIME_CAP);
    }
    auto updated_resources = increase_resources(add_minutes);
    updated_resources.at(ORE) -= blueprint.at(C_CLAY_ORE);
    return Strategy(blueprint, add_at(CLAY), updated_resources,
                    minutes + add_minutes);
  }
  Strategy spawn_obsidian() {
    int add_minutes_ore = calc_add_time(ORE, C_OBS_ORE);
    int add_minutes_clay = calc_add_time(CLAY, C_OBS_CLAY);
    int add_minutes = std::max(add_minutes_ore, add_minutes_clay);
    if (minutes + add_minutes > TIME_CAP) {
      add_minutes = TIME_CAP - minutes;
      return Strategy(blueprint, setup, increase_resources(add_minutes),
                      TIME_CAP);
    }
    auto updated_resources = increase_resources(add_minutes);
    updated_resources.at(ORE) -= blueprint.at(C_OBS_ORE);
    updated_resources.at(CLAY) -= blueprint.at(C_OBS_CLAY);
    return Strategy(blueprint, add_at(OBS), updated_resources,
                    minutes + add_minutes);
  }
  Strategy spawn_geode() {
    int add_minutes_ore = calc_add_time(ORE, C_GEO_ORE);
    int add_minutes_obs = calc_add_time(OBS, C_GEO_OBS);
    int add_minutes = std::max(add_minutes_ore, add_minutes_obs);
    if (minutes + add_minutes > TIME_CAP) {
      add_minutes = TIME_CAP - minutes;
      return Strategy(blueprint, setup, increase_resources(add_minutes),
                      TIME_CAP);
    }
    auto updated_resources = increase_resources(add_minutes);
    updated_resources.at(ORE) -= blueprint.at(C_GEO_ORE);
    updated_resources.at(OBS) -= blueprint.at(C_GEO_OBS);
    return Strategy(blueprint, add_at(GEO), updated_resources,
                    minutes + add_minutes);
  }
  Vec add_at(int index) {
    Vec new_vec = {0, 0, 0, 0};
    for (int i = 0; i < 4; ++i) {
      new_vec.at(i) = i == index ? setup.at(i) + 1 : setup.at(i);
    }
    return new_vec;
  }
  Vec increase_resources(int add_minutes) {
    Vec new_vec = {0, 0, 0, 0};
    for (int i = 0; i < 4; ++i) {
      new_vec.at(i) = resources.at(i) + add_minutes * setup.at(i);
    }
    return new_vec;
  }
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

int find_max(std::vector<Strategy> es, bool check_score = false) {
  if (es.size() > 0) {
    auto max = std::max_element(
        es.begin(), es.end(), [](const Strategy &a, const Strategy &b) {
          return a.resources.at(GEO) < b.resources.at(GEO);
        });
    return check_score ? max->resources.at(GEO) * max->blueprint.at(ID)
                       : max->resources.at(GEO);
  } else {
    return 0;
  }
};

int calc_potential(Strategy s) {
  int t = TIME_CAP - s.minutes;
  return t * (t - 1) / 2 + s.setup.at(GEO) * t + s.resources.at(GEO);
};

int main() {
  auto blueprints =
      helpers::parse_input<std::vector<int>>("input.txt", extractIntegers);

  Vec points;
  for (auto &b : blueprints) {
    std::vector<Strategy> strategies = {Strategy(b, 0)};
    std::vector<Strategy> evaluated_strategies;
    std::vector<Strategy> ns;
    int max = 0;
    while (true) {
      ns.clear();
      for (auto &s : strategies) {
        if (s.minutes < TIME_CAP && calc_potential(s) < max) {
          // throw away.
        } else if (s.minutes < TIME_CAP) {
          auto ss = s.spawn();
          ns.insert(ns.end(), ss.begin(), ss.end());
        } else {
          evaluated_strategies.push_back(s);
        }
      }
      max = find_max(evaluated_strategies);
      if (ns.size() > 0) {
        strategies.clear();
        strategies.insert(strategies.begin(), ns.begin(), ns.end());
      } else {
        break;
      }
    }
    auto score = find_max(evaluated_strategies, true);
    points.push_back(score);
    evaluated_strategies.clear();
  }

  int sum = 0;
  for (auto p : points) {
    sum += p;
  }
  std::cout << "1. " << sum << std::endl;

  return 0;
}