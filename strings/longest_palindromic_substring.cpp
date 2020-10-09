#include <iostream>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

string_view longest_palindromic_substr_dp(string_view s) {  // time complexity: O(n^2), space complexity: O(n^2)
  size_t s_len = s.length();
  vector<vector<bool>> if_palindrome(s_len, vector<bool>(s_len, false));  // if_palindrome[i, j] = true <=> s[i,...j] is palindrome
  for (size_t i = 0; i < s_len; i++) {
    if_palindrome[i][i] = true; // one element is always palindrome
  }
  int max_len = 1;
  size_t start = 0;
  for (size_t k = 2; k <= s_len; k++) {  // length of substring
    for (size_t i = 0; i < s_len - k + 1; i++) {  // start index of substring
      size_t j = i + k - 1; // end index of substring
      if (k == 2 && s[i] == s[j]) {
        if_palindrome[i][j] = true;
        max_len = k;
        start = i;
      } else if (if_palindrome[i + 1][j - 1] && s[i] == s[j]) {
        if_palindrome[i][j] = true;
        max_len = k;
        start = i;
      }
    }
  }
  return s.substr(start, max_len);
}

string_view longest_palindromic_substr_2(string_view s) {  // time complexity: O(n^2), space complexity: O(1)
  size_t s_len = s.length();
  size_t max_len = 0;
  size_t start = 0;
  for (size_t i = 1; i < s_len; i++) { // even length substrings
    size_t j = 1;
    for(; i - j != (size_t)-1 && (i + j - 1) < s_len; j++) {
      if (s[i - j] != s[i + j - 1]) {
        break;
      }
    }
    if (2 * (j - 1) > max_len) {
      max_len = 2 * (j - 1);
      start = i - (j - 1);
    }
  }
  for (size_t i = 0; i < s_len; i++) {  // odd length substrings
    size_t j = 0;
    for (; i - j != (size_t)-1 && i + j < s_len; j++) {
      if (s[i - j] != s[i + j]) {
        break;
      }
    }
    if (1 + 2 * (j - 1) > max_len) {
      max_len = 1 + 2 * (j - 1);
      start = i - (j - 1);
    }
  }
  return s.substr(start, max_len);
}

string_view longest_palindromic_substr_manacher(string_view s) {  // time complexity: O(n), space complexity: O(n)
  size_t s_len = s.length();
  size_t max_len = 0;
  size_t start = 0;
  
  vector<size_t> d1(s_len - 1, 0);  // even length substrings
  vector<size_t> d2(s_len, 0);  //odd length substrings
  
  size_t l = 0, r = 0;
  for (size_t i = 0; i < s_len - 1; i++) {  // building d1[], current space between s[i] and s[i + 1]
    if (i < r) {
      size_t j = l + (r - i) - 1;
      if (d1[j] < (j - l)) {
        d1[i] = d1[j];
        continue;
      } else {
        d1[i] = r - i;
      }
    }
    while (i - d1[i] != (size_t)-1 && i + d1[i] + 1 < s_len) {
      if (s[i - d1[i]] != s[i + d1[i] + 1]) {
        break;
      }
      d1[i]++;
    }
    if (d1[i] > 0 && i + d1[i] > r) {
      r = i + d1[i];
      l = (i + 1) - d1[i];
    }
    if (2 * d1[i] > max_len) {
      max_len = 2 * d1[i];
      start = (i + 1) - d1[i];
    }
  }
  
  l = 0, r = 0;
  for (size_t i = 0; i < s_len; i++) {  // building d2[]
    if (i < r) {
      size_t j = l + (r - i);
      if (d2[j] < j - l) {
        d2[i] = d2[j];
        continue;
      }
      d2[i] = r - i;
    }
    while (i - d2[i] != (size_t)-1 && i + d2[i] < s_len) {
      if (s[i - d2[i]] != s[i + d2[i]]) {
        break;
      }
      d2[i]++;
    }
    if (i + d2[i] - 1 > r) {
      r = i + d2[i] - 1;
      l = (i + 1) - d2[i];
    }
    if (2 * (d2[i] - 1) + 1 > max_len) {
      max_len = 2 * (d2[i] - 1) + 1;
      start = (i + 1) - d2[i];
    }
  }
  
  return s.substr(start, max_len);
}

// one more approach: using suffix tree: time complexity = O(n)
// TODO: Ukkonen's suffix tree construction algorithm (time complexity = O(n)) 

