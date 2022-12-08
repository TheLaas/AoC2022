// #include "7.hpp"

#include <boost/algorithm/string.hpp>
#include <map>

#include "common.hpp"
class Dir {
 public:
  Dir(std::string name, Dir *parent) : name(name), parent(parent){};
  ~Dir(){};

  void propagate_files(int size) {
    size_files += size;
    if (name[0] == '/')
      ;
    else {
      parent->propagate_files(size);
    }
  }

  std::string name;
  Dir *parent;
  int size_files = 0;
};

enum Type { CD, LS, DIR, FIL };

struct Line {
  Type type;
  std::vector<std::string> args;
};

int main() {
  auto parse_func = [](std::string line) {
    std::vector<std::string> args;
    boost::split(args, line, boost::is_any_of(" "));
    Line l = {.args = args};
    if (line[0] == '$') {
      if (args.size() == 3) {
        l.type = CD;
      } else {
        l.type = LS;
      }
    } else if (line[0] == 'd') {
      l.type = DIR;
    } else if (std::isdigit(line[0])) {
      l.type = FIL;
    }
    return l;
  };
  auto lines = helpers::parse_input<Line>("input.txt", parse_func);

  std::vector<Dir *> dirs;
  Dir *current_dir;
  Dir *root_dir;
  for (auto line : lines) {
    switch (line.type) {
      case CD:
        if (line.args.at(2)[0] == '.')
          current_dir = current_dir->parent;
        else {
          std::string name = line.args.at(2);
          Dir *dir = new Dir(name, current_dir);
          dirs.push_back(dir);
          current_dir = dir;
          if (name[0] == '/') root_dir = current_dir;
        }
        break;
      case LS:
        break;
      case DIR:
        break;
      case FIL:
        current_dir->propagate_files(std::stoi(line.args.at(0)));
        break;
    }
  }
  int sum = 0;
  int space_needed_freed = 30000000 - (70000000 - root_dir->size_files);
  int min_size_folder_to_delete = root_dir->size_files;
  for (auto &dir : dirs) {
    if (dir->size_files <= 100000) sum += dir->size_files;
    if (dir->size_files >= space_needed_freed) {
      if (dir->size_files < min_size_folder_to_delete) {
        min_size_folder_to_delete = dir->size_files;
      }
    }
  }
  std::cout << "1. Size = " << sum << std::endl;
  std::cout << "2. Size = " << min_size_folder_to_delete << std::endl;

  for (auto *d : dirs) {
    delete d;
  }
  dirs.clear();
  return 0;
}