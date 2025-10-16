// Knapecz, Adam - 1DAE11
#pragma once

#include "Vector2f.h"
#include <vector>


class Texture;
class Platform;

class Level final
{
public:
    explicit Level();
    ~Level();
    Level(const Level& other) = delete;
    Level(Level&& other) noexcept = delete;
    Level& operator=(const Level& other) = delete;
    Level& operator=(Level&& other) noexcept = delete;
    void DrawBackground() const;
    void DrawForeground() const;
    void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const;
    bool IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const;
    Rectf GetBoundaries() const;
    bool HasReachedEnd(const Rectf& actorShape) const;

private:
    void SetVertices();

private:
    std::vector<std::vector<Point2f>> m_Vertices;
    Texture* m_pBackgroundTexture;
    Texture* m_pFenceTexture;
    Point2f m_FenceBottomLeft;
    Rectf m_Boundaries;

    Platform* m_pPlatform;
    Texture* m_pEndSignTexture;
    Rectf m_EndSignShape;
};
