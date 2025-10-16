// Knapecz, Adam - 1DAE11

#pragma once
class Texture;

class PowerUp final
{
public:
    enum class Type
    {
        green = 1,
        brown = 2
    };

    explicit PowerUp(const Point2f& center, PowerUp::Type type);
    ~PowerUp();
    void Update(float elapsedSec);
    void Draw() const;
    bool IsOverlapping(const Rectf& rect) const;
    void SetRadius(float radius);

public:

private:
    const Type m_Type;
    const Texture* m_pTexture;
    const float m_RotSpeed;
    Rectf m_TextClip;
    Circlef m_Shape;
    float m_Angle;
    const char* m_Path;
};
