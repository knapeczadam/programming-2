// Knapecz, Adam - 1DAE11
#pragma once
#include "DaeShape.h"
#include "Vector2f.h"

class DaeRectangle : public DaeShape
{
public:
	DaeRectangle(const Point2f& center, float width, float height, const Color4f& color);
	virtual ~DaeRectangle() override = default;
	DaeRectangle(const DaeRectangle& other) = delete;
	DaeRectangle(DaeRectangle&& other) noexcept = delete;
	DaeRectangle& operator=(const DaeRectangle& other) = delete;
	DaeRectangle& operator=(DaeRectangle&& other) noexcept = delete;
	void Draw() const override;
	std::string ToString() const override;
};
