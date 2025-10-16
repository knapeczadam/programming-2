// Knapecz, Adam - 1DAE11
#pragma once

class MouseManager final
{
public:
    MouseManager() = default;
    virtual ~MouseManager() = 0;
    MouseManager(const MouseManager& other) = delete;
    MouseManager(MouseManager&& other) noexcept = delete;
    MouseManager& operator=(const MouseManager& other) = delete;
    MouseManager& operator=(MouseManager&& other) noexcept = delete;

    static Point2f GetMousePos();
    static void SetMousePos(const Point2f& mousePos);
    static bool IsDragging();
    static void LMBDown();
    static void LMBUp();
    static Point2f GetDifference();
    static void SetInUse();
    static bool IsInUse();
    static void Release();
    static bool IsLMBIdle();
    static Point2f GetMousePosSnapshot();

private:
    static Point2f s_MousePos;
    static Point2f s_MousePosSnapshot;
    static bool s_IsLMBDown;
    static bool s_IsLMBUp;
    static bool s_IsInUse;
};
