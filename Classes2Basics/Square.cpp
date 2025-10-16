// Knapecz, Adam - 1DAE11
#include "Square.h"
#include <iostream>
#include <iomanip>

Square::Square(float size)
	: m_Left{ }
	, m_Bottom{  }
	, m_Size{ size }
{
	std::cout << "Constructor: Square( float size ), creates resources" << std::endl;
}

Square::Square(float left, float bottom)
	: m_Left{left}
	, m_Bottom{bottom}
	, m_Size{10.0f}
{
	std::cout << "Constructor: Square( float left, float bottom ), creates resources" << std::endl;
}

Square::Square(float size, float left, float bottom)
	: m_Left{ left }
	, m_Bottom{ bottom }
	, m_Size{ size }
{
	std::cout << "Constructor: Square( float left, float bottom, float size ), creates resources" << std::endl;
}

Square::~Square()
{
	std::cout << "Square destructor: release the resources\n";
}


void Square::Print() const
{
	std::cout << std::fixed;
	std::cout << "Left: ";
	std::cout << std::setprecision(2) << m_Left;

	std::cout << ", bottom: ";
	std::cout << std::setprecision(2) << m_Bottom << std::endl;

	std::cout << "Size: ";
	std::cout << std::setprecision(2) << m_Size << std::endl;

	std::cout << "Perimeter: ";
	std::cout << std::setprecision(2) << GetPerimeter() << std::endl;;
	std::cout << "Area: ";
	std::cout << std::setprecision(2) << GetArea() << std::endl;;
}

void Square::Translate(float deltaLeft, float deltaBottom)
{
	m_Left += deltaLeft;
	m_Bottom += deltaBottom;
}
void Square::SetSize(float newSize)
{
	m_Size = newSize;
}

float Square::GetArea() const
{
	return m_Size * m_Size;
}

float Square::GetPerimeter() const
{
	return 4 * m_Size;
}
