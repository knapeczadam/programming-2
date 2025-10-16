// Knapecz, Adam - 1DAE11
#pragma once

class Disk final
{
public:
    Disk();
    ~Disk() = default;
    Disk(const Disk& other) = delete;
    Disk(Disk&& other) noexcept = delete;
    Disk& operator=(const Disk& other) = delete;
    Disk& operator=(Disk&& other) noexcept = delete;

    void Draw() const;
    void CheckSelection();
    void Update();
    void UpdatePosition();
    int GetID() const;
    void SetID(int id);
    void SetTopDiskID(int id);
    void SetWidth(float width);
    void SetHeight(float height);
    void SetPos(const Point2f& pos);
    void SetLastPos(const Point2f& pos);
    void SetColor(const Color4f& color);
    bool IsSelected() const;
    void Drag();
    bool IsDraggable() const;
    void SetRect();
    void SetNewTowerID(int id);
    void UpdateTowerID();
    bool IsTowerIDChanged() const;
    int GetTowerID() const;
    float GetWidth() const;

    static const int s_FreeDiskID;

private:
    int m_ID;
    float m_Width;
    float m_Height;
    Point2f m_Pos;
    Point2f m_LastPos;
    Color4f m_Color;
    bool m_IsSelected;
    const float m_LineThickness;
    int m_TopDiskID;
    Rectf m_Rect;
    int m_TowerID;
    int m_NewTowerID;
};
