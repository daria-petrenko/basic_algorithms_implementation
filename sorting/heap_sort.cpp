#include <iostream>
#include <vector>

using namespace std;

size_t left_child_ind(size_t i) {
  return (i + 1) * 2 - 1;
}

size_t right_child_ind(size_t i) {
  return (i + 1) * 2;
}

size_t parent_ind(size_t i) {
  return i / 2;
}

/**
 *  @brief  Push an element onto a heap.
 *  @param  begin  Start of heap.
 *  @param  end  End of heap.
 * 
 *  Input range [begin, end-1) should be a valid heap. This operation inserts 
 *  (end-1) element onto a heap, after completion [begin, end) is a valid heap.
**/
template <typename RandomAccessIterator>
void my_push_heap(RandomAccessIterator begin, RandomAccessIterator end) {
  size_t ind = end - begin - 1;
  while(*(begin + ind) > *(begin + parent_ind(ind)) and ind != 0) {
    swap(*(begin + ind), *(begin + parent_ind(ind)));
    ind = parent_ind(ind);
  }
}

/**
 *  @brief  Merge two valid heaps.
 *  @param  begin  Start of container.
 *  @param  end  End of container.
 *  @param  ind  Index of new heap root.
 * 
 *  Both children of ind element should be valid heaps. This operation makes 
 *  a tree with root ind a valid heap.
**/
template <typename RandomAccessIterator>
void my_heapify(RandomAccessIterator begin, 
                RandomAccessIterator end, size_t ind) {
  size_t heap_size = end - begin;
  size_t left_child = left_child_ind(ind);
  size_t right_child = right_child_ind(ind);
  
  while (left_child < heap_size) {
    size_t max_child = left_child;
    if (right_child < heap_size and 
        *(begin + right_child) > *(begin + max_child)) {
      max_child = right_child;
    }
    if (*(begin + ind) > *(begin + max_child)) {
      break;
    }
    swap(*(begin + ind), *(begin + max_child));
    ind = max_child;
    left_child = left_child_ind(ind);
    right_child = right_child_ind(ind);
  }
}

/**
 *  @brief  Make a heap.
 *  @param  begin  Start of container.
 *  @param  end  End of container.
 * 
 *  Makes range [begin, end) a valid heap.
**/
template <typename RandomAccessIterator>
void my_make_heap(RandomAccessIterator begin, RandomAccessIterator end) {
  for (size_t i = end - begin - 1; i != (size_t)-1; i--) {
    my_heapify(begin, end, i);
  }
}

/**
 *  @brief  Pop first element from heap.
 *  @param  begin  Start of container.
 *  @param  end  End of container.
 * 
 *  Swaps the first and the last elements in heap, then makes range 
 *  [begin, end-1) a valid heap.
**/
template <typename RandomAccessIterator>
void my_pop_heap(RandomAccessIterator begin, RandomAccessIterator end) {
  size_t heap_size = end - begin;
  if (heap_size <= 1) {
    return;
  }
  swap(*begin, *(begin + heap_size - 1));
  my_heapify(begin, end - 1, 0);
}

/**
 *  @brief  Heap sort.
 *  @param  begin  Start of container.
 *  @param  end  End of container.
 * 
 *  Makes range [begin, end) a valid heap. Then makes in-place heap-sort 
 *  of [begin, end).
**/
template <typename RandomAccessIterator>
void my_heap_sort(RandomAccessIterator begin, RandomAccessIterator end) {
  my_make_heap(begin, end);
  size_t heap_size = end - begin;
  for (size_t i = 0; i < heap_size - 1; i++) {
    my_pop_heap(begin, end - i);
  }
}

