// Knapecz, Adam - 1DAE11
#pragma once
#include "Vector2f.h"
#include <vector>

class Texture;

class Platform final
{
public:
    Platform(const Point2f& bottomLeft);
    ~Platform();
    Platform(const Platform& other) = delete;
    Platform(Platform&& other) noexcept = delete;
    Platform& operator=(const Platform& other) = delete;
    Platform& operator=(Platform&& other) noexcept = delete;
    void Draw() const;
    void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const;
    bool IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const;

private:
    void SetVertices();

private:
    Rectf m_Shape;
    Texture* m_pTexture;
    std::vector<Point2f> m_Vertices;
};
