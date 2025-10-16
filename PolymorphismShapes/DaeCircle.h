// Knapecz, Adam - 1DAE11
#pragma once
#include "DaeEllipse.h"
#include "Vector2f.h"

class DaeCircle : public DaeEllipse
{
public:
	DaeCircle(const Point2f& center, float diameter, const Color4f& color, bool isFilled);
	~DaeCircle() override = default;

	void Draw() const override;

private:
	float m_Diameter;
};
