// Knapecz, Adam - 1DAE11
#pragma once
#include "DaeShape.h"
#include "Vector2f.h"

class DaeEllipse : public DaeShape
{
public:
	DaeEllipse(const Point2f& center, float width, float height, const Color4f& color, bool isFilled);
	virtual ~DaeEllipse() override = default;
	DaeEllipse(const DaeEllipse& other) = delete;
	DaeEllipse(DaeEllipse&& other) noexcept = delete;
	DaeEllipse& operator=(const DaeEllipse& other) = delete;
	DaeEllipse& operator=(DaeEllipse&& other) noexcept = delete;
	void Draw() const override;
	std::string ToString() const override;

protected:
	bool m_IsFilled;
};
