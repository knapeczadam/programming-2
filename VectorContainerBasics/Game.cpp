// Knapecz, Adam - 1DAE11

#include "pch.h"
#include "Game.h"
#include "Card.h"

#include <iostream>

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
	PrintInstruction();

	for (int rank{Card::m_MinRank}; rank <= Card::m_MaxRank; ++rank)
	{
		m_Cards.push_back(new Card{Card::Suit::clubs, rank});
	}
	for (int rank{Card::m_MinRank}; rank <= Card::m_MaxRank; ++rank)
	{
		m_Cards.push_back(new Card{Card::Suit::diamonds, rank});
	}
	for (int rank{Card::m_MinRank}; rank <= Card::m_MaxRank; ++rank)
	{
		m_Cards.push_back(new Card{Card::Suit::hearts, rank});
	}
	for (int rank{Card::m_MinRank}; rank <= Card::m_MaxRank; ++rank)
	{
		m_Cards.push_back(new Card{Card::Suit::spades, rank});
	}
}

void Game::Cleanup()
{
	for (int idx{0}; idx < m_Cards.size(); ++idx)
	{
		delete m_Cards[idx];
	}
}

void Game::Update(float elapsedSec)
{
	// Check keyboard state
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	if (pStates[SDL_SCANCODE_RIGHT])
	{
		std::cout << "Right arrow key is down\n";
	}
	if (pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	{
		std::cout << "Left and up arrow keys are down\n";
	}
}

void Game::Draw() const
{
	ClearBackground();
	DrawCards();
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
	switch (e.keysym.sym)
	{
	case SDLK_s:
		ShuffleCards();
		break;
	case SDLK_h:
		PrintInstruction();
		break;
	case SDLK_UP:
		IncrementElements();
		PrintElements();
		break;
	case SDLK_DOWN:
		DecrementElements();
		PrintElements();
		break;
	case SDLK_EQUALS:
		if (e.keysym.mod & KMOD_SHIFT)
		{
			const int randNum{std::rand() % 31};
			m_nums.push_back(randNum);
			PrintElements();
		}
		break;
	case SDLK_MINUS:
		if (!m_nums.empty())
		{
			m_nums.pop_back();
			PrintElements();
		}
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

void Game::PrintInstruction() const
{
	std::cout << "+: Add a number at the end of the vector" << std::endl;
	std::cout << "-: Remove last number from the vector" << std::endl;
	std::cout << "^: Increment all numbers in the vector" << std::endl;
	std::cout << "v: Decrement all numbers in the vector" << std::endl;
	std::cout << "h: Show menu" << std::endl;
}

void Game::PrintElements()
{
	// for (int idx{0}; idx < m_nums.size(); ++idx)
	// {
	// 	std::cout << m_nums[idx] << ' ';
	// }
	// std::cout << std::endl;

	if (m_nums.size())
	{
		for (const int& e : m_nums)
		{
			std::cout << e << ' ';
		}
		std::cout << std::endl;
	}
}

void Game::IncrementElements()
{
	for (int idx{0}; idx < m_nums.size(); ++idx)
	{
		++m_nums[idx];
	}
}

void Game::DecrementElements()
{
	for (int idx{0}; idx < m_nums.size(); ++idx)
	{
		--m_nums[idx];
	}
}

void Game::DrawCards() const
{
	const float scale{0.5f};
	float left{};
	float bottom{GetViewPort().height};
	const int rows{4};
	const int cols{13};
	for (int row{0}; row < rows; row++)
	{
		for (int col{0}; col < cols; ++col)
		{
			Card* card = m_Cards[row * cols + col];
			Rectf dst{};
			dst.width = card->GetWidth() * scale;
			dst.height = card->GetHeight() * scale;
			dst.left = dst.width / 2 * col;
			dst.bottom = bottom - dst.height * (row + 1);
			card->Draw(dst);
		}
		left = 0;
	}
}

void Game::ShuffleCards()
{
	const int numSuite{4};
	const int nShuffle{5};
	const int maxCardNum{numSuite * Card::m_MaxRank};
	for (int i{0}; i < nShuffle; ++i)
	{
		int a{std::rand() % maxCardNum};
		int b{std::rand() % maxCardNum};
		while (a == b)
		{
			a = std::rand() % maxCardNum;
		}
		Card* temp{m_Cards[a]};
		m_Cards[a] = m_Cards[b];
		m_Cards[b] = temp;
	}
}
