#pragma once
#include "Sequence.hpp"
#include "MutableArraySequence.hpp"
#include <cassert>
#include <iostream>

template<class T>
class Stack {
private:
    std::unique_ptr<Sequence<T>> seq;
public:
    Stack() : seq(new MutableArraySequence<T>()) {}
    void Push(const T& item) { seq->Append(item); }
    T Pop() {
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
    size_t Size() const { return seq->GetLength(); }
    void Print() const {
        size_t n = seq->GetLength();
        for (size_t i = 0; i < n; ++i) std::cout << seq->Get(i) << ' ';
        std::cout << std::endl;
    }
};

