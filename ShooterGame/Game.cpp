// Knapecz, Adam - 1DAE11

#include "pch.h"
#include "Game.h"

#include "Avatar.h"
#include "Enemy.h"

const int Game::s_NrEnemies{40};

Game::Game(const Window& window)
	: BaseGame{window}
	  , m_pEnemies{s_NrEnemies}
{
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	InitializeAvatar();
	InitializeEnemies();
}

void Game::Cleanup()
{
	delete m_pAvatar;
	DeleteEnemies();
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
	m_pAvatar->Update(elapsedSec, m_pEnemies);
}

void Game::Draw() const
{
	ClearBackground();
	m_pAvatar->Draw();
	DrawEnemies();
}

/*
 * While the left / right arrow key is pressed, the avatar moves left/right
o check when the left or right arrow key is down (use
SDL_GetKeyboardState) to move the Avatar.
o If you do not (fully) understand why we do not do this in the key up
event, ask a teacher!
 */
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

void Game::InitializeAvatar()
{
	const float size{30.0f};
	const Point2f center{GetViewPort().width / 2, size / 2};
	m_pAvatar = new Avatar{center, size, size, GetViewPort()};
}

void Game::InitializeEnemies()
{
	const float size{30.0f};
	const int nrRow{4};
	const int nrCol{10};
	const float offset{GetViewPort().width / (nrCol + 1)};
	for (int row{0}; row < nrRow; ++row)
	{
		for (int col{0}; col < nrCol; ++col)
		{
			Point2f center;
			center.x = offset * (col + 1);
			center.y = GetViewPort().height - offset * (row + 1);
			m_pEnemies[row * nrCol + col] = new Enemy{center, size, size};
		}
	}
}

void Game::DrawEnemies() const
{
	for (const Enemy* enemy : m_pEnemies)
	{
		if (enemy->IsDead())
		{
			continue;
		}
		enemy->Draw();
	}
}

void Game::DeleteEnemies()
{
	for (const Enemy* enemy : m_pEnemies)
	{
		delete enemy;
	}
}
