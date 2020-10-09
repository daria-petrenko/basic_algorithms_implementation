#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#define max(a, b) (a > b ? a : b)

using namespace std;

size_t longest_palindromic_subseq_1(const string& s) {  // time complexity: O(n^2), space complexity: O(n^2)
  size_t s_len = s.length();
  vector<vector<size_t>> subseq_len(s_len, vector<size_t>(s_len, 0));
  
  for (size_t i = 0; i < s_len; i++) {
    subseq_len[i][i] = 1;
  }
  
  size_t max_len = 1;
  
  for (size_t i = 0; i < s_len - 1; i++) {
    if (s[i] == s[i + 1]) {
      subseq_len[i][i + 1] = 2;
      if (max_len < 2) {
        max_len = 2;
      }
    } else {
      subseq_len[i][i + 1] = 1;
    }
  }

  for (size_t k = 3; k <= s_len; k++) {  // length of subsequence
    for (size_t i = 0; i <= s_len - k; i++) {  // start index
      size_t j = i + k - 1;  // end index
      if (s[i] == s[j]) {
        subseq_len[i][j] = subseq_len[i + 1][j - 1] + 2;
      } else {
        subseq_len[i][j] = max(subseq_len[i][j - 1], subseq_len[i + 1][j]);
      }
      if (max_len < subseq_len[i][j]) {
        max_len = subseq_len[i][j];
      }
    }
  }
  
  return max_len;
}

size_t longest_palindromic_subseq_2(const string& s) {  // time complexity: O(n^2), space complexity: O(n)
  size_t s_len = s.length();
  vector<size_t> subseq_len(s_len, 0);
  
  for (size_t i = s_len - 1; i != (size_t)-1; i--) {  // start of substring
    size_t prev = 0;  // subseq_len[i - 1][j - 1]
    subseq_len[i] = 1;
    
    for (size_t j = i + 1; j < s_len; j++) {
      if (s[i] == s[j]) {
        size_t tmp = subseq_len[j];  // save subseq_len[i - 1][j - 1] for the next step
        subseq_len[j] = prev + 2;
        prev = tmp;
      } else {
        prev = subseq_len[j]; 
        subseq_len[j] = max(subseq_len[j], subseq_len[j - 1]);  // initially subseq_len[i][j] has subseq_len[i - 1][j] in it,
      }                                                                  // subseq_len[i][j - 1] get from previous step
    }
  }
  return subseq_len[s_len - 1];  // finally has subseq_len[0][s_len - 1] in it
}

  

