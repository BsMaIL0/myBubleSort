# myBubbleSort

**Пузырьковая сортировка на C++ с поддержкой шаблонов, компараторов и комплексным набором тестов.**

Этот проект представляет собой учебную реализацию алгоритма пузырьковой сортировки (`Bubble Sort`) с оптимизацией (ранний выход при отсутствии обменов). Код активно использует шаблоны C++ для работы с любыми типами данных и функциями сравнения.

## Особенности

- **Шаблонная реализация**: Работает с массивами любых типов (`int`, `double`, `char`, `std::string`, пользовательские структуры).
- **Гибкий компаратор**: Поддержка стандартных (`std::less`, `std::greater`) и пользовательских функций сравнения (лямбды, функторы).
- **Оптимизированный алгоритм**: Раннее завершение, если массив уже отсортирован.
- **Корректная обработка краевых случаев**: Пустые массивы, массивы из одного элемента, дубликаты, отрицательные числа.
- **Комплексное тестирование**: Более 20 тестов с использованием GoogleTest, включая тесты производительности и стресс-тесты.
- **Непрерывная интеграция (CI)**: Автоматическая сборка и тестирование через GitHub Actions.

## Начало работы

### Требования

- Компилятор с поддержкой C++17 (gcc, clang, MSVC)
- CMake 3.20 или выше
- (Опционально) Интернет для скачивания GoogleTest во время сборки

### Сборка проекта

```
# Клонируйте репозиторий
git clone https://github.com/yourusername/myBubbleSort.git
cd myBubbleSort

# Создайте директорию для сборки
mkdir build && cd build

# Сгенерируйте файлы сборки
cmake ..

# Выполните сборку
cmake --build .
```

### Примеры использования

Базовый пример (int)

```
#include "myBubbleSort/myBubbleSort.h"

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    myBubbleSort(arr, size);

    // Результат: 11 12 22 25 34 64 90
    return 0;
}
```

Сортировка строк в обратном порядке

```
#include <string>
#include "myBubbleSort/myBubbleSort.h"

int main() {
    std::string arr[] = {"apple", "banana", "cherry"};
    myBubbleSort(arr, 3, std::greater<std::string>());

    // Результат: cherry banana apple
    return 0;
}
```

Пользовательский компаратор (по модулю числа)

```
#include "myBubbleSort/myBubbleSort.h"
#include <cmath>

int main() {
    int arr[] = {-5, 3, -2, 4, -1, 2};
    auto abs_compare = [](int a, int b) {
        return std::abs(a) < std::abs(b);
    };

    myBubbleSort(arr, 6, abs_compare);

    // Результат: -1, -2, 3, 4, -5 (или подобное, с сохранением исходных знаков)
    return 0;
}
```

## Сложность:

Время: O(n²) в худшем и среднем случае, O(n) в лучшем (уже отсортированный массив).

## Структура репозитория

```
myBubbleSort/
├── .github/
│   └── workflows/
│       └── ci.yml               # Конфигурация CI (GitHub Actions)
├── myBubbleSort/
│   └── myBubbleSort.h           # Реализация алгоритма (header-only)
├── tests/
│   └── tests.cpp                # Набор тестов GoogleTest (~400 строк)
├── .clang-format                # Стиль форматирования кода
├── .clang-tidy                  # Настройки статического анализатора
├── .gitignore
├── CMakeLists.txt               # Система сборки
└── README.md
```

## Автор

**Фомин Константин Александрович**

[![GitHub](https://img.shields.io/badge/GitHub-BsMaIL0-181717?logo=github)](https://github.com/BsMaIL0)
[![Codewars](https://img.shields.io/badge/Codewars-BsMaIL-B1361E?logo=codewars)](https://www.codewars.com/users/BsMaIL)

Студент 2 курса СПбГУ, факультет прикладной математики — процессов управления

Проект выполнен в рамках изучения алгоритмов и создания для необходимой базы алгоритмов.
