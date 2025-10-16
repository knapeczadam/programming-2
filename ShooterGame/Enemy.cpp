// Knapecz, Adam - 1DAE11

#include "pch.h"
#include "Enemy.h"
#include "utils.h"

Enemy::Enemy()
	: m_Center{}
	  , m_Width{}
	  , m_Height{}
	  , m_IsDead()
{
}

Enemy::Enemy(const Point2f& center, float width, float height)
	: m_Center{center}
	  , m_Width{width}
	  , m_Height{height}
	  , m_IsDead(false)
	  , m_Color{1.0f, 0, 0, 1.0f}
{
}

// Draw: draws itself from the center. When it is dead it doesn’t draw anything!
void Enemy::Draw() const
{
	utils::SetColor(m_Color);
	utils::DrawRect(GetBounds());
}

/*
 * should return true when the given rectangular object overlaps this
enemy. In this case the enemy dies.
 */
bool Enemy::DoHitTest(const Rectf& other)
{
	const bool hit{utils::IsOverlapping(GetBounds(), other)};
	if (hit)
	{
		m_IsDead = true;
	}
	return hit;
}

void Enemy::SetCenter(const Point2f& center)
{
	m_Center = center;
}

void Enemy::SetDimensions(float width, float height)
{
	m_Width = width;
	m_Height = height;
}

bool Enemy::IsDead() const
{
	return m_IsDead;
}

/*
 * returns the actual bounds (bounding rect) of the Enemy objects,
keeping in mind that it is positioned from the center.
 */
Rectf Enemy::GetBounds() const
{
	Rectf bounds;
	bounds.width = m_Width;
	bounds.height = m_Height;
	bounds.left = m_Center.x - bounds.width / 2;
	bounds.bottom = m_Center.y - bounds.height / 2;
	return bounds;
}
