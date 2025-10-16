// Knapecz, Adam - 1DAE11

#include "pch.h"
#include "Game.h"

#include <iostream>

#include "cmath"
#include "utils.h"

Game::Game(const Window& window)
	: BaseGame{window}
{
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	const float closeVerticalOffset{50.0f};
	const float farVerticalOffset{100.0f};
	const float horizontalOffset{100.0f};

	const Point2f A{GetViewPort().width / 2, closeVerticalOffset};
	const Point2f B{GetViewPort().width - horizontalOffset, farVerticalOffset};
	const Point2f C{GetViewPort().width - horizontalOffset, GetViewPort().height - farVerticalOffset};
	const Point2f D{GetViewPort().width / 2, GetViewPort().height - closeVerticalOffset};
	const Point2f E{horizontalOffset, C.y};
	const Point2f F{horizontalOffset, farVerticalOffset};

	m_Vertices.push_back(A);
	m_Vertices.push_back(B);
	m_Vertices.push_back(C);
	m_Vertices.push_back(D);
	m_Vertices.push_back(E);
	m_Vertices.push_back(F);
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

	utils::SetColor(Color4f{0, 0, 0, 1.0f});
	utils::FillPolygon(m_Vertices);
	utils::SetColor(Color4f{1.0f, 0, 0, 1.0f});
	utils::DrawPolygon(m_Vertices);

	// The Ray (yellow)
	Point2f p1, p2;
	p1.x = GetViewPort().width / 2;
	p1.y = GetViewPort().height / 2;
	p2 = m_MousePos;
	utils::SetColor(Color4f{1.0f, 1.0f, 0.0f, 1});
	utils::DrawLine(p1, p2);

	// Do the raycast
	utils::HitInfo hitInfo{};

	if (utils::Raycast(m_Vertices, p1, p2, hitInfo))
	{
		// intersection point
		utils::SetColor(Color4f{1.0f, 1.0f, 1.0f, 1});
		const float radius{10.0f};
		utils::FillEllipse(hitInfo.intersectPoint, radius, radius);

		// the normal
		utils::SetColor(Color4f{0.0f, 1.0f, 0.0f, 1});
		utils::DrawLine(hitInfo.intersectPoint, hitInfo.intersectPoint + hitInfo.normal * -30);

		// length 1
		Vector2f rayVector{p1, p2};
		float length1{rayVector.Length() * hitInfo.lambda};
		utils::SetColor(Color4f{0, 0, 1.0f, 1.0f});
		utils::DrawLine(p1, hitInfo.intersectPoint);

		// length 2
		float length2{rayVector.Length() * (1.0f - hitInfo.lambda)};
		utils::SetColor(Color4f{1.0f, 0, 0, 1.0f});
		utils::DrawLine(hitInfo.intersectPoint, p2);

		// the reflection
		utils::SetColor(Color4f{1.0f, 1.0f, 1.0f, 1});
		Vector2f reflectedRay{-rayVector.Reflect(hitInfo.normal)};
		utils::DrawLine(hitInfo.intersectPoint, hitInfo.intersectPoint + reflectedRay * (1 - hitInfo.lambda));
	}
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
	switch (e.keysym.sym)
	{
	case SDLK_LEFT:
		std::cout << "Left arrow key pressed\n";
		break;
	}
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
	m_MousePos.x = float(e.x);
	m_MousePos.y = float(e.y);
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
