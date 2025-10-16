// Knapecz, Adam - 1DAE11
#pragma once
class Square
{
public:
	Square(float size);
	Square(float left, float bottom);
	Square(float size, float left, float bottom);
	~Square();

	// Member functions
	void Print() const;
	void Translate(float deltaLeft, float deltaBottom);
	void SetSize(float newSize);

private:
	// Data members
	float m_Left;
	float m_Bottom;
	float m_Size;

	// Helper functions
	float GetArea() const;
	float GetPerimeter() const;

};
