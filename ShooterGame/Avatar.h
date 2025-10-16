// Knapecz, Adam - 1DAE11
#pragma once

#include <vector>

class Bullet;
class Enemy;

class Avatar
{
public:
	explicit Avatar();
	Avatar(const Point2f& center, float width, float height, const Rectf& fieldBoundaries);
	~Avatar();
	void MoveLeft(float elapsedSec);
	void MoveRight(float elapsedSec);
	void Shoot() const;
	void Update(float elapsedSec, std::vector<Enemy*>& enemies);
	void Draw() const;
	void SetCenter(const Point2f& center);
	void SetDimensions(float width, float height);
	void SetFieldBoundaries(const Rectf& boundaries);
	void Clamp();
	Rectf GetBounds() const;

private:
	Point2f m_Center;
	float m_Width;
	float m_Height;
	float m_Speed;
	Rectf m_FieldBoundaries;
	const Color4f m_Color;

	Bullet* m_pBullet;
};
