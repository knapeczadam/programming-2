// Knapecz, Adam - 1DAE11
#pragma once

class Container
{
public:
	explicit Container(int capacity = 10);
	~Container();
	int Size() const;
	int Capacity() const;
	int Get(int index) const;
	void Set(int index, int newValue);
	void PushBack(int element);
	void Reserve(int newCapacity);
private:
	int m_Size;
	int m_Capacity;
	int* m_pDynArray;
};

