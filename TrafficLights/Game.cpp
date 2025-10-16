// Knapecz, Adam - 1DAE11

#include "pch.h"
#include "Game.h"
#include "TrafficLight.h"
#include "utils.h"

#include <iostream>

const int Game::m_NumTrafficLights = 10;

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
	const int rowNum{ 2 };
	const int colNum{ 5 };
	const float border{ 20.0f };
	const float trafficWidth{ 50.0f };
	const float trafficHeight{ 150.0f };
	const float trafficRadius{ 15.0f };

	m_CanvasWidth = border * (colNum + 1) + colNum * trafficWidth;
	m_CanvasHeight = border * (rowNum + 1) + rowNum * trafficHeight;

	float bottom{ GetViewPort().height };

	for (int row{0}; row < rowNum; ++row)
	{
		for (int col{0}; col < colNum; ++col)
		{
			TrafficLight* trafficLight{ new TrafficLight{} };
			trafficLight->SetWidth(trafficWidth);
			trafficLight->SetHeight(trafficHeight);
			trafficLight->SetRadius(trafficRadius);

			Point2f pos;
			pos.x += border + (trafficWidth + border) * col;
			pos.y = bottom - (trafficHeight + border) * (row + 1);
			trafficLight->SetPosition(pos);
			m_TrafficLight.push_back(trafficLight);
		}
	}
}

void Game::Cleanup( )
{
	for (int idx{0}; idx < m_TrafficLight.size(); ++idx)
	{
		delete m_TrafficLight[idx];
	}
}

void Game::Update( float elapsedSec )
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
	for (int idx{0}; idx < m_TrafficLight.size(); ++idx)
	{
		m_TrafficLight[idx]->Update(elapsedSec);
	}
}

void Game::Draw( ) const
{
	ClearBackground( );
	DrawCanvas();
	DrawTrafficLights();

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
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		for (int idx{0}; idx < m_TrafficLight.size(); ++idx)
		{
			const Point2f pos{ float(e.x), float(e.y)};
			m_TrafficLight[idx]->DoHitTest(pos);
		}
		break;
	}
	
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

void Game::DrawTrafficLights() const
{
	for (int idx{0}; idx < m_TrafficLight.size(); ++idx)
	{
		m_TrafficLight[idx]->Draw();
	}
}

void Game::DrawCanvas() const
{
	const Color4f gray{ 0.3f, 0.3f, 0.3f, 1.0f };
	utils::SetColor(gray);
	utils::FillRect(0, GetViewPort().height - m_CanvasHeight, m_CanvasWidth, m_CanvasHeight);
}

