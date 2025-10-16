// Knapecz, Adam - 1DAE11
#pragma once

#include "Vector2f.h"
#include <vector>

class Texture;

class Level final
{
public:
    explicit Level();
    ~Level();
    void DrawBackground() const;
    void DrawForeground() const;
    void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const;
    bool IsOnGround(const Rectf& actorShape) const;
    void SetVertices();
    Rectf GetBoundaries() const;

private:
    std::vector<Point2f> m_Vertices;
    Texture* m_pBackgroundTexture;
    Texture* m_pFenceTexture;
    Point2f m_FenceBottomLeft;
    Rectf m_Boundaries;
};
