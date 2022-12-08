#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace helpers {

inline bool is_number(const std::string& s) {
  std::string::const_iterator it = s.begin();
  while (it != s.end() && std::isdigit(*it)) ++it;
  return !s.empty() && it == s.end();
}

template <typename T>
inline std::vector<T> parse_input(std::string file_name,
                                  std::function<T(std::string)> parse_line) {
  std::ifstream input_stream(file_name);
  std::vector<T> result;
  std::string line;
  while (getline(input_stream, line)) {
    result.push_back(parse_line(line));
  }
  return result;
}

template <typename T>
inline std::vector<std::vector<T>> parse_input(
    std::string file_name, std::function<T(std::string)> parse_line, int rows) {
  std::ifstream input_stream(file_name);
  std::vector<std::vector<T>> result;
  std::string line;
  while (getline(input_stream, line)) {
    std::vector<T> tmp;
    tmp.push_back(parse_line(line));
    for (int i = 1; i < rows; i++) {
      getline(input_stream, line);
      tmp.push_back(parse_line(line));
    }
    result.push_back(tmp);
  }
  return result;
}

}  // namespace helpers