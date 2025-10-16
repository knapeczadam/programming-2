// Knapecz, Adam - 1DAE11

#include "Vector2f.h"
#include <vector>

class Enemy;

#pragma once
class Bullet
{
public:
	explicit Bullet();
	Bullet(float width, float height, const Rectf& fieldBoundaries);
	void Draw() const;
	void Update(float elapsedSec, std::vector<Enemy*>& enemies);
	void Shoot(const Point2f& center, const Vector2f& velocity);
	void SetDimensions(float width, float height);
	void SetFieldBoundaries(const Rectf& boundaries);
	void CheckBoundaries();
	void CheckEnemiesHit(std::vector<Enemy*>& enemies);
	void IsActivated(bool activated);
	bool IsActivated() const;
	Rectf GetBounds() const;

private:
	Point2f m_Center;
	float m_Width;
	float m_Height;
	Vector2f m_Velocity;
	Rectf m_FieldBoundaries;
	bool m_IsActivated;
	const Color4f m_Color;
};
