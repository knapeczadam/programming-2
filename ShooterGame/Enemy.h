// Knapecz, Adam - 1DAE11

#pragma once
class Enemy
{
public:
	explicit Enemy();
	Enemy(const Point2f& center, float width, float height);
	void Draw() const;
	bool DoHitTest(const Rectf& other);
	void SetCenter(const Point2f& center);
	void SetDimensions(float width, float height);
	bool IsDead() const;
	Rectf GetBounds() const;

private:
	Point2f m_Center;
	float m_Width;
	float m_Height;
	bool m_IsDead;
	const Color4f m_Color;
};
