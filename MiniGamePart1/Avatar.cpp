// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "Avatar.h"
#include "utils.h"
#include <iostream>
#include <algorithm>
#include "Level.h"
#include "Texture.h"


Avatar::Avatar()
    : m_Shape{50.0f, 280.0f, 36.0f, 97.0f}
      , m_HorSpeed{200.0f}
      , m_JumpSpeed{600.0f}
      , m_Velocity{0.f, 0.f}
      , m_Acceleration{0, -981.0f}
      , m_ActionState{ActionState::moving}
      , m_AccuTransformSec{}
      , m_MaxTransformSec{1.0f}
      , m_MaxPower{3}
      , m_Power{}
{
}

void Avatar::MoveHorizontal(const Uint8* pState, float elapsedSec)
{
    if (pState[SDL_SCANCODE_LEFT])
    {
        m_Velocity.x = -m_HorSpeed;
    }
    else if (pState[SDL_SCANCODE_RIGHT])
    {
        m_Velocity.x = m_HorSpeed;
    }
    else
    {
        m_Velocity.x = 0;
    }
}

void Avatar::MoveVertical(const Uint8* pState, float elapsedSec)
{
    if (pState[SDL_SCANCODE_UP])
    {
        m_Velocity.y = m_JumpSpeed;
    }
    else
    {
        m_Velocity.y = 0;
    }
}

void Avatar::ApplyGravity(float elapsedSec)
{
    m_Velocity += m_Acceleration * elapsedSec;
}

void Avatar::MoveAvatar(float elapsedSec, const Uint8* pState)
{
    MoveHorizontal(pState, elapsedSec);
    MoveVertical(pState, elapsedSec);
}

void Avatar::Update(float elapsedSec, const Level& level)
{
    switch (m_ActionState)
    {
    case ActionState::moving:
    case ActionState::waiting:
        UpdatePosition(elapsedSec, level);
        break;
    case ActionState::transforming:
        Transform(elapsedSec);
        break;
    }
    level.HandleCollision(m_Shape, m_Velocity);
}


void Avatar::UpdatePosition(float elapsedSec, const Level& level)
{
    if (level.IsOnGround(m_Shape))
    {
        const Uint8* pState{SDL_GetKeyboardState(nullptr)};
        MoveAvatar(elapsedSec, pState);
    }
    UpdateState();

    ApplyGravity(elapsedSec);

    m_Shape.left += m_Velocity.x * elapsedSec;
    m_Shape.bottom += m_Velocity.y * elapsedSec;

    CheckForBoundaries(level.GetBoundaries());
}

void Avatar::UpdateState()
{
    if (m_Velocity == Vector2f{})
    {
        m_ActionState = ActionState::waiting;
    }
    else
    {
        m_ActionState = ActionState::moving;
    }
}

void Avatar::Draw() const
{
    SetStateColor();
    utils::FillRect(m_Shape);
    DrawPower();
}


void Avatar::SetStateColor() const
{
    switch (m_ActionState)
    {
    case ActionState::moving:
        utils::SetColor(Color4f{1.0f, 0, 0, 1.0f});
        break;
    case ActionState::transforming:
        utils::SetColor(Color4f{0, 0, 1.0f, 1.0f});
        break;
    case ActionState::waiting:
        utils::SetColor(Color4f{1.0f, 1.0f, 0, 1.0f});
        break;
    }
}

void Avatar::CheckForBoundaries(const Rectf& boundaries)
{
    if (m_Shape.left < boundaries.left)
    {
        m_Shape.left = boundaries.left;
    }
    else if (m_Shape.left + m_Shape.width > boundaries.left + boundaries.width)
    {
        m_Shape.left = boundaries.left + boundaries.width - m_Shape.width;
    }
}

/*
Tells the avatar that it hit a power-up.
 */
void Avatar::PowerUpHit()
{
    m_ActionState = ActionState::transforming;
}

Rectf Avatar::GetShape() const
{
    return m_Shape;
}

void Avatar::Transform(float elapsedSec)
{
    m_AccuTransformSec += elapsedSec;
    if (m_AccuTransformSec >= m_MaxTransformSec)
    {
        IncreasePower();
        m_AccuTransformSec = 0;
        m_ActionState = ActionState::moving;
    }
}

void Avatar::IncreasePower()
{
    if (m_Power < m_MaxPower)
    {
        ++m_Power;
    }
}

void Avatar::DrawPower() const
{
    const float size{5.0f};
    const float offset{size};
    utils::SetColor(Color4f{});
    for (int i{}; i < m_Power; ++i)
    {
        utils::FillRect(Rectf{m_Shape.left + offset + (i * 2 * offset), m_Shape.bottom + offset, size, size});
    }
}
