// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "MouseManager.h"

Point2f MouseManager::s_MousePos{};
bool MouseManager::s_IsLMBDown{};
bool MouseManager::s_IsLMBUp{};
Point2f MouseManager::s_MousePosSnapshot{};
bool MouseManager::s_IsInUse{};

Point2f MouseManager::GetMousePos()
{
    return s_MousePos;
}

void MouseManager::SetMousePos(const Point2f& mousePos)
{
    s_MousePos = mousePos;
}

bool MouseManager::IsDragging()
{
    return s_IsLMBDown and not s_IsLMBUp;
}

void MouseManager::LMBDown()
{
    s_IsLMBUp = false;
    s_IsLMBDown = true;
    s_MousePosSnapshot = s_MousePos;
}

void MouseManager::LMBUp()
{
    s_IsLMBDown = false;
    s_IsLMBUp = true;
}


Point2f MouseManager::GetDifference()
{
    Point2f diff;
    diff.x = s_MousePos.x - s_MousePosSnapshot.x;
    diff.y = s_MousePos.y - s_MousePosSnapshot.y;
    return diff;
}

void MouseManager::SetInUse()
{
    s_IsInUse = true;
}

bool MouseManager::IsInUse()
{
    return s_IsInUse;
}

void MouseManager::Release()
{
    s_IsInUse = false;
}

bool MouseManager::IsLMBIdle()
{
    return not s_IsLMBDown and not s_IsLMBUp;
}

Point2f MouseManager::GetMousePosSnapshot()
{
    return s_MousePosSnapshot;
}
