// Knapecz, Adam - 1DAE11
#pragma once
#include <deque>

#include "Vector2f.h"

class TrailingCircle
{
public:
	TrailingCircle( float radius, const Point2f& center);
	void Update( float elapsedSec, const Rectf& boundingRect );
	void Draw( ) const;

private:
	void DrawTrails( ) const;
	void UpdateTrails(float elapsedSec);
	const float m_Radius;
	const Color4f m_Color;
	Point2f m_Center;
	Vector2f m_Velocity;

	Vector2f GetRandomVelocity( );
	Color4f GetRandomColor();

	std::deque<Point2f> m_Trails;
	const size_t m_MaxTrails;

	float m_AccuSec;
	const float m_TrailInterval;
};
