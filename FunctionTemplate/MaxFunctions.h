// Knapecz, Adam - 1DAE11
#pragma once
#include <string>
#include "Fraction.h"

// int Max( int a, int b );
// float Max( float a, float b );
// const std::string& Max( const std::string& a, const std::string& b );
// const Fraction& Max( const Fraction& a, const Fraction& b );

template<typename T>
const T& Max( const T& a, const T& b )
{
    return a < b ? b : a;
}
