#pragma once
#include "DaeShape.h"
#include "Vector2f.h"

class DaeRectangle : public DaeShape
{
public:
	DaeRectangle(const Point2f& center, float width, float height, const Color4f& color);
	~DaeRectangle() override = default;
	void Draw() const override;

protected:
	float m_Width;
	float m_Height;
};
