#include "pch.h"
#include "DaeShape.h"

DaeShape::DaeShape(const Point2f& center, const Color4f& color)
	: m_Center{center}
	  , m_Color{color}
{
}

void DaeShape::Translate(const Vector2f& tr)
{
	m_Center += tr;
}
