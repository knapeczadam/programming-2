// Knapecz, Adam - 1DAE11

#include "pch.h"
#include "Game.h"
#include <iostream>

#include "Matrix2x3.h"
#include "Texture.h"
#include "utils.h"

Game::Game(const Window& window)
    : BaseGame{window}
      , m_Vertices{}
      , m_TransformedVertices{}
      , m_DiamondCenter{}
      , m_Size{48.f}
      , m_Angle{}
      , m_ScalingFactor{1.0f}
      , m_Translation{}
      , m_IsSelected{}
      , m_pDiamondTexture{new Texture{"images/Diamond.png"}}
      , m_TransformationMatrix{}
      , m_RotationMatrix{}
      , m_ScalingMatrix{}
      , m_OffsetMatrix{}
{
    Initialize();
}

Game::~Game()
{
    Cleanup();
}

void Game::Initialize()
{
    m_DiamondCenter = Point2f{m_Size / 2, m_Size / 2};

    const Point2f A{m_Size / 2, 0};
    const Point2f B{m_Size, m_Size / 2};
    const Point2f C{m_Size / 2, m_Size};
    const Point2f D{0, m_Size / 2};

    m_Vertices.push_back(A);
    m_Vertices.push_back(B);
    m_Vertices.push_back(C);
    m_Vertices.push_back(D);

    m_OffsetMatrix.SetAsTranslate(-m_Size / 2, -m_Size / 2);

    PrintInfo();
}

void Game::Cleanup()
{
    delete m_pDiamondTexture;
}

void Game::Update(float elapsedSec)
{
    // Check keyboard state
    const Uint8* pStates = SDL_GetKeyboardState(nullptr);
    if (pStates[SDL_SCANCODE_A])
    {
        m_Angle += 60 * elapsedSec;
        //RotateDiamond();
    }
    if (pStates[SDL_SCANCODE_D])
    {
        m_Angle -= 60 * elapsedSec;
        //RotateDiamond();
    }
    if (pStates[SDL_SCANCODE_W])
    {
        m_ScalingFactor *= 1 + 3 * elapsedSec;
        //ScaleDiamond();
    }
    if (pStates[SDL_SCANCODE_S])
    {
        m_ScalingFactor /= 1 + 3 * elapsedSec;
        //ScaleDiamond();
    }
    if (pStates[SDL_SCANCODE_UP])
    {
        m_Translation.y += 120 * elapsedSec;
        //TransformDiamond();
    }
    if (pStates[SDL_SCANCODE_DOWN])
    {
        m_Translation.y -= 120 * elapsedSec;
        //TransformDiamond();
    }
    if (pStates[SDL_SCANCODE_LEFT])
    {
        m_Translation.x -= 120 * elapsedSec;
        //TransformDiamond();
    }
    if (pStates[SDL_SCANCODE_RIGHT])
    {
        m_Translation.x += 120 * elapsedSec;
        //TransformDiamond();
    }
    TransformDiamond();
}

void Game::Draw() const
{
    ClearBackground();
    DrawDiamondTexture();
    if (m_IsSelected)
    {
        utils::SetColor(Color4f{1, 0, 0, 1.0f});
    }
    else
    {
        utils::SetColor(Color4f{0, 0, 1, 1.0f});
    }
    utils::DrawPolygon(m_TransformedVertices, 2.0f);
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
        OnMouseDown(float(e.x), float(e.y));
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

void Game::PrintInfo() const
{
    std::cout << "a: Rotate ccw" << std::endl;
    std::cout << "d: Rotate cw" << std::endl;
    std::cout << "w: Zoom in" << std::endl;
    std::cout << "s: Zoom out" << std::endl;
    std::cout << "Arrows: Translate" << std::endl;
}

void Game::RotateDiamond()
{
    Matrix2x3 T1{Matrix2x3::CreateTranslationMatrix(-m_DiamondCenter.x, -m_DiamondCenter.y)};
    Matrix2x3 R1{Matrix2x3::CreateRotationMatrix(m_Angle)};
    Matrix2x3 T2{Matrix2x3::CreateTranslationMatrix(m_DiamondCenter.x, m_DiamondCenter.y)};
    Matrix2x3 I{Matrix2x3::CreateIdentityMatrix()};
    for (Point2f& vertex : m_Vertices)
    {
        I.orig = Vector2f{vertex.x, vertex.y};
        I = T2 * R1 * T1 * I;
        vertex.x = I.orig.x;
        vertex.y = I.orig.y;
    }
}

void Game::ScaleDiamond()
{
    Matrix2x3 T1{Matrix2x3::CreateTranslationMatrix(-m_DiamondCenter.x, -m_DiamondCenter.y)};
    Matrix2x3 S1{Matrix2x3::CreateScalingMatrix(m_ScalingFactor)};
    Matrix2x3 T2{Matrix2x3::CreateTranslationMatrix(m_DiamondCenter.x, m_DiamondCenter.y)};
    Matrix2x3 I{Matrix2x3::CreateIdentityMatrix()};
    for (Point2f& vertex : m_Vertices)
    {
        I.orig = Vector2f{vertex.x, vertex.y};
        I = T2 * S1 * T1 * I;
        vertex.x = I.orig.x;
        vertex.y = I.orig.y;
    }
}

void Game::TranslateDiamond()
{
    m_DiamondCenter.x += m_Translation.ToPoint2f().x;
    m_DiamondCenter.y += m_Translation.ToPoint2f().y;

    Matrix2x3 T1{Matrix2x3::CreateTranslationMatrix(m_Translation)};
    Matrix2x3 I{Matrix2x3::CreateIdentityMatrix()};
    for (Point2f& vertex : m_Vertices)
    {
        I.orig = Vector2f{vertex.x, vertex.y};
        I = T1 * I;
        vertex.x = I.orig.x;
        vertex.y = I.orig.y;
    }
}

void Game::ResetTranslationFactors()
{
    m_Angle = 0;
    m_ScalingFactor = 1.0f;
    m_Translation = Vector2f{};
}

void Game::TransformDiamond()
{
    // TRS + offset
    m_TransformationMatrix.SetAsTranslate(m_Translation);
    m_RotationMatrix.SetAsRotate(m_Angle);
    m_ScalingMatrix.SetAsScale(m_ScalingFactor);
    Matrix2x3 TRS{m_TransformationMatrix * m_RotationMatrix * m_ScalingMatrix * m_OffsetMatrix};
    m_TransformedVertices = TRS.Transform(m_Vertices);
}

void Game::OnMouseDown(float x, float y)
{
    if (utils::IsPointInPolygon(Point2f{x, y}, m_TransformedVertices))
    {
        m_IsSelected = !m_IsSelected;
    }
}

void Game::DrawDiamondTexture() const
{
    glPushMatrix();
    glTranslatef(m_Translation.x, m_Translation.y, 0.0f);
    glRotatef(m_Angle, 0.0f, 0.0f, 1.0f);
    glScalef(m_ScalingFactor, m_ScalingFactor, 1.0f);
    glTranslatef(-m_pDiamondTexture->GetWidth() / 2, -m_pDiamondTexture->GetHeight() / 2, 0.0f);
    m_pDiamondTexture->Draw();
    glPopMatrix();
}

