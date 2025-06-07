// tests.cpp

#include "Sequence.hpp"
#include "MutableArraySequence.hpp"
#include "MutableListSequence.hpp"
#include "DynamicArray.hpp"
#include "LinkedList.hpp"
#include "Queue.hpp"
#include "Stack.hpp"
#include "PriorityQueue.hpp"
#include "Deque.hpp"

#include <iostream>
#include <cassert>
#include <complex>
#include <string>
#include <ctime>

// ----------------- 1) Функции для теста указателей -------------------

int inc1(int x) {
    return x + 1;
}
int inc2(int x) {
    return x + 2;
}
int inc3(int x) {
    return x + 3;
}

// ----------------- 2) Определения PersonID, Person, Student, Teacher -------------------

/*
  Тип PersonID: используем struct с полями series и number.
  Далее класс Person, в котором храним ID, имя, фамилию, отчество, дату рождения.
  Студент (Student) и преподаватель (Teacher) просто наследуются от Person.
*/

struct PersonID {
    int series;
    int number;
};

class Person {
protected:
    PersonID id;
    std::string firstName;
    std::string middleName;
    std::string lastName;
    std::time_t birthDate;

public:
    Person() = default;
    Person(const PersonID& _id,
           const std::string& _first,
           const std::string& _middle,
           const std::string& _last,
           std::time_t _birth)
        : id(_id),
          firstName(_first),
          middleName(_middle),
          lastName(_last),
          birthDate(_birth)
    {}

    PersonID GetID() const {
        return id;
    }
    std::string GetFirstName() const {
        return firstName;
    }
    std::string GetMiddleName() const {
        return middleName;
    }
    std::string GetLastName() const {
        return lastName;
    }
    std::time_t GetBirthDate() const {
        return birthDate;
    }

    // Возвращает полное имя: «Фамилия Имя Отчество»
    std::string GetFullName() const {
        std::string full = "";
        if (!lastName.empty()) {
            full += lastName;
            full += " ";
        }
        if (!firstName.empty()) {
            full += firstName;
            full += " ";
        }
        if (!middleName.empty()) {
            full += middleName;
        }
        return full;
    }
};

// Класс Student
class Student : public Person {
private:
    std::string group; // Дополнительно: группа студента

public:
    Student() = default;
    Student(const PersonID& _id,
            const std::string& _first,
            const std::string& _middle,
            const std::string& _last,
            std::time_t _birth,
            const std::string& _group)
        : Person(_id, _first, _middle, _last, _birth),
          group(_group)
    {}

    std::string GetGroup() const {
        return group;
    }
};

// Класс Teacher
class Teacher : public Person {
private:
    std::string department; // Дополнительно: кафедра/департамент

public:
    Teacher() = default;
    Teacher(const PersonID& _id,
            const std::string& _first,
            const std::string& _middle,
            const std::string& _last,
            std::time_t _birth,
            const std::string& _dept)
        : Person(_id, _first, _middle, _last, _birth),
          department(_dept)
    {}

    std::string GetDepartment() const {
        return department;
    }
};

// ----------------- 3) Вспомогательная функция для создания даты -------------------

// Принимает год, месяц(1-12), день и возвращает time_t
std::time_t MakeDate(int year, int month, int day) {
    std::tm tm = {};
    tm.tm_year = year - 1900;
    tm.tm_mon  = month - 1;
    tm.tm_mday = day;
    tm.tm_hour = 0;
    tm.tm_min  = 0;
    tm.tm_sec  = 0;
    tm.tm_isdst = -1; // автоопределение перехода на летнее/зимнее время
    return std::mktime(&tm);
}

// ----------------- 4) Обёртка для std::complex<double> -------------------

// PriorityQueue использует std::less<T> по умолчанию (operator<).
// У std::complex<double> нет operator<, поэтому сделаем wrapper,
// сравнивающий по абсолютному значению.
struct ComplexWrapper {
    std::complex<double> value;
    ComplexWrapper() = default;
    ComplexWrapper(const std::complex<double>& v) : value(v) {}

    // «Меньше», если модуль меньше
    bool operator<(const ComplexWrapper& other) const {
        return std::abs(value) < std::abs(other.value);
    }

    bool operator==(const ComplexWrapper& other) const {
        return std::abs(value - other.value) < 1e-12;
    }
};

// ----------------- 5) Основные тесты -------------------

int main() {
    // --- 5.1 Тесты для целых чисел (int) ---
    {
        Queue<int> q_int;
        q_int.Enqueue(10);
        q_int.Enqueue(20);
        assert(q_int.Size() == 2);
        int d1 = q_int.Dequeue();
        assert(d1 == 10);
        assert(q_int.Size() == 1);

        Stack<int> s_int;
        s_int.Push(5);
        s_int.Push(7);
        assert(s_int.Size() == 2);
        int top1 = s_int.Pop();
        assert(top1 == 7);
        assert(s_int.Size() == 1);

        Deque<int> d_int;
        d_int.PushBack(100);
        d_int.PushFront(200);
        assert(d_int.Size() == 2);
        int df = d_int.PopFront();
        assert(df == 200);
        int db = d_int.PopBack();
        assert(db == 100);

        PriorityQueue<int> pq_int;
        pq_int.Push(3);
        pq_int.Push(1);
        pq_int.Push(2);
        assert(pq_int.Size() == 3);
        int p1 = pq_int.Pop();
        int p2 = pq_int.Pop();
        int p3 = pq_int.Pop();
        // По умолчанию max-heap: сначала 3, потом 2, потом 1
        assert(p1 == 3);
        assert(p2 == 2);
        assert(p3 == 1);
    }

    // --- 5.2 Тесты для вещественных чисел (double) ---
    {
        Queue<double> q_double;
        q_double.Enqueue(1.5);
        q_double.Enqueue(2.75);
        assert(q_double.Dequeue() == 1.5);
        assert(q_double.Dequeue() == 2.75);

        Stack<double> s_double;
        s_double.Push(3.14);
        s_double.Push(6.28);
        assert(s_double.Pop() == 6.28);
        assert(s_double.Pop() == 3.14);

        Deque<double> d_double;
        d_double.PushBack(9.81);
        d_double.PushFront(1.618);
        assert(d_double.PopBack() == 9.81);
        assert(d_double.PopFront() == 1.618);

        PriorityQueue<double> pq_double;
        pq_double.Push(2.2);
        pq_double.Push(1.1);
        pq_double.Push(3.3);
        double dp1 = pq_double.Pop();
        double dp2 = pq_double.Pop();
        double dp3 = pq_double.Pop();
        assert(dp1 == 3.3);
        assert(dp2 == 2.2);
        assert(dp3 == 1.1);
    }

    // --- 5.3 Тесты для комплексных чисел (std::complex<double>) через ComplexWrapper ---
    {
        using cd = std::complex<double>;
        Queue<cd> q_cmplx;
        q_cmplx.Enqueue(cd(1.0, 2.0));
        q_cmplx.Enqueue(cd(3.0, 4.0));
        cd c1 = q_cmplx.Dequeue();
        cd c2 = q_cmplx.Dequeue();
        assert(c1 == cd(1.0, 2.0));
        assert(c2 == cd(3.0, 4.0));

        Stack<cd> s_cmplx;
        s_cmplx.Push(cd(5.0, 6.0));
        s_cmplx.Push(cd(7.0, 8.0));
        cd stop = s_cmplx.Pop();
        assert(stop == cd(7.0, 8.0));
        assert(s_cmplx.Pop() == cd(5.0, 6.0));

        Deque<cd> d_cmplx;
        d_cmplx.PushBack(cd(0.5, 0.5));
        d_cmplx.PushFront(cd(1.5, 1.5));
        assert(d_cmplx.PopFront() == cd(1.5, 1.5));
        assert(d_cmplx.PopBack() == cd(0.5, 0.5));

        // Теперь проверяем PriorityQueue<ComplexWrapper>
        PriorityQueue<ComplexWrapper> pq_cmplx;
        pq_cmplx.Push(ComplexWrapper(cd(1.0, 1.0)));  // модуль ≈ 1.414
        pq_cmplx.Push(ComplexWrapper(cd(2.0, 2.0)));  // модуль ≈ 2.828
        pq_cmplx.Push(ComplexWrapper(cd(0.0, 3.0)));  // модуль = 3.0
        ComplexWrapper topc = pq_cmplx.Pop();    // должен получиться (0, 3)
        assert(topc == ComplexWrapper(cd(0.0, 3.0)));
    }

    // --- 5.4 Тесты для строк и символов (std::string, char) ---
    {
        Queue<std::string> q_str;
        q_str.Enqueue("Hello");
        q_str.Enqueue("World");
        assert(q_str.Dequeue() == "Hello");
        assert(q_str.Dequeue() == "World");

        Stack<char> s_char;
        s_char.Push('x');
        s_char.Push('y');
        assert(s_char.Pop() == 'y');
        assert(s_char.Pop() == 'x');

        Deque<std::string> d_str;
        d_str.PushBack("front");
        d_str.PushFront("back");
        assert(d_str.PopFront() == "back");
        assert(d_str.PopBack() == "front");

        // Для string используем стандартный лексикографический (std::less<string>)
        PriorityQueue<std::string> pq_str;
        pq_str.Push("apple");
        pq_str.Push("zebra");
        pq_str.Push("monkey");
        // max-heap: сначала "zebra", потом "monkey", потом "apple"
        assert(pq_str.Pop() == "zebra");
        assert(pq_str.Pop() == "monkey");
        assert(pq_str.Pop() == "apple");
    }

    // --- 5.5 Тесты для указателей на функции (int(*)(int)) ---
    {
        // Используем Deque для демонстрации. Можно использовать любую другую ADT.
        Deque<int(*)(int)> d_fun;
        d_fun.PushBack(&inc1);
        d_fun.PushBack(&inc2);
        d_fun.PushBack(&inc3);
        assert(d_fun.PopFront()(0) == 1);
        assert(d_fun.PopFront()(0) == 2);
        assert(d_fun.PopFront()(0) == 3);

        // Также протестируем Queue:
        Queue<int(*)(int)> q_fun;
        q_fun.Enqueue(&inc1);
        q_fun.Enqueue(&inc2);
        q_fun.Enqueue(&inc3);
        assert(q_fun.Dequeue()(5) == 6); // 5+1
        assert(q_fun.Dequeue()(5) == 7); // 5+2
        assert(q_fun.Dequeue()(5) == 8); // 5+3
    }

    // --- 5.6 Тесты для Student (3 экземпляра) ---
    {
        // Создаём трёх студентов
        Student st1(
            PersonID{10, 1001},
            "Ivan",
            "Petrovich",
            "Ivanov",
            MakeDate(1998, 5, 12),
            "CS-101"
        );
        Student st2(
            PersonID{10, 1002},
            "Petr",
            "Sergeevich",
            "Petrov",
            MakeDate(1999, 6, 20),
            "CS-102"
        );
        Student st3(
            PersonID{10, 1003},
            "Anna",
            "Ivanovna",
            "Sidorova",
            MakeDate(2000, 7, 15),
            "CS-103"
        );

        // Проверяем, что данные сохранились
        assert(st1.GetID().series == 10 && st1.GetID().number == 1001);
        assert(st1.GetFirstName() == "Ivan");
        assert(st1.GetMiddleName() == "Petrovich");
        assert(st1.GetLastName() == "Ivanov");
        assert(st1.GetFullName() == "Ivanov Ivan Petrovich");
        assert(st1.GetGroup() == "CS-101");

        // Аналогично для st2 и st3
        assert(st2.GetID().number == 1002 && st2.GetGroup() == "CS-102");
        assert(st3.GetID().number == 1003 && st3.GetGroup() == "CS-103");

        // Сохраним студентов в Queue<Student> и проверим Dequeue
        Queue<Student> q_st;
        q_st.Enqueue(st1);
        q_st.Enqueue(st2);
        q_st.Enqueue(st3);
        Student ds1 = q_st.Dequeue();
        Student ds2 = q_st.Dequeue();
        Student ds3 = q_st.Dequeue();
        assert(ds1.GetID().number == 1001);
        assert(ds2.GetID().number == 1002);
        assert(ds3.GetID().number == 1003);
    }

    // --- 5.7 Тесты для Teacher (3 экземпляра) ---
    {
        Teacher t1(
            PersonID{20, 2001},
            "Elena",
            "Nikolaevna",
            "Kuznetsova",
            MakeDate(1975, 3, 8),
            "Mathematics"
        );
        Teacher t2(
            PersonID{20, 2002},
            "Sergey",
            "Ivanovich",
            "Volkov",
            MakeDate(1980, 11, 30),
            "Physics"
        );
        Teacher t3(
            PersonID{20, 2003},
            "Olga",
            "Petrovna",
            "Smirnova",
            MakeDate(1985, 1, 22),
            "Computer Science"
        );

        // Проверяем атрибуты
        assert(t1.GetID().series == 20 && t1.GetID().number == 2001);
        assert(t1.GetDepartment() == "Mathematics");
        assert(t1.GetFullName() == "Kuznetsova Elena Nikolaevna");

        assert(t2.GetID().number == 2002 && t2.GetDepartment() == "Physics");
        assert(t3.GetID().number == 2003 && t3.GetDepartment() == "Computer Science");

        // Сохраним преподавателей в Deque<Teacher> и проверим Pop
        Deque<Teacher> d_teach;
        d_teach.PushBack(t1);
        d_teach.PushBack(t2);
        d_teach.PushBack(t3);
        Teacher dt1 = d_teach.PopFront();
        Teacher dt2 = d_teach.PopFront();
        Teacher dt3 = d_teach.PopFront();
        assert(dt1.GetID().number == 2001);
        assert(dt2.GetID().number == 2002);
        assert(dt3.GetID().number == 2003);
    }

    // --- 5.8 Вывод результата, если все assert-ы прошли ---
    std::cout << "=== Все тесты пройдены успешно! ===\n";

    return 0;
}

