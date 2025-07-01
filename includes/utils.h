#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <memory>
#include <iostream>
#include <vector>
#include <functional>

template <typename T>
std::vector<T*> filterByPredicate(const std::vector<T*>& items, std::function<bool(const T*)> predicate) {
    std::vector<T*> result;
    for (const auto& item : items) {
        if (predicate(item)) {
            result.push_back(item);
        }
    }
    return result;
}

template <typename T, typename Predicate>
void afiseazaDaca(const std::vector<std::unique_ptr<T>>& vec, Predicate cond) {
    for (const auto& item : vec) {
        if (cond(item.get())) {
            std::cout << *item << "\n";
        }
    }
}

#endif // UTILS_H
