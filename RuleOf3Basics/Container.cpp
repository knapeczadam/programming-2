// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "Container.h"
#include <cassert>
#include <iostream>

Container::Container( int capacity ) 
	: m_Size{ 0 }
	, m_Capacity{ capacity }
	, m_pElement{ new int[capacity] }
{
	std::cout << "Container(int) called" << std::endl;
}

Container::~Container( ) 
{ 
	delete[] m_pElement; 
}

Container::Container(const Container& other)
{
	std::cout << "Container(const Container&) called" << std::endl;
	m_Size = other.m_Size;
	m_Capacity = other.m_Capacity;
	m_pElement = new int[m_Capacity];
	for (int i = 0; i < m_Size; ++i)
	{
		m_pElement[i] = other.m_pElement[i];
	}
}

Container& Container::operator=(const Container& other)
{
	std::cout << "Container& operator=(const Container&) called" << std::endl;
	if (this != &other)
	{
		delete[] m_pElement;
		m_Size = other.m_Size;
		m_Capacity = other.m_Capacity;
		m_pElement = new int[m_Capacity];
		for (int i = 0; i < m_Size; ++i)
		{
			m_pElement[i] = other.m_pElement[i];
		}
	}
	return *this;
}

int Container::Size( ) const
{ 
	return m_Size; 
}

int Container::Capacity( ) const
{
	return m_Capacity;
}

int Container::Get( int index ) const
{
	assert( index >= 0 && index < m_Size );
	return m_pElement[index];
}

void Container::Set( int index, int value )
{
	assert( index >= 0 && index < m_Size );
	m_pElement[index] = value;
}

void Container::PushBack( int value )
{
	if ( !( m_Size < m_Capacity ) )
	{
		Reserve( m_Capacity * 2  + 1);
	}
	m_pElement[m_Size] = value;
	++m_Size;
}

//int Container::operator[](int index) const
int& Container::operator[](int index) 
{
	assert(index >= 0 && index < m_Size);
	return m_pElement[index];
}

int Container::operator[](int index) const
{
	assert(index >= 0 && index < m_Size);
	return m_pElement[index];
}

void Container::Reserve( int newCapacity )
{
	if ( newCapacity <= m_Capacity )
	{
		return;
	}

	// Dynamically allocate memory
	int * pNew = new int[newCapacity] {};
	// Copy the elements into this new memory
	for ( int i{ 0 }; i < m_Size; ++i )
	{
		pNew[i] = m_pElement[i];
	}
	// Free the old memory
	delete[] m_pElement;

	// Adapt the data members to this new situation
	m_pElement = pNew;
	m_Capacity = newCapacity;
}



