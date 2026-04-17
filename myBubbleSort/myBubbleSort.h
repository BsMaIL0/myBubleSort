#ifndef MY_BUBBLE_SORT_H
#define MY_BUBBLE_SORT_H

#include <utility>

template <typename T, typename Compare = std::less<T>>
void myBubbleSort(T* array, size_t size, Compare comp = std::less<T>{}) {
  if (size <= 1) return;

  for (size_t i = 0; i < size; ++i) {
    bool is_sorted = true;
    for (size_t j = size - 1; j > i; --j) {
      if (comp(array[j], array[j - 1])) {
        std::swap(array[j], array[j - 1]);
        is_sorted = false;
      }
    }
    if (is_sorted) break;
  }
}

#endif