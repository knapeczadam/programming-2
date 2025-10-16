// Knapecz, Adam - 1DAE11
#pragma once

#include "Vector2f.h"

class Level;
class Texture;

class Avatar
{
public:
    enum class ActionState
    {
        waiting,
        moving,
        transforming
    };

public:
    explicit Avatar();
    void Draw() const;
    void UpdatePosition(float elapsedSec, const Level& level);
    void UpdateState();
    void Update(float elapsedSec, const Level& level);
    void MoveHorizontal(const Uint8* pState, float elapsedSec);
    void MoveVertical(const Uint8* pState, float elapsedSec);
    void ApplyGravity(float elapsedSec);
    void MoveAvatar(float elapsedSec, const Uint8* pState);
    void PowerUpHit();
    Rectf GetShape() const;
    void Transform(float elapsedSec);

private:
    void IncreasePower();
    void DrawPower() const;
    void SetStateColor() const;
    void CheckForBoundaries(const Rectf& boundaries);

private:
    Rectf m_Shape;
    float m_HorSpeed;
    float m_JumpSpeed;
    Vector2f m_Velocity;
    Vector2f m_Acceleration;
    ActionState m_ActionState;
    float m_AccuTransformSec;
    float m_MaxTransformSec;
    const int m_MaxPower;
    int m_Power;
};
