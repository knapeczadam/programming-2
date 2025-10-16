#pragma once
#include "Vector2f.h"

class DaeShape
{
public:
	explicit DaeShape(const Point2f& center, const Color4f& color);
	virtual ~DaeShape() = default;

	virtual void Draw() const = 0;
	virtual void Translate(const Vector2f& tr) final;

protected:
	Point2f m_Center;
	Color4f m_Color;
};
