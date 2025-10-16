// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "Game.h"
#include "utils.h"
#include "Texture.h"

Game::Game( const Window& window ) 
	: BaseGame{ window }
	, m_Vertices{ }
	, m_Angle{ }
	, m_Scale{ 1.f }
	, m_Translation{ }
	, m_TranslationMatrix{ }
	, m_RotatingMatrix{ }
	, m_ScaleMatrix{ }
	, m_IsClicked{ }
	, m_pTexture{ new Texture{ "images/diamond.png"}}
{
	Initialize();
	InitDiamond();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{
	TRSOnKey(elapsedSec);
	InitializeMatrix();
}

void Game::Draw( ) const
{
	ClearBackground( );

	if (m_IsClicked)
	{
		utils::SetColor(Color4f{ 1.f, 0.f, 0.f, 1.f });
	}
	else if (!m_IsClicked)
	{
		utils::SetColor(Color4f{ 0.f, 0.f, 1.f, 1.f });
	}
	// utils::DrawPolygon(m_Vertices);
	DrawDiamondTexture();
	utils::DrawPolygon(m_TransVertices, 2.f);
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
	CheckIfPressed(e);
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.66f, 0.66f, 0.66f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::InitDiamond()
{
	m_Vertices.push_back(Point2f{ 0.f, 24.f });
	m_Vertices.push_back(Point2f{ 24.f, 48.f });
	m_Vertices.push_back(Point2f{ 48.f, 24.f });
	m_Vertices.push_back(Point2f{ 24.f, 0.f });
}

void Game::InitializeMatrix()
{
	m_TranslationMatrix.SetAsTranslate(m_Translation);
	m_RotatingMatrix = Matrix2x3::CreateRotationMatrix(m_Angle);
	m_ScaleMatrix.SetAsScale(m_Scale);
	m_CenterMatrix.SetAsTranslate(Vector2f(-24.f, -24.f));

	Matrix2x3 matrixInWorld{ m_TranslationMatrix * m_RotatingMatrix * m_ScaleMatrix * m_CenterMatrix };
	m_TransVertices = matrixInWorld.Transform(m_Vertices);
}

void Game::TRSOnKey(float elapsedSec)
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	if (pStates[SDL_SCANCODE_A])
	{
		m_Angle -= 60.f * elapsedSec;
	}
	else if (pStates[SDL_SCANCODE_D])
	{
		m_Angle += 60.f * elapsedSec;
	}

	if (pStates[SDL_SCANCODE_W])
	{
		m_Scale *= 1 + 3 * elapsedSec;
	}
	else if (pStates[SDL_SCANCODE_S])
	{
		m_Scale /= 1 + 3 * elapsedSec;
	}

	if (pStates[SDL_SCANCODE_UP])
	{
		m_Translation.y += 120.f * elapsedSec;
	}
	else if (pStates[SDL_SCANCODE_RIGHT])
	{
		m_Translation.x += 120.f * elapsedSec;
	}
	else if (pStates[SDL_SCANCODE_DOWN])
	{
		m_Translation.y -= 120.f * elapsedSec;
	}
	else if (pStates[SDL_SCANCODE_LEFT])
	{
		m_Translation.x -= 120.f * elapsedSec;
	}
}

void Game::CheckIfPressed(const SDL_MouseButtonEvent& e)
{
	Point2f mousePos{ float(e.x), float(e.y) };
	if (utils::IsPointInPolygon(mousePos, m_TransVertices) && !m_IsClicked)
	{
		m_IsClicked = true;
	}
	else
	{
		m_IsClicked = false;
	}
}

void Game::DrawDiamondTexture() const
{
	glPushMatrix();
	glTranslatef(m_Translation.x, m_Translation.y, 0);
	glRotatef(m_Angle, 0.f, 0.f, 1.f);
	glScalef(m_Scale, m_Scale, 1.f);
	glTranslatef(-m_pTexture->GetWidth() / 2.f, -m_pTexture->GetHeight() / 2.f, 0.f);
	m_pTexture->Draw();
	glPopMatrix();
}


