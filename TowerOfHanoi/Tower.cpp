// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "Tower.h"
#include "ColorManager.h"
#include <iostream>
#include <algorithm>
#include "MouseManager.h"
#include "utils.h"

Tower::Tower()
    : m_ID{}
      , m_Width{}
      , m_Height{}
      , m_Thickness{}
      , m_Pos{}
      , m_LineWidth{3.0f}
      , m_Rect{}
      , m_IsActive{}
{
    std::cout << "Tower created\n";
}

void Tower::Draw() const
{
    if (m_IsActive)
    {
        utils::SetColor(ColorManager::s_LightGray);
        utils::FillRect(m_Pos, m_Width, m_Height);
    }

    // MIDDLE
    utils::SetColor(ColorManager::s_Brown);
    Point2f middlePos;
    middlePos.x = m_Pos.x + m_Width / 2 - m_Thickness / 2;
    middlePos.y = m_Pos.y;
    utils::FillRect(middlePos, m_Thickness, m_Height);
    utils::SetColor(ColorManager::s_Black);
    utils::DrawRect(middlePos, m_Thickness, m_Height, m_LineWidth);


    // BASE
    utils::SetColor(ColorManager::s_Brown);
    utils::FillRect(m_Pos, m_Width, m_Thickness);
    utils::SetColor(ColorManager::s_Black);
    utils::DrawRect(m_Pos, m_Width, m_Thickness, m_LineWidth);
}

bool Tower::CheckIfTowerIsActive(Disk* disks, int nrOfDisks)
{
    if (utils::IsPointInRect(MouseManager::GetMousePos(), m_Rect))
    {
        for (int idx{}; idx < nrOfDisks; ++idx)
        {
            if (disks[idx].IsSelected())
            {
                if (HasDisk(disks[idx].GetID()))
                {
                    break;
                }
                disks[idx].SetNewTowerID(m_ID); // reparent disk
                m_IsActive = true;
                return true;
            }
        }
    }
    m_IsActive = false;
    return false;
}

void Tower::Update(Disk* disks, int nrOfDisks)
{
    ReparentDisk(disks, nrOfDisks);
    CheckIfTowerIsActive(disks, nrOfDisks);
}

void Tower::SetID(int id)
{
    m_ID = id;
}

void Tower::SetWidth(float width)
{
    m_Width = width;
}

void Tower::SetHeight(float height)
{
    m_Height = height;
}

void Tower::SetThickness(float thickness)
{
    m_Thickness = thickness;
}

Point2f Tower::GetPos() const
{
    return m_Pos;
}

void Tower::SetPos(const Point2f& pos)
{
    m_Pos = pos;
    SetRect();
}

void Tower::SetRect()
{
    m_Rect.left = m_Pos.x;
    m_Rect.bottom = m_Pos.y;
    m_Rect.width = m_Width;
    m_Rect.height = m_Height;
}

void Tower::AddDisk(int diskID, Disk* disks, int nrOfDisks)
{
    if (!IsEmptyTower())
    {
        disks[GetTopDiskID()].SetTopDiskID(diskID);
    }
    m_DiskIDs.push_back(diskID);
    disks[GetTopDiskID()].SetTopDiskID(Disk::s_FreeDiskID);
}

void Tower::RemoveDisk(Disk* disks, int nrOfDisks)
{
    m_DiskIDs.pop_back();
    if (!IsEmptyTower())
    {
        disks[GetTopDiskID()].SetTopDiskID(Disk::s_FreeDiskID);
    }
}

bool Tower::IsEmptyTower() const
{
    return m_DiskIDs.empty();
}

int Tower::GetTopDiskID() const
{
    return m_DiskIDs.back();
}

int Tower::CountDisks() const
{
    return m_DiskIDs.size();
}

bool Tower::HasDisk(int selectedDiskID) const
{
    return std::find(m_DiskIDs.begin(), m_DiskIDs.end(), selectedDiskID) != m_DiskIDs.end();
}

std::vector<int> Tower::GetDiskIDs() const
{
    return m_DiskIDs;
}

void Tower::ReparentDisk(Disk* disks, int nrOfDisks)
{
    if (m_IsActive)
    {
        bool noneIsSelected{true};
        for (int idx{}; idx < nrOfDisks; ++idx)
        {
            if (disks[idx].IsSelected())
            {
                noneIsSelected = false;
                break;
            }
        }
        if (noneIsSelected)
        {
            for (int idx{}; idx < nrOfDisks; ++idx)
            {
                if (disks[idx].IsTowerIDChanged())
                {
                    // if new disk's ID is greater than the top disk's ID
                    if (IsEmptyTower() or (not IsEmptyTower() and disks[idx].GetID() > GetTopDiskID()))
                    {
                        disks[idx].UpdateTowerID();
                    }
                }
            }
        }
    }
}
