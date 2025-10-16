// Knapecz, Adam - 1DAE11
#pragma once

class Camera
{
public:
    explicit Camera(float width, float height);
    explicit Camera() = default;
    void SetLevelBoundaries(const Rectf& levelBoundaries);
    void Draw(const Rectf& target) const;
    void Transform(const Rectf& target) const;
    Point2f Track(const Rectf& target) const;
    void Clamp(Point2f& bottomLeftPos) const;
    void SetWidth(float width);
    void SetHeight(float height);

private:
    float m_Width;
    float m_Height;
    Rectf m_LevelBoundaries;
};
