// Knapecz, Adam - 1DAE11
#pragma once
#include "DaeEllipse.h"
#include "Vector2f.h"

class DaeCircle : public DaeEllipse
{
public:
	DaeCircle(const Point2f& center, float diameter, const Color4f& color, bool isFilled);
	virtual ~DaeCircle() override = default;
	DaeCircle(const DaeCircle& other) = delete;
	DaeCircle(DaeCircle&& other) noexcept = delete;
	DaeCircle& operator=(const DaeCircle& other) = delete;
	DaeCircle& operator=(DaeCircle&& other) noexcept = delete;
	void Draw() const override;

	std::string ToString() const override;

private:
	float m_Diameter;
};
