// Knapecz, Adam - 1DAE11

#include "pch.h"
#include "Game.h"
#include "Diamond.h"
#include "Texture.h"
#include <iostream>
#include <algorithm>
#include <ranges>
#include "utils.h"

Game::Game(const Window& window)
    : BaseGame{window}
      , m_NrOfDiamonds{10}
      , m_Diamonds{}
      , m_Translation{}
      , m_ScalingFactor{1}
      , m_Angle{}
{
    Initialize();
}

Game::~Game()
{
    Cleanup();
}

void Game::Initialize()
{
    Diamond::SetTexture(new Texture{"images/Diamond.png"});
    InitDiamonds();
}

void Game::Cleanup()
{
    Diamond::DeleteTexture();
    DeleteDiamonds();
}

void Game::Update(float elapsedSec)
{
    const Uint8* pStates = SDL_GetKeyboardState(nullptr);
    if (pStates[SDL_SCANCODE_A])
    {
        SetRotation(elapsedSec, false);
    }
    if (pStates[SDL_SCANCODE_D])
    {
        SetRotation(elapsedSec, true);
    }
    if (pStates[SDL_SCANCODE_W])
    {
        SetScaling(elapsedSec, false);
    }
    if (pStates[SDL_SCANCODE_S])
    {
        SetScaling(elapsedSec, true);
    }
    if (pStates[SDL_SCANCODE_UP])
    {
        SetVerticalTranslation(elapsedSec, false);
    }
    if (pStates[SDL_SCANCODE_DOWN])
    {
        SetVerticalTranslation(elapsedSec, true);
    }
    if (pStates[SDL_SCANCODE_LEFT])
    {
        SetHorizontalTranslation(elapsedSec, true);
    }
    if (pStates[SDL_SCANCODE_RIGHT])
    {
        SetHorizontalTranslation(elapsedSec, false);
    }
    if (pStates[SDL_SCANCODE_R])
    {
        ResetDiamonds();
    }
    //UpdateTransformation();
    TransformDiamonds();
}

void Game::Draw() const
{
    ClearBackground();
    DrawDiamonds();
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
    //std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
    //std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
    //switch ( e.keysym.sym )
    //{
    //case SDLK_LEFT:
    //	//std::cout << "Left arrow key released\n";
    //	break;
    //case SDLK_RIGHT:
    //	//std::cout << "`Right arrow key released\n";
    //	break;
    //case SDLK_1:
    //case SDLK_KP_1:
    //	//std::cout << "Key 1 released\n";
    //	break;
    //}
}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
    //std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
    switch (e.button)
    {
    case SDL_BUTTON_LEFT:
        OnMouseDown(Point2f{float(e.x), float(e.y)});
        break;
    }
}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
    //std::cout << "MOUSEBUTTONUP event: ";
    //switch ( e.button )
    //{
    //case SDL_BUTTON_LEFT:
    //	std::cout << " left button " << std::endl;
    //	break;
    //case SDL_BUTTON_RIGHT:
    //	std::cout << " right button " << std::endl;
    //	break;
    //case SDL_BUTTON_MIDDLE:
    //	std::cout << " middle button " << std::endl;
    //	break;
    //}
}

void Game::UpdateTransformation()
{
    for (Diamond* diamond : m_Diamonds)
    {
        if (diamond->IsSelected())
        {
            diamond->SetTranslation(m_Translation);
            diamond->SetRotation(m_Angle);
            diamond->SetScaling(m_ScalingFactor);
        }
    }
}

void Game::OnMouseDown(const Point2f& pos)
{
    std::ranges::for_each(m_Diamonds, [&pos](Diamond* diamond)
    {
        diamond->OnMouseDown(pos);
    });
}

void Game::ResetDiamonds()
{
    std::ranges::for_each(m_Diamonds, [](Diamond* diamond)
    {
        if (diamond->IsSelected())
        {
            diamond->Reset();
        }
    });
}

void Game::DrawDiamonds() const
{
    std::ranges::for_each(m_Diamonds, [](Diamond* diamond)
    {
        diamond->Draw();
    });
}

void Game::TransformDiamonds()
{
    std::ranges::for_each(m_Diamonds, [](Diamond* diamond)
    {
        diamond->TransformVertices();
    });
}

void Game::InitDiamonds()
{
    for (int idx{}; idx < m_NrOfDiamonds; ++idx)
    {
        const Point2f center{GetRandomPosition()};

        m_Diamonds.push_back(new Diamond{center});
    }
}

void Game::DeleteDiamonds()
{
    std::ranges::for_each(m_Diamonds, [](Diamond* diamond)
    {
        delete diamond;
    });
}

void Game::SetRotation(float elapsedSec, bool clockwise)
{
    std::ranges::for_each(m_Diamonds, [&](Diamond* diamond)
    {
        if (diamond->IsSelected())
        {
            float rotation{diamond->GetRotation()};
            if (clockwise)
            {
                rotation += -60 * elapsedSec;
            }
            else
            {
                rotation += 60 * elapsedSec;
            }
            diamond->SetRotation(rotation);
        }
    });
}

void Game::SetScaling(float elapsedSec, bool downScaling)
{
    std::ranges::for_each(m_Diamonds, [&](Diamond* diamond)
    {
        if (diamond->IsSelected())
        {
            float scaling{diamond->GetScaling()};
            if (downScaling)
            {
                scaling /= 1 + 3 * elapsedSec;
            }
            else
            {
                scaling *= 1 + 3 * elapsedSec;
            }
            diamond->SetScaling(scaling);
        }
    });
}

void Game::SetHorizontalTranslation(float elapsedSec, bool left)
{
    std::ranges::for_each(m_Diamonds, [&](Diamond* diamond)
    {
        if (diamond->IsSelected())
        {
            Vector2f translation{diamond->GetTranslation()};
            if (left)
            {
                translation.x -= 120 * elapsedSec;
            }
            else
            {
                translation.x += 120 * elapsedSec;
            }
            diamond->SetTranslation(translation);
        }
    });
}

void Game::SetVerticalTranslation(float elapsedSec, bool down)
{
    std::ranges::for_each(m_Diamonds, [&](Diamond* diamond)
    {
        if (diamond->IsSelected())
        {
            Vector2f translation{diamond->GetTranslation()};
            if (down)
            {
                translation.y -= 120 * elapsedSec;
            }
            else
            {
                translation.y += 120 * elapsedSec;
            }
            diamond->SetTranslation(translation);
        }
    });
}

Point2f Game::GetRandomPosition() const
{
    const int size{48};
    const int minX{size / 2};
    const int maxX{int(GetViewPort().width) - size / 2};
    const int minY{size / 2};
    const int maxY{int(GetViewPort().height) - size / 2};

    const int randX{std::rand() % (maxX - minX) + minX};
    const int randY{std::rand() % (maxY - minY) + minY};
    return Point2f{float(randX), float(randY)};
}

void Game::ClearBackground() const
{
    glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
