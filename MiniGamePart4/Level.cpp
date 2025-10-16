// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "Level.h"

#include "SVGParser.h"
#include "Texture.h"
#include "Platform.h"
#include "utils.h"

Level::Level()
    : m_Vertices{}
      , m_pBackgroundTexture{new Texture{"Images/background.png"}}
      , m_pFenceTexture{new Texture{"Images/fence.png"}}
      , m_FenceBottomLeft{200.0f, 190.0f}
      , m_Boundaries{}
      , m_pPlatform{new Platform{Point2f{250.0f, 300.0f}}}
      , m_pEndSignTexture{new Texture{"Images/endSign.png"}}
      , m_EndSignShape{730.0f, 224.0f, 0, 0}
{
    m_Boundaries.width = m_pBackgroundTexture->GetWidth();
    m_Boundaries.height = m_pBackgroundTexture->GetHeight();
    m_EndSignShape.width = m_pEndSignTexture->GetWidth();
    m_EndSignShape.height = m_pEndSignTexture->GetHeight();
    SetVertices();
}

Level::~Level()
{
    delete m_pBackgroundTexture;
    delete m_pFenceTexture;
    delete m_pPlatform;
    delete m_pEndSignTexture;
}

/*
Draws the background texture
 */
void Level::DrawBackground() const
{
    m_pBackgroundTexture->Draw();
    m_pPlatform->Draw();
    utils::DrawPolygon(m_Vertices[0]);
}

/*
Draws the fence texture at the given position
 */
void Level::DrawForeground() const
{
    m_pFenceTexture->Draw(m_FenceBottomLeft);
    m_pEndSignTexture->Draw(m_EndSignShape);
    utils::DrawRect(m_FenceBottomLeft.x, m_FenceBottomLeft.y, m_pFenceTexture->GetWidth(),
                    m_pFenceTexture->GetHeight());
    utils::DrawRect(m_EndSignShape.left, m_EndSignShape.bottom, m_EndSignShape.width, m_EndSignShape.height);
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
    m_pPlatform->HandleCollision(actorShape, actorVelocity);
    const float epsilon{0.0f};
    utils::HitInfo hit;
    Point2f p1, p2;
    p1.x = actorShape.left + actorShape.width / 2;
    p1.y = actorShape.bottom + actorShape.height / 2;
    p2.x = p1.x;
    p2.y = actorShape.bottom - epsilon;
    const bool isHit{utils::Raycast(m_Vertices[0], p1, p2, hit)};
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
bool Level::IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const
{
    const float epsilon{1.0f};
    utils::HitInfo hit;
    Point2f p1, p2;
    p1.x = actorShape.left + actorShape.width / 2;
    p1.y = actorShape.bottom + actorShape.height / 2;
    p2.x = p1.x;
    p2.y = actorShape.bottom - epsilon;
    return utils::Raycast(m_Vertices[0], p1, p2, hit) or m_pPlatform->IsOnGround(actorShape, actorVelocity);
}

void Level::SetVertices()
{
    SVGParser::GetVerticesFromSvgFile("Images/level.svg", m_Vertices);
}

Rectf Level::GetBoundaries() const
{
    return m_Boundaries;
}

bool Level::HasReachedEnd(const Rectf& actorShape) const
{
    const Point2f actorCenter{actorShape.left + actorShape.width / 2, actorShape.bottom + actorShape.height / 2};
    const Point2f endSignCenter{
        m_EndSignShape.left + m_EndSignShape.width / 2, m_EndSignShape.bottom + m_EndSignShape.height / 2
    };
    const float distance{utils::GetDistance(actorCenter, endSignCenter)};
    const float epsilon{50.0f};
    return distance <= epsilon;
}
