#pragma once
#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>

template<class T, class Compare = std::less<T>>
class PriorityQueue {
private:
    std::vector<T> data;
    Compare cmp;
public:
    PriorityQueue() = default;
    void Push(const T& item) {
        data.push_back(item);
        std::push_heap(data.begin(), data.end(), cmp);
    }
    T Pop() {
        assert(!data.empty());
        std::pop_heap(data.begin(), data.end(), cmp);
        T item = data.back(); data.pop_back();
        return item;
    }
    size_t Size() const { return data.size(); }
    void Print() const {
        for (const auto& item : data) std::cout << item << ' ';
        std::cout << std::endl;
    }
};
