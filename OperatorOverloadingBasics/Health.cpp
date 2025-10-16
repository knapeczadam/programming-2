// Knapecz, Adam - 1DAE11
// #include "pch.h"
#include "Health.h"

Health::Health( int value) 
	: m_Value{value}
{
}
int Health::GetValue( ) const
{
	return m_Value;
}

Health& Health::operator+=(const int rhs)
{
	m_Value += rhs;
	return *this;
}

Health& Health::operator-=(const int rhs)
{
	m_Value -= rhs;
	return *this;
}

Health operator+(const int lhs, const Health& rhs)
{
	Health health{lhs};
	return health += rhs.GetValue();
	
}

Health operator-(const int lhs, const Health& rhs)
{
	Health health{lhs};
	return health -= rhs.GetValue();
}

Health operator+(const Health& lhs, const int rhs)
{
	Health lhs1{lhs.GetValue()};
	return lhs1 += rhs;
}

Health operator-(const Health& lhs, const int rhs)
{
	Health lhs1{lhs.GetValue()};
	return lhs1 -= rhs;
}


