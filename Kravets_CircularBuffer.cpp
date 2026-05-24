// Kravets_CircularBuffer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
#include "windows.h"

template <typename T>
class CircularBuffer
{
private:
    T* buffer;
    int capacity;
    int head;
    int tail;
    int current_size;

public:
    CircularBuffer(int size)
    {
        capacity = size;
        buffer = new T[capacity];
        head = 0;
        tail = 0;
        current_size = 0;
    }

    ~CircularBuffer()
    {
        delete[] buffer;
    }

    bool is_full() const
    {
        return current_size == capacity;
    }

    bool is_empty() const
    {
        return current_size == 0;
    }

    void write(const T& item)
    {
        if (is_full())
        {
            cout << "Помилка: Буфер повний! Неможливо записати елемент." << endl;
            return;
        }

        buffer[head] = item;
        head = (head + 1) % capacity;
        current_size++;
    }

    T read()
    {
        if (is_empty())
        {
            cout << "Помилка: Буфер порожній! Повертається стандартне значення." << endl;
            return T();
        }

        T item = buffer[tail];
        tail = (tail + 1) % capacity; // Кільцевий зсув індексу читання
        current_size--;

        return item;
    }
};

void main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "Створення буфера на 3 елементи" << endl;
    CircularBuffer<int> cb(3);

    cout << "Буфер порожній? " << (cb.is_empty() ? "Так" : "Ні") << endl;

    cout << "\nЗапис даних" << endl;
    cout << "Записуємо: 10" << endl;
    cb.write(10);
    cout << "Записуємо: 20" << endl;
    cb.write(20);
    cout << "Записуємо: 30" << endl;
    cb.write(30);

    cout << "Буфер повний? " << (cb.is_full() ? "Так" : "Ні") << endl;

    cout << "Спроба записати 40 у повний буфер: ";
    cb.write(40);

    cout << "\nЧитання даних" << endl;
    cout << "Прочитано: " << cb.read() << endl;

    cout << "\nКільцевий запис" << endl;
    cout << "Записуємо: 50" << endl;
    cb.write(50);

    cout << "\nЧитання залишків" << endl;
    cout << "Прочитано: " << cb.read() << endl;
    cout << "Прочитано: " << cb.read() << endl;
    cout << "Прочитано: " << cb.read() << endl; 

    cout << "Спроба читання з порожнього буфера: ";
    cb.read();
}
