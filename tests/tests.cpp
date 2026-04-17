#include <gtest/gtest.h>

#include <algorithm>
#include <chrono>
#include <functional>
#include <random>
#include <vector>

// Подключаем вашу сортировку
#include "myBubbleSort/myBubbleSort.h"

// ============================================================================
// Базовые тесты
// ============================================================================

TEST(BubbleSortTest, EmptyArray) {
  int* arr = nullptr;
  // Пустой массив не должен вызывать ошибок
  myBubbleSort(arr, 0);
  SUCCEED();
}

TEST(BubbleSortTest, SingleElement) {
  int arr[] = {42};
  myBubbleSort(arr, 1);
  EXPECT_EQ(arr[0], 42);
}

TEST(BubbleSortTest, TwoElementsSorted) {
  int arr[] = {1, 2};
  myBubbleSort(arr, 2);
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
}

TEST(BubbleSortTest, TwoElementsUnsorted) {
  int arr[] = {2, 1};
  myBubbleSort(arr, 2);
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
}

TEST(BubbleSortTest, ThreeElements) {
  int arr[] = {3, 1, 2};
  myBubbleSort(arr, 3);
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
}

TEST(BubbleSortTest, AlreadySorted) {
  int arr[] = {1, 2, 3, 4, 5};
  myBubbleSort(arr, 5);
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr[i], i + 1);
  }
}

TEST(BubbleSortTest, ReverseSorted) {
  int arr[] = {5, 4, 3, 2, 1};
  myBubbleSort(arr, 5);
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr[i], i + 1);
  }
}

TEST(BubbleSortTest, AllEqual) {
  int arr[] = {7, 7, 7, 7, 7};
  myBubbleSort(arr, 5);
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr[i], 7);
  }
}

TEST(BubbleSortTest, NegativeNumbers) {
  int arr[] = {-5, -1, -10, 0, 3, -2};
  myBubbleSort(arr, 6);

  int expected[] = {-10, -5, -2, -1, 0, 3};
  for (int i = 0; i < 6; ++i) {
    EXPECT_EQ(arr[i], expected[i]);
  }
}

TEST(BubbleSortTest, Duplicates) {
  int arr[] = {5, 2, 8, 2, 5, 1, 8};
  myBubbleSort(arr, 7);

  int expected[] = {1, 2, 2, 5, 5, 8, 8};
  for (int i = 0; i < 7; ++i) {
    EXPECT_EQ(arr[i], expected[i]);
  }
}

// ============================================================================
// Тесты с разными типами данных
// ============================================================================

TEST(BubbleSortTest, DoubleArray) {
  double arr[] = {3.14, 1.41, 2.71, 1.0, 0.5};
  myBubbleSort(arr, 5);

  double expected[] = {0.5, 1.0, 1.41, 2.71, 3.14};
  for (int i = 0; i < 5; ++i) {
    EXPECT_DOUBLE_EQ(arr[i], expected[i]);
  }
}

TEST(BubbleSortTest, CharArray) {
  char arr[] = {'d', 'a', 'c', 'b', 'e'};
  myBubbleSort(arr, 5);

  char expected[] = {'a', 'b', 'c', 'd', 'e'};
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr[i], expected[i]);
  }
}

TEST(BubbleSortTest, StringArray) {
  std::string arr[] = {"banana", "apple", "cherry", "date"};
  myBubbleSort(arr, 4);

  std::string expected[] = {"apple", "banana", "cherry", "date"};
  for (int i = 0; i < 4; ++i) {
    EXPECT_EQ(arr[i], expected[i]);
  }
}

// ============================================================================
// Тесты с компараторами
// ============================================================================

TEST(BubbleSortTest, DescendingOrder) {
  int arr[] = {1, 3, 2, 5, 4};
  myBubbleSort(arr, 5, std::greater<int>{});

  int expected[] = {5, 4, 3, 2, 1};
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr[i], expected[i]);
  }
}

TEST(BubbleSortTest, CustomComparatorAbsoluteValue) {
  int arr[] = {-5, 3, -2, 4, -1, 2};

  auto abs_compare = [](int a, int b) { return std::abs(a) < std::abs(b); };

  myBubbleSort(arr, 6, abs_compare);

  // Проверяем, что массив отсортирован по модулю
  for (int i = 0; i < 5; ++i) {
    EXPECT_LE(std::abs(arr[i]), std::abs(arr[i + 1]));
  }

  // Проверяем, что все элементы на месте (мультимножество)
  std::multiset<int> expected = {-5, -2, -1, 2, 3, 4};
  std::multiset<int> actual(arr, arr + 6);
  EXPECT_EQ(expected, actual);
}

TEST(BubbleSortTest, CustomComparatorEvenFirst) {
  int arr[] = {1, 2, 3, 4, 5, 6};

  // Чётные числа идут первыми
  auto even_first = [](int a, int b) {
    bool a_even = (a % 2 == 0);
    bool b_even = (b % 2 == 0);
    if (a_even != b_even) return a_even > b_even;
    return a < b;
  };

  myBubbleSort(arr, 6, even_first);

  int expected[] = {2, 4, 6, 1, 3, 5};
  for (int i = 0; i < 6; ++i) {
    EXPECT_EQ(arr[i], expected[i]);
  }
}

// ============================================================================
// Тесты с большими массивами
// ============================================================================

TEST(BubbleSortTest, LargeRandomArray) {
  const int size = 1000;
  std::vector<int> arr(size);
  std::vector<int> expected(size);

  // Заполняем случайными числами
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(1, 10000);

  for (int i = 0; i < size; ++i) {
    arr[i] = dist(gen);
    expected[i] = arr[i];
  }

  // Сортируем нашей сортировкой и std::sort
  myBubbleSort(arr.data(), size);
  std::sort(expected.begin(), expected.end());

  // Сравниваем результаты
  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(arr[i], expected[i]);
  }
}

TEST(BubbleSortTest, AlreadySortedLarge) {
  const int size = 10000;
  std::vector<int> arr(size);
  for (int i = 0; i < size; ++i) {
    arr[i] = i;
  }

  // Замеряем время (опционально)
  auto start = std::chrono::high_resolution_clock::now();
  myBubbleSort(arr.data(), size);
  auto end = std::chrono::high_resolution_clock::now();

  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "Already sorted " << size << " elements: " << duration.count()
            << " ms\n";

  // Проверяем, что массив остался отсортированным
  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(arr[i], i);
  }
}

TEST(BubbleSortTest, ReverseSortedLarge) {
  const int size = 5000;
  std::vector<int> arr(size);
  for (int i = 0; i < size; ++i) {
    arr[i] = size - i;
  }

  myBubbleSort(arr.data(), size);

  // Проверяем сортировку
  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(arr[i], i + 1);
  }
}

// ============================================================================
// Edge cases
// ============================================================================

TEST(BubbleSortTest, MaxIntValues) {
  int arr[] = {INT_MAX, INT_MIN, 0, INT_MAX - 1, INT_MIN + 1};
  myBubbleSort(arr, 5);

  // Проверяем, что сортировка работает с крайними значениями
  EXPECT_TRUE(std::is_sorted(arr, arr + 5));
}

TEST(BubbleSortTest, VerySmallDoubles) {
  double arr[] = {1e-10, 1e-12, 1e-11, 1e-9};
  myBubbleSort(arr, 4);

  EXPECT_TRUE(std::is_sorted(arr, arr + 4));
}

// ============================================================================
// Тесты с указателями
// ============================================================================

TEST(BubbleSortTest, PointerArray) {
  int a = 5, b = 2, c = 8, d = 1;
  int* arr[] = {&a, &b, &c, &d};

  // Сортируем указатели по значениям
  myBubbleSort(arr, 4, [](int* x, int* y) { return *x < *y; });

  EXPECT_EQ(*arr[0], 1);
  EXPECT_EQ(*arr[1], 2);
  EXPECT_EQ(*arr[2], 5);
  EXPECT_EQ(*arr[3], 8);
}

// ============================================================================
// Сравнение производительности с std::sort (информативно)
// ============================================================================

TEST(BubbleSortTest, PerformanceComparison) {
  const int size = 1000;
  std::vector<int> arr1(size);
  std::vector<int> arr2(size);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(1, 10000);

  for (int i = 0; i < size; ++i) {
    arr1[i] = dist(gen);
    arr2[i] = arr1[i];
  }

  auto start1 = std::chrono::high_resolution_clock::now();
  myBubbleSort(arr1.data(), size);
  auto end1 = std::chrono::high_resolution_clock::now();

  auto start2 = std::chrono::high_resolution_clock::now();
  std::sort(arr2.begin(), arr2.end());
  auto end2 = std::chrono::high_resolution_clock::now();

  auto duration1 =
      std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);
  auto duration2 =
      std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);

  std::cout << "BubbleSort time: " << duration1.count() << " ms\n";
  std::cout << "std::sort time:   " << duration2.count() << " ms\n";
  std::cout << "Ratio: " << (double)duration1.count() / duration2.count()
            << "x\n";

  // Проверяем, что результаты одинаковы
  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(arr1[i], arr2[i]);
  }
}

// ============================================================================
// Main функция
// ============================================================================

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}