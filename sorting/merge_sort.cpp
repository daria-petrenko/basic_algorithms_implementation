#include <iostream>
#include <vector>
#include "vector_print.h"

using namespace std;

template <typename RandomAccessIterator>
void my_merge_sort(RandomAccessIterator begin, RandomAccessIterator end) {
  size_t cnt_size = end - begin;
  if (cnt_size <= 1) {
    return;
  }
  size_t left_size = cnt_size / 2;
  my_merge_sort(begin, begin + left_size);
  my_merge_sort(begin + left_size, end);
  
  vector<typename RandomAccessIterator::value_type> tmp_container(cnt_size);
  auto tmp_iter = tmp_container.begin();
  auto left_iter = begin;
  auto right_iter = begin + left_size;
  while (left_iter != begin + left_size and right_iter != end) {
    if (*left_iter < *right_iter) {
      *tmp_iter = *left_iter;
      left_iter++;
      tmp_iter++;
    } else {
      *tmp_iter = *right_iter;
      right_iter++;
      tmp_iter++;
    }
  }
  if (left_iter != begin + left_size) {
    copy(left_iter, begin + left_size, tmp_iter);
  }
  if (right_iter != end) {
    copy(right_iter, end, tmp_iter);
  }
  copy(tmp_container.begin(), tmp_container.end(), begin);
}

