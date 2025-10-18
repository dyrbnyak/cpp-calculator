#pragma once

#include <deque>

template<class T, class Comp>
std::deque<T> Merge(const std::deque<T>& half1, const std::deque<T>& half2, const Comp& comparator) {
    // Реализуйте слияние, используя компаратор.
    std::deque<T> result;
    size_t idx1 = 0;
    size_t idx2 = 0;

    while (idx1 < half1.size() && idx2 < half2.size()) {
        if (comparator(half1[idx1], half2[idx2])){
            result.push_back(half1[idx1]);
            idx1 += 1;
        } else {
            result.push_back(half2[idx2]);
            idx2 += 1;
        }
    }

    // Добавляем оставшиеся элементы
    while (idx1 < half1.size()) {
        result.push_back(half1[idx1]);
        idx1 += 1;
    }

    while (idx2 < half2.size()) {
        result.push_back(half2[idx2]);
        idx2 += 1;
    }

    return result;
}

template<class T, class Comp>
std::deque<T> MergeSort(const std::deque<T>& src, const Comp& comparator) {
    // Реализуйте рекурсивную функцию MergeSort
    // на основе задачи из урока о рекурсии.

    if (src.size() <= 1) {
        return src;
    }

    const size_t mid = src.size() / 2;
    const std::deque<T> left_sorted = MergeSort(std::deque(src.begin(), src.begin() + mid), comparator);
    const std::deque<T> right_sorted = MergeSort(std::deque(src.begin() + mid, src.end()), comparator);

    return Merge(left_sorted, right_sorted, comparator);
}
