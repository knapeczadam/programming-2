// Knapecz, Adam - 1DAE11
#pragma once

class Texture;

class UI final
{
public:
    UI();
    ~UI() = default;
    UI(const UI& other) = delete;
    UI(UI&& other) noexcept = delete;
    UI& operator=(const UI& other) = delete;
    UI& operator=(UI&& other) noexcept = delete;

    void Draw() const;
    void SetMove(int move);
    void SetViewPort(const Rectf& viewPort);

private:
    int m_Move;
    Rectf m_ViewPort;
};
