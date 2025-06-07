#pragma once
#include "Sequence.hpp"
#include "MutableArraySequence.hpp"
#include <cassert>
#include <iostream>

template<class T>
class Deque {
private:
    std::unique_ptr<Sequence<T>> seq;
public:
    Deque() : seq(new MutableArraySequence<T>()) {}
    void PushBack(const T& item) { seq->Append(item); }
    void PushFront(const T& item) { seq->Prepend(item); }
    T PopBack() {
        assert(seq->GetLength() > 0);
        size_t idx = seq->GetLength() - 1;
        T item = seq->Get(idx);
        if (idx > 0) {
            seq = seq->GetSubsequence(0, idx - 1);
        } else {
            seq.reset(new MutableArraySequence<T>());
        }
        return item;
    }
    T PopFront() {
        assert(seq->GetLength() > 0);
        T item = seq->Get(0);
        size_t len = seq->GetLength();
        if (len > 1) {
            seq = seq->GetSubsequence(1, len - 1);
        } else {
            seq.reset(new MutableArraySequence<T>());
        }
        return item;
    }
    size_t Size() const { return seq->GetLength(); }
    void Print() const {
        size_t n = seq->GetLength();
        for (size_t i = 0; i < n; ++i) std::cout << seq->Get(i) << ' ';
        std::cout << std::endl;
    }
};
