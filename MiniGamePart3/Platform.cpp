// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "Platform.h"
#include "Texture.h"
#include "utils.h"

Platform::Platform(const Point2f& bottomLeft)
    : m_Shape{bottomLeft.x, bottomLeft.y, 0, 0}
      , m_pTexture{new Texture{"Images/platform copy.png"}}
{
    m_Shape.width = m_pTexture->GetWidth();
    m_Shape.height = m_pTexture->GetHeight();
    SetVertices();
}

Platform::~Platform()
{
    delete m_pTexture;
}

void Platform::Draw() const
{
    m_pTexture->Draw(m_Shape);
    utils::DrawRect(m_Shape.left, m_Shape.bottom, m_Shape.width, m_Shape.height);
}

/*
Handles collision with this platform only when the actor is moving downwards.
 */
void Platform::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const
{
    const Point2f p1{actorShape.left + actorShape.width / 2, actorShape.bottom + actorShape.height / 2};
    const Point2f p2{p1.x, actorShape.bottom};
    utils::HitInfo hit;
    const bool isHit{utils::Raycast(m_Vertices, p1, p2, hit)};
    // Swamp effect
    // if (isHit)
    // {
    //    if (actorVelocity.y < 0.0f and hit.intersectPoint.y < actorShape.bottom)
    //    {
    //        actorShape.bottom = hit.intersectPoint.y;
    //        actorVelocity.y = 0.0f;
    //    } 
    // }
    if (isHit and actorVelocity.y < 0.0f)
    {
        actorShape.bottom = hit.intersectPoint.y;
        actorVelocity.y = 0.0f;
    }
}

/*
Returns true when the given actor is not going upwards and is on the
platform’s top.
 */
bool Platform::IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const
{
    const float epsilon{1.0f};
    const Point2f p1{actorShape.left + actorShape.width / 2, actorShape.bottom};
    const Point2f p2{p1.x, actorShape.bottom - epsilon};
    return actorVelocity.y <= 0.0f && utils::IsOverlapping(p1, p2, m_Shape);
}

void Platform::SetVertices()
{
    m_Vertices.insert(m_Vertices.end(), {
                          Point2f{m_Shape.left, m_Shape.bottom},
                          Point2f{m_Shape.left + m_Shape.width, m_Shape.bottom},
                          Point2f{m_Shape.left + m_Shape.width, m_Shape.bottom + m_Shape.height},
                          Point2f{m_Shape.left, m_Shape.bottom + m_Shape.height},
                          Point2f{m_Shape.left, m_Shape.bottom}
                      });
}
