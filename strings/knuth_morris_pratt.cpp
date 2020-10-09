#include <iostream>
#include <string>
#include <vector>
#include "vector_print.h"

using namespace std;

vector<int> prefix_function(const string& s) {
  vector<int> pi(s.size(), 0);
  for (size_t i = 1; i < s.size(); i++) {
    int j = pi[i - 1];
    while(true) {
      if (s[i] == s[j]) {
        pi[i] = j + 1;
        break;
      }
      if (j > 0) {
        j = pi[j - 1];
      } else {
        break;
      }
    }
  }
  return pi;
}
    
      
