// Knapecz, Adam - 1DAE11
#pragma once
#include "Disk.h"

#include <vector>

class Tower final
{
public:
#pragma
    Tower();
    ~Tower() = default;
    Tower(const Tower& other) = delete;
    Tower(Tower&& other) noexcept = delete;
    Tower& operator=(const Tower& other) = delete;
    Tower& operator=(Tower&& other) noexcept = delete;

    void Draw() const;
    bool CheckIfTowerIsActive(Disk* disks, int nrOfDisks);
    void Update(Disk* disks, int nrOfDisks);
    void ReparentDisk(Disk* disks, int nrOfDisks);
    void SetID(int id);
    void SetWidth(float width);
    void SetHeight(float height);
    void SetThickness(float thickness);
    Point2f GetPos() const;
    void SetPos(const Point2f& pos);
    void SetRect();
    void AddDisk(int diskID, Disk* disks, int nrOfDisks);
    void RemoveDisk(Disk* disks, int nrOfDisks);
    bool IsEmptyTower() const;
    int GetTopDiskID() const;
    int CountDisks() const;
    bool HasDisk(int diskID) const;
    std::vector<int> GetDiskIDs() const;

private:
    int m_ID;
    float m_Width;
    float m_Height;
    float m_Thickness;
    Point2f m_Pos;
    const float m_LineWidth;
    Rectf m_Rect;
    bool m_IsActive;
    std::vector<int> m_DiskIDs;
};
