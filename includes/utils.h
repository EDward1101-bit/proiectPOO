#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <memory>
#include <iostream>

template <typename T, typename Predicate>
void afiseazaDaca(const std::vector<std::unique_ptr<T>>& vec, Predicate cond) {
    for (const auto& item : vec) {
        if (cond(item.get())) {
            std::cout << *item << "\n";
        }
    }
}

#endif // UTILS_H
