// Knapecz, Adam - 1DAE11
#pragma once
#include "Vector2f.h"

class DaeShape 
{
public:
	explicit DaeShape(const Point2f& center, const Color4f& color);
	explicit DaeShape(const Point2f& center, float width, float height, const Color4f& color);
	virtual ~DaeShape() = default;
	DaeShape(const DaeShape& other) = delete;
	DaeShape(DaeShape&& other) noexcept = delete;
	DaeShape& operator=(const DaeShape& other) = delete;
	DaeShape& operator=(DaeShape&& other) noexcept = delete;

	virtual void Draw() const = 0;
	virtual void Translate(const Vector2f& tr) final;
	std::string PropertiesToString() const;
	virtual std::string ToString() const = 0;

protected:
	Point2f m_Center;
	float m_Width;
	float m_Height;
	Color4f m_Color;
};
