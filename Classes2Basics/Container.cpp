// Knapecz, Adam - 1DAE11
#include "Container.h"
#include <exception>

Container::Container(int capacity)
	: m_Size{}
	, m_Capacity{capacity}
	, m_pDynArray{nullptr}
{
	m_pDynArray = new int[m_Capacity];
}

Container::~Container()
{
	delete m_pDynArray;
}

int Container::Size() const
{
	return m_Size;
}

int Container::Capacity() const
{
	return m_Capacity;
}

int Container::Get(int index) const
{
	if (index < 0)
	{
		throw std::exception{ "Negative out-of-range exception" };
	}
	if (index >= m_Size)
	{
		throw std::exception{ "Positive out-of-range exception" };
	}
	return m_pDynArray[index];
}

void Container::Set(int index, int newValue)
{
	if (index < 0)
	{
		throw std::exception{ "Negative out-of-range exception" };
	}
	if (index >= m_Size)
	{
		throw std::exception{ "Positive out-of-range exception" };
	}
	m_pDynArray[index] = newValue;
}

void Container::PushBack(int element)
{
	if (m_Capacity == m_Size)
	{
		m_Capacity *= 2;
		int* temp = new int[m_Capacity];
		for (int idx{0}; idx < m_Size; ++idx)
		{
			temp[idx] = m_pDynArray[idx];
		}
		delete m_pDynArray;
		m_pDynArray = temp;
	}
	m_pDynArray[m_Size++] = element;

}

void Container::Reserve(int newCapacity)
{
	int* temp = new int[newCapacity];
	for (int idx{0}; idx < m_Size; ++idx)
	{
		temp[idx] = m_pDynArray[idx];
	}
	delete m_pDynArray;
	m_pDynArray = temp;
}
