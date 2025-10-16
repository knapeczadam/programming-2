// Knapecz, Adam - 1DAE11
#pragma once
#include "Vector2f.h"
#include <vector>

class Texture;

class Platform
{
public:
    Platform(const Point2f& bottomLeft);
    ~Platform();
    void Draw() const;
    void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const;
    bool IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const;

private:
    void SetVertices();
    Rectf m_Shape;
    Texture* m_pTexture;
    std::vector<Point2f> m_Vertices;
};
