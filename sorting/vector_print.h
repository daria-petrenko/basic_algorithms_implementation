#pragma once
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
  os << "[";
  bool first = true;
  for (const auto& elem : v) {
    if (!first) {
      os << ", ";
    } else {
      first = false;
    }
    os << elem;
  }
  os << "]";
  return os;
}
