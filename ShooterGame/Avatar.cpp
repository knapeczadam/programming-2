// Knapecz, Adam - 1DAE11

#include "pch.h"
#include "Avatar.h"

#include "Bullet.h"
#include "utils.h"

#include <iostream>

Avatar::Avatar()
	: m_Center{}
	  , m_Width{}
	  , m_Height{}
	  , m_Speed{}
	  , m_FieldBoundaries{}
	  , m_Color{1.0f, 1.0f, 0, 1.0f}
	  , m_pBullet{nullptr}
{
}

Avatar::Avatar(const Point2f& center, float width, float height, const Rectf& fieldBoundaries)
	: m_Center{center}
	  , m_Width{width}
	  , m_Height{height}
	  , m_Speed{200.0f}
	  , m_FieldBoundaries{fieldBoundaries}
	  , m_Color{1.0f, 1.0f, 0, 1.0f}
	  , m_pBullet{nullptr}
{
	const float bulletSize{10.0f};
	m_pBullet = new Bullet{bulletSize, bulletSize, m_FieldBoundaries};
}

Avatar::~Avatar()
{
	delete m_pBullet;
}

/*
 * t changes position with its speed, staying within the
field boundaries (Helper function: Clamp)
 */
void Avatar::MoveLeft(float elapsedSec)
{
	if (GetBounds().left <= m_FieldBoundaries.left)
	{
		return;
	}
	m_Center.x -= m_Speed * elapsedSec;
}

void Avatar::MoveRight(float elapsedSec)
{
	const Rectf bounds{GetBounds()};
	if (bounds.left + bounds.width >= m_FieldBoundaries.width)
	{
		return;
	}
	m_Center.x += m_Speed * elapsedSec;
}

/*
 * shoot (to make sure a bullet starts from the position of the avatar)
 */
void Avatar::Shoot() const
{
	const Vector2f velocity{0.0f, 200.0f};
	m_pBullet->Shoot(m_Center, velocity);
	m_pBullet->IsActivated(true);
}

/*
 * update (to make sure the bullet keeps moving)
Now let’s add the last functionality to our game: an enemy should be killed by
the bullet when they overlap.
There are several options where we can check if the bullet collides with an
enemy; in this case we will do it in the Bullet class.
Therefore, we somehow need to get the enemies information (which is in Game)
to the Bullet class. Just like we do with the methods, we will pass it through the
Avatar class to the Bullet class.
 */
void Avatar::Update(float elapsedSec, std::vector<Enemy*>& enemies)
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	if (pStates[SDL_SCANCODE_RIGHT])
	{
		MoveRight(elapsedSec);
	}
	if (pStates[SDL_SCANCODE_LEFT])
	{
		MoveLeft(elapsedSec);
	}
	if (pStates[SDL_SCANCODE_UP])
	{
		if (!m_pBullet->IsActivated())
		{
			Shoot();
		}
	}
	if (m_pBullet->IsActivated())
	{
		m_pBullet->Update(elapsedSec, enemies);
	}
}


/*
 *  it draws itself from the center (yellow rect)
 */
void Avatar::Draw() const
{
	m_pBullet->Draw();

	utils::SetColor(m_Color);
	utils::FillRect(GetBounds());
}

void Avatar::SetCenter(const Point2f& center)
{
	m_Center = center;
}

void Avatar::SetDimensions(float width, float height)
{
	m_Width = width;
	m_Height = height;
}

void Avatar::SetFieldBoundaries(const Rectf& boundaries)
{
	m_FieldBoundaries = boundaries;
}

void Avatar::Clamp()
{
}

/*
 * returns the actual bounding rect (left,bottom,w,h) of the Avatar,
keeping in mind that it is positioned from the center!
 */
Rectf Avatar::GetBounds() const
{
	Rectf bounds;
	bounds.width = m_Width;
	bounds.height = m_Height;
	bounds.left = m_Center.x - bounds.width / 2;
	bounds.bottom = m_Center.y - bounds.height / 2;
	return bounds;
}
