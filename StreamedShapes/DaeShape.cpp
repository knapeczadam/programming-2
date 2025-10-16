// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "DaeShape.h"

DaeShape::DaeShape(const Point2f& center, const Color4f& color)
    : m_Center{center}
      , m_Color{color}
{
}

DaeShape::DaeShape(const Point2f& center, float width, float height, const Color4f& color)
    : m_Center{center}
      , m_Width{width}
      , m_Height{height}
      , m_Color{color}
{
}

void DaeShape::Translate(const Vector2f& tr)
{
    m_Center += tr;
}

std::string DaeShape::PropertiesToString() const
{
    std::string properties;
    properties += "  Center=\"" + std::to_string(m_Center.x) + "," + std::to_string(m_Center.y) + "\"\n";
    properties += "  Width=\"" + std::to_string(m_Width) + "\"\n";
    properties += "  Height=\"" + std::to_string(m_Height) + "\"\n";
    properties += "  Color=\"" + std::to_string(m_Color.r) + "," + std::to_string(m_Color.g) + "," + std::to_string(m_Color.b) + "," + std::to_string(m_Color.a) + "\"\n";
    return properties;
}
