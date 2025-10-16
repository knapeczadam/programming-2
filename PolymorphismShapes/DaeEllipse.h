// Knapecz, Adam - 1DAE11
#pragma once
#include "DaeShape.h"
#include "Vector2f.h"

class DaeEllipse : public DaeShape
{
public:
	DaeEllipse(const Point2f& center, float width, float height, const Color4f& color, bool isFilled);
	~DaeEllipse() override = default;

	void Draw() const override;

protected:
	bool m_IsFilled;

private:
	float m_Width;
	float m_Height;
};
