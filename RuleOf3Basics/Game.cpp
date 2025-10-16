// Knapecz, Adam - 1DAE11

#include "pch.h"
#include "Game.h"
#include "Container.h"
#include <iostream>

Texture Game::m_StatDaeTexture{"DAE.png"};

Game::Game(const Window& window)
    : BaseGame{window}
      , m_DaeTexture{"DAE.png"}
{
    Initialize();
}

Game::~Game()
{
    Cleanup();
}

void Game::Initialize()
{
    TestContainer();
    //m_StatDaeTexture = m_DaeTexture;
}

void Game::Cleanup()
{
}

void Game::Update(float elapsedSec)
{
    // Check keyboard state
    //const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
    //if ( pStates[SDL_SCANCODE_RIGHT] )
    //{
    //	std::cout << "Right arrow key is down\n";
    //}
    //if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
    //{
    //	std::cout << "Left and up arrow keys are down\n";
    //}
}

void Game::Draw() const
{
    ClearBackground();
    m_StatDaeTexture.Draw(Point2f{0.0f, 50.0f});
    DrawTexture(m_DaeTexture, Point2f{0.0f, 200.0f}, 5, 100, 100);
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
    //std::cout << "MOUSEBUTTONDOWN event: ";
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

void Game::ClearBackground() const
{
    glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Game::AddValues(Container& c, int nr, int min, int max)
{
    for (int idx{}; idx < nr; ++idx)
    {
        c.PushBack(rand() % (max - min + 1) + min);
    }
}

void Game::TestContainer()
{
    Container c1{};
    AddValues(c1, 3, 1, 10);
    Container c2{c1};
    c1[0] = 20;
    //
    Container c3{3};
    AddValues(c3, 3, 10, 20);
    c3 = c1;
    //
    c3 = c3;
    //
    c3 = 4;

    Container c4 = c1;
    c4 = c2;

    std::cout << "------" << std::endl;
    c4 = CreateMultiplies(c1, 2);
    std::cout << "------" << std::endl;
    AddValues(c4, 3, 20, 30);
    //
    // AddValues(c1, 20, 0, 10);
    // AddValues(c2, 20, 0, 10);
    // AddValues(c3, 20, 0, 10);
    // AddValues(c4, 20, 0, 10);
}

Container Game::CreateMultiplies(Container c, int factor)
{
    for (int idx{}; idx < c.Size(); ++idx)
    {
        c[idx] *= factor;
    }
    return c;
}

void Game::DrawTexture(const Texture& texture, const Point2f& pos, int nr, int dx, int dy) const
{
    for (int i{}; i < nr; ++i)
    {
        texture.Draw(Point2f{pos.x + i * dx, pos.y + i * dy});
    }
}
