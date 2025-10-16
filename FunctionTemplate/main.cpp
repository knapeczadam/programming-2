// Knapecz, Adam - 1DAE11
#include <iostream>
#include <string>
#include "Fraction.h"
#include "MaxFunctions.h"

void TestMaxFunction( );

int main( )
{
	std::cout << "FunctionTemplate - Name, first name - 1DAEXX\n";
	
	TestMaxFunction( );

	std::cout << "Push ENTER to continue";
	std::cin.get( );
	return 0;
}


void TestMaxFunction( )
{
	std::cout << "--> Test of Max function <--\n";
	// Max of 2 integers
	int int1{ rand( ) };
	int int2{ rand( ) };
	std::cout << "Max of " << int1 << " and " << int2 << " is " << Max( int1, int2 ) << "\n";

	// Max of 2 floats
	float float1{ rand( ) / 100.0f };
	float float2{ rand( ) / 100.0f };
	std::cout << "Max of " << float1 << " and " << float2 << " is " << Max( float1, float2 ) << "\n";

	// Max of 2 strings
	std::string string1{ "abcd" };
	std::string string2{ "abdc" };
	std::cout << "Max of " << string1 << " and " << string2 << " is " << Max( string1, string2 ) << "\n";

	// Max of 2 fractions
	Fraction f1{ 2,3 };
	Fraction f2{ 2,4 };
	std::cout << "Max of " << f1 << " and " << f2 << " is " << Max( f1, f2 ) << "\n";

}


