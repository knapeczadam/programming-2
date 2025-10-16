// Knapecz, Adam - 1DAE11
#pragma once
#include "DaeRectangle.h"
#include "Vector2f.h"
#include "Texture.h"

class DaeRectLabel : public DaeRectangle
{
public:
	DaeRectLabel(const Point2f& center, float width, float height, const Color4f& color, const std::string& label,
	             const Color4f& textColor, TTF_Font* pFont);
	~DaeRectLabel() override;
	DaeRectLabel(const DaeRectLabel& other) = delete;
	DaeRectLabel(DaeRectLabel&& other) noexcept = delete;
	DaeRectLabel& operator=(const DaeRectLabel& other) = delete;
	DaeRectLabel& operator=(DaeRectLabel&& other) noexcept = delete;
	void Draw() const override;
	std::string ToString() const override;

private:
	Texture* m_pLabelText;
	std::string m_Label;
	float m_MarginX;
	float m_MarginY;
	Color4f m_TextColor;
};
