// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "UI.h"
#include "Texture.h"
#include "ColorManager.h"
#include "ScoreManager.h"

UI::UI()
    : m_Move{}
{
}


void UI::Draw() const
{
    Texture text{"Moves: " + std::to_string(ScoreManager::GetScore()), "DIN-Light.otf", 24, ColorManager::s_Black};
    const int border{50};
    const Point2f pos{border, m_ViewPort.height - border};
    text.Draw(pos);
}

void UI::SetMove(int move)
{
    m_Move = move;
}

void UI::SetViewPort(const Rectf& viewPort)
{
    m_ViewPort = viewPort;
}
