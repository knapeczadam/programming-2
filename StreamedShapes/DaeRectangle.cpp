// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "DaeRectangle.h"
#include "utils.h"

DaeRectangle::DaeRectangle(const Point2f& center, float width, float height, const Color4f& color)
    : DaeShape{center, width, height, color}
{
}

void DaeRectangle::Draw() const
{
    utils::SetColor(m_Color);
    utils::FillRect(Point2f{m_Center.x - m_Width / 2, m_Center.y - m_Height / 2}, m_Width, m_Height);
}

std::string DaeRectangle::ToString() const
{
    std::string properties;
    properties += "<DaeRectangle\n";
    properties += PropertiesToString();
    properties += "/>\n";
    return properties;
}
