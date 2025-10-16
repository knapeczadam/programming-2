// Knapecz, Adam - 1DAE11

#include "pch.h"
#include "Game.h"
#include "Smiley.h"

#include "utils.h"

Game::Game(const Window& window)
	: BaseGame{window}
	  , m_BoundingRect{}
	  , m_SafeRect{}
{
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	Smiley::LoadTexture();
	CreateSmileys();

	m_BoundingRect.width = GetViewPort().width;
	m_BoundingRect.height = GetViewPort().height;

	const float border{30.0f};
	m_SafeRect.width = m_BoundingRect.width - 2 * border;
	m_SafeRect.height = m_BoundingRect.height - 2 * border;
	m_SafeRect.left = border;
	m_SafeRect.bottom = border;
}

void Game::Cleanup()
{
	DeleteSmileys();
}

void Game::Update(float elapsedSec)
{
	UpdateSmileys(elapsedSec);
	DetermineHighestSmiley();
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
	DrawSafeArea();
	DrawSmileys();
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
	switch (e.keysym.sym)
	{
	case SDLK_DOWN:
		DecreaseSmileysSpeed();
		break;
	case SDLK_UP:
		IncreaseSmileysSpeed();
		break;
	case SDLK_DELETE:
		DeleteSleepers();
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
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
		HitTestSmileys(e);
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

void Game::ClearBackground() const
{
	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Game::CreateSmileys()
{
	const int nrSmileys{10};
	const float emptySpace{GetViewPort().width - nrSmileys * Smiley::GetSmileyWidth()};
	const float offset{emptySpace / (nrSmileys + 1)};
	const float bottom{GetViewPort().height / 2 - Smiley::GetSmileyHeight() / 2};
	float left{offset};
	for (int idx{0}; idx < nrSmileys; ++idx)
	{
		Smiley* smiley = new Smiley{Point2f{left, bottom}};
		m_pSmileys.push_back(smiley);
		left += Smiley::GetSmileyWidth();
		left += offset;
	}
}

void Game::DeleteSmileys()
{
	for (size_t idx{0}; idx < m_pSmileys.size(); ++idx)
	{
		if (m_pSmileys[idx] == nullptr)
		{
			continue;
		}
		delete m_pSmileys[idx];
	}
}

void Game::DrawSmileys() const
{
	for (const Smiley* smiley : m_pSmileys)
	{
		if (smiley == nullptr)
		{
			continue;
		}
		smiley->Draw();
	}
}

void Game::UpdateSmileys(float elapsedSec)
{
	for (Smiley* smiley : m_pSmileys)
	{
		if (smiley == nullptr)
		{
			continue;
		}
		smiley->Update(elapsedSec, m_BoundingRect, m_SafeRect);
	}
}

void Game::DrawSafeArea() const
{
	utils::DrawRect(m_SafeRect, 2.0f);
}

void Game::HitTestSmileys(const SDL_MouseButtonEvent& e)
{
	for (Smiley* smiley : m_pSmileys)
	{
		if (smiley == nullptr)
		{
			continue;
		}
		smiley->HitTest(Point2f{float(e.x), float(e.y)});
	}
}

void Game::DetermineHighestSmiley()
{
	int index{-1};
	float highestPos{-1};
	for (size_t idx{0}; idx < m_pSmileys.size(); ++idx)
	{
		Smiley* smiley = m_pSmileys[idx];
		if (smiley == nullptr)
		{
			continue;
		}
		if (smiley->IsSleeping())
		{
			continue;
		}
		smiley->SetHighest(false);
		if (smiley->GetPosition().y > highestPos)
		{
			highestPos = smiley->GetPosition().y;
			index = idx;
		}
	}
	if (index == -1)
	{
		return;
	}
	if (m_pSmileys[index] == nullptr)
	{
		return;
	}
	m_pSmileys[index]->SetHighest(true);
}

void Game::IncreaseSmileysSpeed()
{
	for (Smiley* smiley : m_pSmileys)
	{
		if (smiley == nullptr)
		{
			continue;
		}
		smiley->IncreaseSpeed();
	}
}

void Game::DecreaseSmileysSpeed()
{
	for (Smiley* smiley : m_pSmileys)
	{
		if (smiley == nullptr)
		{
			continue;
		}
		smiley->DecreaseSpeed();
	}
}

void Game::DeleteSleepers()
{
	for (size_t idx{0}; idx < m_pSmileys.size(); ++idx)
	{
		const Smiley* smiley{m_pSmileys[idx]};
		if (smiley == nullptr)
		{
			continue;
		}
		if (smiley->IsSleeping())
		{
			delete smiley;
			m_pSmileys[idx] = nullptr;
		}
	}
}
