#include "Queue.hpp"
#include "PriorityQueue.hpp"
#include "Stack.hpp"
#include "Deque.hpp"
#include <iostream>
#include <cassert>

void queueUI() {
    Queue<int> q;
    while (true) {
        std::cout << "\n-- Queue<int> --\n"
                  << "1) Enqueue 2) Dequeue 3) Size 4) Print 0) Back\n> ";
        int c; std::cin >> c; if (!std::cin || !c) break;
        if (c == 1) { int x; std::cin >> x; q.Enqueue(x); }
        else if (c == 2) { std::cout << q.Dequeue() << "\n"; }
        else if (c == 3) { std::cout << q.Size() << "\n"; }
        else if (c == 4) { q.Print(); }
    }
}

void pqueueUI() {
    PriorityQueue<int> pq;
    while (true) {
        std::cout << "\n-- PriorityQueue<int> --\n"
                  << "1) Push 2) Pop 3) Size 4) Print 0) Back\n> ";
        int c; std::cin >> c; if (!std::cin || !c) break;
        if (c == 1) { int x; std::cin >> x; pq.Push(x); }
        else if (c == 2) { std::cout << pq.Pop() << "\n"; }
        else if (c == 3) { std::cout << pq.Size() << "\n"; }
        else if (c == 4) { pq.Print(); }
    }
}

void stackUI() {
    Stack<int> s;
    while (true) {
        std::cout << "\n-- Stack<int> --\n"
                  << "1) Push 2) Pop 3) Size 4) Print 0) Back\n> ";
        int c; std::cin >> c; if (!std::cin || !c) break;
        if (c == 1) { int x; std::cin >> x; s.Push(x); }
        else if (c == 2) { std::cout << s.Pop() << "\n"; }
        else if (c == 3) { std::cout << s.Size() << "\n"; }
        else if (c == 4) { s.Print(); }
    }
}

void dequeUI() {
    Deque<int> d;
    while (true) {
        std::cout << "\n-- Deque<int> --\n"
                  << "1) PushBack 2) PushFront 3) PopBack 4) PopFront 5) Size 6) Print 0) Back\n> ";
        int c; std::cin >> c; if (!std::cin || !c) break;
        if (c == 1) { int x; std::cin >> x; d.PushBack(x); }
        else if (c == 2) { int x; std::cin >> x; d.PushFront(x); }
        else if (c == 3) { std::cout << d.PopBack() << "\n"; }
        else if (c == 4) { std::cout << d.PopFront() << "\n"; }
        else if (c == 5) { std::cout << d.Size() << "\n"; }
        else if (c == 6) { d.Print(); }
    }
}

void selfTestsUI() {
    std::cout << "\n-- Running built-in self-tests --\n";
    Queue<int> q; q.Enqueue(1); q.Enqueue(2);
    assert(q.Dequeue() == 1 && q.Size() == 1);

    PriorityQueue<int> pq; pq.Push(3); pq.Push(1); pq.Push(2);
    assert(pq.Pop() == 3 && pq.Pop() == 2);

    Stack<int> st; st.Push(5); st.Push(6);
    assert(st.Pop() == 6 && st.Size() == 1);

    Deque<int> dq; dq.PushBack(7); dq.PushFront(8);
    assert(dq.PopFront() == 8 && dq.PopBack() == 7);

    std::cout << "All new ADT tests passed!\n";
}

int main() {
    while (true) {
        std::cout << "\n== Menu ==\n"
                  << "1) Queue 2) PriorityQueue 3) Stack 4) Deque 5) Tests 0) Exit\n> ";
        int c; std::cin >> c; if (!std::cin || !c) break;
        switch (c) {
            case 1: queueUI(); break;
            case 2: pqueueUI(); break;
            case 3: stackUI(); break;
            case 4: dequeUI(); break;
            case 5: selfTestsUI(); break;
            default: std::cout << "?\n";
        }
    }
    return 0;
}
