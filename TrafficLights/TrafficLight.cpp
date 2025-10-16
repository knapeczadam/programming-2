// Knapecz, Adam - 1DAE11

#include "pch.h"
#include "TrafficLight.h"
#include "utils.h"

#include <iostream>

TrafficLight::TrafficLight()
	: m_State{State::off}
	  , m_Width(50.0f)
	  , m_Height(150.0f)
	  , m_Radius(10.0f)
	  , m_AccumulatedSec{0}
{
}

TrafficLight::TrafficLight(const Point2f& pos)
	: m_Position{pos}
	  , m_State{State::off}
	  , m_Width(50.0f)
	  , m_Height(150.0f)
	  , m_Radius(10.0f)
	  , m_AccumulatedSec{0}
{
}

void TrafficLight::DoHitTest(const Point2f& point)
{
	const float left{m_Position.x + m_Width / 2};
	float bottom{m_Position.y + m_Height};
	const float offset{m_Height / 4};

	Circlef circle;
	circle.center.x = left;
	circle.center.y = bottom;
	circle.radius = m_Radius;

	// RED
	circle.center.y -= offset;
	if (utils::IsPointInCircle(point, circle))
	{
		std::cout << "red" << std::endl;
		SetState(State::red);
		return;
	}
	// ORANGE
	circle.center.y -= offset;
	if (utils::IsPointInCircle(point, circle))
	{
		std::cout << "orange" << std::endl;
		SetState(State::orange);
		return;
	}
	// GREEN
	circle.center.y -= offset;
	if (utils::IsPointInCircle(point, circle))
	{
		std::cout << "green" << std::endl;
		SetState(State::green);
		return;
	}
	// ARMATURE
	Rectf rect;
	rect.width = m_Width;
	rect.height = m_Height;
	rect.left = m_Position.x;
	rect.bottom = m_Position.y;
	if (utils::IsPointInRect(point, rect))
	{
		std::cout << "armature" << std::endl;
		SetState(State::off);
	}
}

void TrafficLight::Update(float elapsedSec)
{
	m_AccumulatedSec += elapsedSec;
	switch (m_State)
	{
	case State::off:
		break;
	case State::red:
		if (m_AccumulatedSec >= 4.0f)
		{
			m_State = State::green;
			m_AccumulatedSec = 0;
		}
		break;
	case State::orange:
		if (m_AccumulatedSec >= 1.0f)
		{
			m_State = State::red;
			m_AccumulatedSec = 0;
		}
		break;
	case State::green:
		if (m_AccumulatedSec >= 4.0f)
		{
			m_State = State::orange;
			m_AccumulatedSec = 0;
		}
		break;
	}
}

void TrafficLight::Draw() const
{
	const Color4f red{1.0f, 0, 0, 1.0f};
	const Color4f orange{0.8f, 0.8f, 0, 1.0f};
	const Color4f green{0, 1.0f, 0, 1.0f};
	const Color4f gray{0.2f, 0.2f, 0.2f, 1.0f};
	const Color4f black{0, 0, 0, 1.0f};

	const float left{m_Position.x + m_Width / 2};
	float bottom{m_Position.y + m_Height};

	const float offset{m_Height / 4};

	Ellipsef circle;
	circle.center = Point2f{left, bottom};
	circle.radiusX = m_Radius;
	circle.radiusY = m_Radius;

	// ARMATURE
	utils::SetColor(black);
	utils::FillRect(m_Position, m_Width, m_Height);

	utils::SetColor(gray);

	// RED
	circle.center.y -= offset;
	if (m_State == State::red) utils::SetColor(red);
	utils::FillEllipse(circle);
	utils::SetColor(gray);


	// ORANGE
	circle.center.y -= offset;
	if (m_State == State::orange) utils::SetColor(orange);
	utils::FillEllipse(circle);
	utils::SetColor(gray);

	// GREEN
	circle.center.y -= offset;
	if (m_State == State::green) utils::SetColor(green);
	utils::FillEllipse(circle);
}

float TrafficLight::GetWidth() const
{
	return m_Width;
}

void TrafficLight::SetWidth(float width)
{
	m_Width = width;
}


float TrafficLight::GetHeight() const
{
	return m_Height;
}

void TrafficLight::SetHeight(float height)
{
	m_Height = height;
}

float TrafficLight::GetRadius() const
{
	return m_Radius;
}

void TrafficLight::SetRadius(float radius)
{
	m_Radius = radius;
}

void TrafficLight::SetPosition(const Point2f& newPosition)
{
	m_Position = newPosition;
}

void TrafficLight::SetState(State state)
{
	switch (m_State)
	{
	case State::off:
		m_State = state;
		m_AccumulatedSec = 0;
		break;
	case State::red:
	case State::orange:
	case State::green:
		if (state == State::off) m_State = State::off;
		break;
	}
}
