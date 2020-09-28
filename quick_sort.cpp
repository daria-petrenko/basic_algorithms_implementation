#include <iostream>
#include <vector>
#include "vector_print.h"

using namespace std;

template <typename RandomAccessIterator>
void my_quick_sort(RandomAccessIterator begin, RandomAccessIterator end) {
  size_t cnt_size = end - begin;
  if (cnt_size <= 1) {
    return;
  }
  
  size_t pivot_ind = rand() % cnt_size; // random number in range [0, cnt_size)
  auto pivot = *(begin + pivot_ind);
  swap(*begin, *(begin + pivot_ind));
  
  auto it = begin;
  auto less = begin;
  auto greater = end - 1;
  while (it != greater + 1) {
    if (*it < pivot) {
      swap(*less, *it);
      less++;
      it++;
    } else if (*it > pivot) {
      swap(*greater, *it);
      greater--;
    } else {
      it++;
    }
  }
  
  my_quick_sort(begin, less);
  my_quick_sort(greater + 1, end);
}

  
