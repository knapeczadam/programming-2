// Knapecz, Adam - 1DAE11

#include "pch.h"
#include "Game.h"
#include "Ball.h"

#include <iostream>


Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	//Ball(const Point2f& center, const Vector2f& velocity, const Color4f& color, float radius);
	const Point2f pos1{ 50.0f, 50.0f };
	const Vector2f vel1{ 20.0f, 20.0f };
	const Color4f col1{ 1.0f, 0, 0, 1.0f };
	const float rad1{ 50.0f };
	Ball* ball1{ new Ball{pos1, vel1, col1, rad1} };

	const Point2f pos2{ 200.0f, 100.0f };
	const Vector2f vel2{ 20.0f, 100.0f };
	const Color4f col2{ 0, 1.0f, 0, 1.0f };
	const float rad2{ 10.0f };
	Ball* ball2{ new Ball{pos2, vel2, col2, rad2} };

	m_Balls[0] = ball1;
	m_Balls[1] = ball2;
}

void Game::Cleanup( )
{
	delete m_Balls[0];
	delete m_Balls[1];
}

void Game::Update( float elapsedSec )
{
	// Check keyboard state
	const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	if ( pStates[SDL_SCANCODE_RIGHT] )
	{
		std::cout << "Right arrow key is down\n";
	}
	if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	{
		std::cout << "Left and up arrow keys are down\n";
	}
	m_Balls[0]->Update(elapsedSec, GetViewPort());
	m_Balls[1]->Update(elapsedSec, GetViewPort());
}

void Game::Draw( ) const
{
	ClearBackground( );
	m_Balls[0]->Draw();
	m_Balls[1]->Draw();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
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

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
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

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
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

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}


