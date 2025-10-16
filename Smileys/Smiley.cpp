// Knapecz, Adam - 1DAE11
// -- Smiley.cpp file --
// Decide yourself about the necessary include directives
#include "pch.h"
#include "Smiley.h"
#include "Texture.h"
#include "utils.h"
#include <iostream>

// Static Texture data
Texture* Smiley::m_pSmileyTexture{nullptr};
int Smiley::m_InstanceCounter{0};
int Smiley::m_NrSmileys{4};

// Constructor
// Initializes the object, among others:
//	- Initializes the data members, the velocity gets a random value within the inclusive range[60, 180] and [-180, -60]
//	- Creates a texture object to load the image, only if it hasn’t been created before( !)
//  - Adapts the instance counter
Smiley::Smiley(const Point2f& position)
	: m_Position{position}
	  , m_Velocity{}
	  , m_IsHighest{}
	  , m_IsSleeping{}
	  , m_IsInSafeArea{}
	  , m_State{State::neutral}
{
	++m_InstanceCounter;
	const int maxSpeed{60};
	m_Velocity.x = std::rand() % (maxSpeed * 2 + 1) - maxSpeed;
	m_Velocity.y = std::rand() % (maxSpeed * 2 + 1) - maxSpeed;
}

// Destructor
// Deletes the Texture object when this is the last Smiley that is being destroyed.
Smiley::~Smiley()
{
	--m_InstanceCounter;
	if (m_InstanceCounter == 0)
	{
		DeleteTexture();
	}
}

// Draw
// Draws a part of the image on the window, which part depends on the state of the smiley:
// - If the smiley is sleeping then the sleeping smiley is drawn.
// - If the smiley is at the highest position, then the happy smiley is drawn.
// - If the smiley is not in the safe area, the scary smiley is drawn.
// - If none of the above conditions is met, the neutral smiley should be drawn.
void Smiley::Draw() const
{
	Rectf src, dst;
	src.width = m_pSmileyTexture->GetWidth() / 4;
	src.height = m_pSmileyTexture->GetHeight();
	src.bottom = 0.0f;

	switch (m_State)
	{
	case State::happy:
		src.left = 0.0f;
		break;
	case State::neutral:
		src.left = src.width;
		break;
	case State::scared:
		src.left = src.width * 2;
		break;
	case State::sleeping:
		src.left = src.width * 3;
		break;
	}

	dst.width = src.width;
	dst.height = src.height;
	dst.left = m_Position.x;
	dst.bottom = m_Position.y;

	m_pSmileyTexture->Draw(dst, src);
}

// Update
// - When the smiley is not sleeping, the new position - using the velocity and elapsed seconds - is calculated.
// - The velocity changes sign when at this new position the smiley is outside the bounding rectangle (boundingRect)
// - Checks whether at this new position, it is located in the safe area and updates m_IsInSafeArea accordingly.
void Smiley::Update(float elapsedSec, const Rectf& boundingRect, const Rectf& safeRect)
{
	if (!m_IsSleeping)
	{
		m_Position.x += m_Velocity.x * elapsedSec;
		m_Position.y += m_Velocity.y * elapsedSec;

		m_IsInSafeArea = IsInSafeArea(safeRect);
		if (m_IsInSafeArea)
		{
			m_State = State::neutral;
		}
		else
		{
			m_State = State::scared;
		}

		const Point2f bottomLeft = m_Position;
		const Point2f topRight = Point2f{m_Position.x + GetSmileyWidth(), m_Position.y + GetSmileyHeight()};

		if (bottomLeft.x < boundingRect.left || topRight.x > boundingRect.width)
		{
			m_Velocity.x *= -1;
		}
		else if (bottomLeft.y < boundingRect.bottom || topRight.y > boundingRect.height)
		{
			m_Velocity.y *= -1;
		}
	}
}

// HitTest
// If the value of the parameter pos is within the boundaries of the smiley’s circle,
// then the sleeping state of the smiley changes.
void Smiley::HitTest(const Point2f& pos)
{
	Circlef circle;
	circle.radius = GetSmileyWidth() / 2;
	circle.center.x = m_Position.x + circle.radius;
	circle.center.y = m_Position.y + circle.radius;
	if (utils::IsPointInCircle(pos, circle))
	{
		m_IsSleeping = !m_IsSleeping;
	}
	if (m_IsSleeping)
	{
		m_State = State::sleeping;
		m_IsHighest = false;
	}
	else
	{
		m_State = State::neutral;
	}
}

// IsSleeping
// Getter of the m_IsSleeping data member
bool Smiley::IsSleeping() const
{
	return m_IsSleeping;
}

// GetPosition
// Getter of the m_Position data member
Point2f Smiley::GetPosition() const
{
	return m_Position;
}

// SetHighest
// Setter of the m_IsHighest data member
void Smiley::SetHighest(bool isHighest)
{
	m_IsHighest = isHighest;
	if (m_IsHighest)
	{
		m_State = State::happy;
	}
}

// IncreaseSpeed
// Changes the speed 5% up
void Smiley::IncreaseSpeed()
{
	m_Velocity.x *= 1.05f;
	m_Velocity.y *= 1.05f;
}

// DecreaseSpeed
// Changes the speed 5% down
void Smiley::DecreaseSpeed()
{
	m_Velocity.x *= 0.95f;
	m_Velocity.y *= 0.95f;
}

void Smiley::LoadTexture()
{
	m_pSmileyTexture = new Texture{"Textures/Smileys.png"};
}

void Smiley::DeleteTexture()
{
	delete m_pSmileyTexture;
}

float Smiley::GetSmileyWidth()
{
	return m_pSmileyTexture->GetWidth() / m_NrSmileys;
}

float Smiley::GetSmileyHeight()
{
	return m_pSmileyTexture->GetHeight();
}

// IsInSafeArea
// Returns true when the smiley is completely inside the safe area as indicated by safeRect
bool Smiley::IsInSafeArea(const Rectf& safeRect)
{
	const Point2f bottomLeft = m_Position;
	const Point2f topRight = Point2f{m_Position.x + GetSmileyWidth(), m_Position.y + GetSmileyHeight()};

	if (bottomLeft.x <= safeRect.left || topRight.x >= safeRect.left + safeRect.width)
	{
		return false;
	}
	if (bottomLeft.y <= safeRect.bottom || topRight.y >= safeRect.bottom + safeRect.height)
	{
		return false;
	}
	return true;
}
