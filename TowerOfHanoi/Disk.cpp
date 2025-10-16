// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "Disk.h"
#include "utils.h"
#include "ColorManager.h"
#include "MouseManager.h"

#include <iostream>

const int Disk::s_FreeDiskID{-1};

Disk::Disk()
    : m_ID{}
      , m_Width{}
      , m_Height{}
      , m_Pos{}
      , m_LastPos{}
      , m_Color{}
      , m_IsSelected{}
      , m_LineThickness{3.0f}
      , m_TopDiskID{}
      , m_Rect()
      , m_TowerID{}
      , m_NewTowerID{}
{
    std::cout << "Disk created\n";
}

void Disk::Draw() const
{
    utils::SetColor(m_Color);
    utils::FillRect(m_Pos, m_Width, m_Height);

    utils::SetColor(ColorManager::s_Black);
    if (m_IsSelected)
    {
        utils::DrawRect(m_Pos, m_Width, m_Height, m_LineThickness);
    }
    else
    {
        utils::DrawRect(m_Pos, m_Width, m_Height);
    }
}

void Disk::CheckSelection()
{
    if (IsDraggable() and MouseManager::IsDragging())
    {
        if (not m_IsSelected)
        {
            if (utils::IsPointInRect(MouseManager::GetMousePosSnapshot(), m_Rect) and not MouseManager::IsInUse())
            {
                m_IsSelected = true;
                MouseManager::SetInUse();
            }
        }
    }
    else
    {
        m_IsSelected = false;
    }
}

void Disk::Update()
{
    CheckSelection();
    UpdatePosition();
}

void Disk::UpdatePosition()
{
    if (m_IsSelected)
    {
        Point2f offset{MouseManager::GetDifference()};
        m_Pos.x = m_LastPos.x + offset.x;
        m_Pos.y = m_LastPos.y + offset.y;
    }
    else
    {
        m_Pos = m_LastPos;
    }
}

int Disk::GetID() const
{
    return m_ID;
}

void Disk::SetID(int id)
{
    m_ID = id;
}

void Disk::SetTopDiskID(int id)
{
    m_TopDiskID = id;
}

void Disk::SetWidth(float width)
{
    m_Width = width;
}

void Disk::SetHeight(float height)
{
    m_Height = height;
}

void Disk::SetPos(const Point2f& pos)
{
    SetLastPos(pos);
    m_Pos = pos;
    SetRect();
}

void Disk::SetLastPos(const Point2f& pos)
{
    m_LastPos = pos;
}

void Disk::SetColor(const Color4f& color)
{
    m_Color = color;
}

bool Disk::IsSelected() const
{
    return m_IsSelected;
}

void Disk::Drag()
{
}

bool Disk::IsDraggable() const
{
    return m_TopDiskID == s_FreeDiskID;
}

void Disk::SetRect()
{
    m_Rect.left = m_Pos.x;
    m_Rect.bottom = m_Pos.y;
    m_Rect.width = m_Width;
    m_Rect.height = m_Height;
}

void Disk::SetNewTowerID(int id)
{
    m_NewTowerID = id;
}

void Disk::UpdateTowerID()
{
    m_TowerID = m_NewTowerID;
}

bool Disk::IsTowerIDChanged() const
{
    return m_TowerID != m_NewTowerID;
}

int Disk::GetTowerID() const
{
    return m_TowerID;
}

float Disk::GetWidth() const
{
    return m_Width;
}
