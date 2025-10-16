// Knapecz, Adam - 1DAE11
#pragma once

class Container final
{
public:
	Container( int capacity = 10); 
	~Container( );

	int Size( ) const;
	int Capacity( ) const;
	int Get( int index ) const;
	void Set( int index, int value );
	void PushBack( int element );

	int& operator[](const int idx);
	const int& operator[](const int idx) const;


private:
	int m_Size;
	int m_Capacity;
	int *m_pElement;

	void Reserve( int newCapacity );
};
