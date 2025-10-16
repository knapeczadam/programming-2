// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "Level.h"
#include "Texture.h"
#include "utils.h"

Level::Level()
    : m_Vertices{}
      , m_pBackgroundTexture{new Texture{"Images/background.png"}}
      , m_pFenceTexture{new Texture{"Images/fence.png"}}
      , m_FenceBottomLeft{200.0f, 190.0f}
      , m_Boundaries{}
{
    m_Boundaries.width = m_pBackgroundTexture->GetWidth();
    m_Boundaries.height = m_pBackgroundTexture->GetHeight();
    SetVertices();
}

Level::~Level()
{
    delete m_pBackgroundTexture;
    delete m_pFenceTexture;
}

/*
Draws the background texture
 */
void Level::DrawBackground() const
{
    m_pBackgroundTexture->Draw();
    utils::DrawPolygon(m_Vertices);
}

/*
Draws the fence texture at the given position
 */
void Level::DrawForeground() const
{
    m_pFenceTexture->Draw(m_FenceBottomLeft);
}

/*
It handles the vertical collision of the given actor with the level using the
Raycast functionality.
It stops the actor when it penetrates the level:
- the bottom-position is changed to the y value of the intersection point
(actor should not penetrate the level) and
- the vertical part of the actor's velocity becomes 0.
Tip: use Raycast with a vertical ray (blue line) in the middle of the actor.
 */
void Level::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const
{
    const float epsilon{0.0f};
    utils::HitInfo hit;
    Point2f p1, p2;
    p1.x = actorShape.left + actorShape.width / 2;
    p1.y = actorShape.bottom + actorShape.height / 2;
    p2.x = p1.x;
    p2.y = actorShape.bottom - epsilon;
    const bool isHit{utils::Raycast(m_Vertices, p1, p2, hit)};
    if (isHit)
    {
        actorShape.bottom = hit.intersectPoint.y;
        actorVelocity.y = 0.f;
    }
}

/*
Returns true when the actor touches the level, otherwise false is returned.
Tip: use RayCast with a vertical ray in the middle of the actor and that is 1
pixel deeper than the bottom.
 */
bool Level::IsOnGround(const Rectf& actorShape) const
{
    const float epsilon{1.0f};
    utils::HitInfo hit;
    Point2f p1, p2;
    p1.x = actorShape.left + actorShape.width / 2;
    p1.y = actorShape.bottom + actorShape.height / 2;
    p2.x = p1.x;
    p2.y = actorShape.bottom - epsilon;
    return utils::Raycast(m_Vertices, p1, p2, hit);
}

void Level::SetVertices()
{
    m_Vertices.insert(m_Vertices.end(), {
                          Point2f{0.0f, 0.0f},
                          Point2f{0.0f, 190.0f},
                          Point2f{340.0f, 190.0f},
                          Point2f{408.0f, 124.0f},
                          Point2f{560.0f, 124.0f},
                          Point2f{660.0f, 224.0f},
                          Point2f{846.0f, 224.0f},
                          Point2f{846.0f, 0.0f},
                          Point2f{0.0f, 0.0f}
                      });
}

Rectf Level::GetBoundaries() const
{
    return m_Boundaries;
}
