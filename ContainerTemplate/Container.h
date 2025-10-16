// Knapecz, Adam - 1DAE11
#pragma once
#include <initializer_list>

template <typename T>
class Container
{
public:
    explicit Container(int capacity = 10);
    Container(const std::initializer_list<T>& list);
    Container(const Container& other);
    Container& operator=(const Container& other);
    Container(Container&& other) noexcept;
    Container& operator=(Container&& other) noexcept;
    ~Container();

    int Size() const;
    int Capacity() const;
    T Get(int index) const;
    void Set(int index, T value);
    void PushBack(T element);
    T& operator[](int index);
    const T& operator[](int index) const;

private:
    int m_Size;
    int m_Capacity;
    T* m_pElements;

    void Reserve(int newCapacity);
};
