// Knapecz, Adam - 1DAE11

#include "pch.h"
#include "Bullet.h"

#include "Enemy.h"
#include "utils.h"

Bullet::Bullet()
	:
	m_Center{}
	, m_Width{}
	, m_Height{}
	, m_Velocity{}
	, m_FieldBoundaries{}
	, m_IsActivated{}
	, m_Color{1.0f, 0, 0, 1.0f}
{
}

Bullet::Bullet(float width, float height, const Rectf& fieldBoundaries)
	: m_Center{}
	  , m_Width{width}
	  , m_Height{height}
	  , m_Velocity{}
	  , m_FieldBoundaries{fieldBoundaries}
	  , m_IsActivated{}
	  , m_Color{1.0f, 0, 0, 1.0f}
{
}

/*
 * only when it is activated, it draws itself (from the center)
 */
void Bullet::Draw() const
{
	if (m_IsActivated)
	{
		utils::SetColor(m_Color);
		utils::FillRect(GetBounds());
	}
}

/*
 * only when it is activated, it changes its position. When it leaves the
field boundaries (CheckBoundaries) it becomes deactivated again.
 */
void Bullet::Update(float elapsedSec, std::vector<Enemy*>& enemies)
{
	if (m_IsActivated)
	{
		m_Center.y += m_Velocity.y * elapsedSec;
		CheckBoundaries();
		CheckEnemiesHit(enemies);
	}
}

/*
 * only when it is not activated yet, it becomes activated, gets the start
position as indicated by the center parameter, and can start moving with the
given velocity. (This function does not actually move the bullet; it just sets
the start state).
 */
void Bullet::Shoot(const Point2f& center, const Vector2f& velocity)
{
	m_Center = center;
	m_Velocity = velocity;
}

void Bullet::SetDimensions(float width, float height)
{
	m_Width = width;
	m_Height = height;
}

void Bullet::SetFieldBoundaries(const Rectf& boundaries)
{
	m_FieldBoundaries = boundaries;
}

void Bullet::CheckBoundaries()
{
	const Rectf bounds{GetBounds()};
	if (bounds.bottom + bounds.height >= m_FieldBoundaries.height)
	{
		m_IsActivated = false;
	}
}

/*
 * After moving the bullet, it calls a CheckEnemiesHit method (todo) to check if one
of the enemies overlaps with the bullet.
As soon as it overlaps one of them, this enemy should be killed and the bullet
should become deactivated again.
 */
void Bullet::CheckEnemiesHit(std::vector<Enemy*>& enemies)
{
	for (Enemy* enemy : enemies)
	{
		if (enemy->IsDead())
		{
			continue;
		}
		if (enemy->DoHitTest(GetBounds()))
		{
			m_IsActivated = false;
			return;
		}
	}
}

void Bullet::IsActivated(bool activated)
{
	m_IsActivated = activated;
}

bool Bullet::IsActivated() const
{
	return m_IsActivated;
}

Rectf Bullet::GetBounds() const
{
	Rectf bounds;
	bounds.width = m_Width;
	bounds.height = m_Height;
	bounds.left = m_Center.x - bounds.width / 2;
	bounds.bottom = m_Center.y - bounds.height / 2;
	return bounds;
}
