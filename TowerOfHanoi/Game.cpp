// Knapecz, Adam - 1DAE11

#include "pch.h"
#include "Game.h"

#include "ColorManager.h"
#include "MouseManager.h"

#include <iostream>

#include "ScoreManager.h"


Game::Game(const Window& window)
    : BaseGame{window}
      , m_TowerWidth{}
      , m_TowerThickness{}
{
    Initialize();
}

Game::~Game()
{
    Cleanup();
}

void Game::Initialize()
{
    m_UI.SetViewPort(GetViewPort());
    InitTowers();
    InitDisks();
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
    UpdateDisks();
    UpdateTowers();
    UpdateRelations();
    UpdateDiskHierarchy();
    UpdateMouseStatus();
}

void Game::Draw() const
{
    ClearBackground();
    m_UI.Draw();
    DrawTowers();
    DrawDisks();
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
    //std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
    switch (e.keysym.sym)
    {
    case SDLK_i:
        DebugDiskHierarchy();
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
    MouseManager::SetMousePos(Point2f{float(e.x), float(e.y)});
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
    //std::cout << "MOUSEBUTTONDOWN event: ";
    switch (e.button)
    {
    case SDL_BUTTON_LEFT:
        MouseManager::LMBDown();
        break;
    }
}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
    // std::cout << "MOUSEBUTTONUP event: ";
    switch (e.button)
    {
    case SDL_BUTTON_LEFT:
        MouseManager::LMBUp();
        break;
    }
}

void Game::ClearBackground() const
{
    glClearColor(ColorManager::s_White.r, ColorManager::s_White.g, ColorManager::s_White.b, ColorManager::s_White.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Game::InitTowers()
{
    const float border{20.0f};
    const float spacing{10.0f};

    m_TowerWidth = (GetViewPort().width - 2 * border - 2 * spacing) / m_NrOfTowers;
    const float towerHeight{GetViewPort().height / 2};
    m_TowerThickness = 25.0f;

    for (int idx{}; idx < m_NrOfTowers; ++idx)
    {
        m_Towers[idx].SetWidth(m_TowerWidth);
        m_Towers[idx].SetHeight(towerHeight);
        m_Towers[idx].SetThickness(m_TowerThickness);

        Point2f pos;
        pos.x = border + idx * (m_TowerWidth + spacing);
        pos.y = border;
        m_Towers[idx].SetPos(pos);

        // ID
        m_Towers[idx].SetID(idx);
        m_Towers[0].AddDisk(idx, m_Disks, m_NrOfDisks);
    }
}

void Game::DrawTowers() const
{
    for (int idx{}; idx < m_NrOfTowers; ++idx)
    {
        m_Towers[idx].Draw();
    }
}


void Game::UpdateTowers()
{
    for (int idx{}; idx < m_NrOfTowers; ++idx)
    {
        m_Towers[idx].Update(m_Disks, m_NrOfDisks);
    }
}

void Game::UpdateRelations()
{
    for (int idx{}; idx < m_NrOfTowers; ++idx)
    {
        for (int diskID : m_Towers[idx].GetDiskIDs())
        {
            if (m_Disks[diskID].GetTowerID() != idx)
            {
                // Set Position
                Point2f pos{m_Towers[m_Disks[diskID].GetTowerID()].GetPos()};

                pos.x += m_TowerWidth / 2 - m_Disks[diskID].GetWidth() / 2;
                int nrOfDisks{m_Towers[m_Disks[diskID].GetTowerID()].CountDisks()};
                pos.y += m_TowerThickness * (nrOfDisks + 1);
                m_Disks[diskID].SetPos(pos);

                // Update Tower's list
                m_Towers[idx].RemoveDisk(m_Disks, m_NrOfDisks);
                m_Towers[m_Disks[diskID].GetTowerID()].AddDisk(diskID, m_Disks, m_NrOfDisks);

                ScoreManager::IncreaseScore();
            }
        }
    }
}

void Game::UpdateDiskHierarchy()
{
}

void Game::InitDisks()
{
    const float offset{20.0f};
    for (int idx{}; idx < m_NrOfDisks; ++idx)
    {
        Point2f pos{m_Towers[0].GetPos()};
        m_Disks[idx].SetWidth(m_TowerWidth - 2 * offset * (idx + 1));
        m_Disks[idx].SetHeight(m_TowerThickness);
        pos.x += offset * (idx + 1);
        pos.y += m_TowerThickness * (idx + 1);
        m_Disks[idx].SetPos(pos);

        m_Disks[idx].SetID(idx);
        m_Disks[idx].SetTopDiskID(idx + 1);
        m_Disks[idx].SetNewTowerID(0);
    }

    // Set top disk as free disk
    m_Disks[m_NrOfDisks - 1].SetTopDiskID(Disk::s_FreeDiskID);

    // COLORS
    m_Disks[0].SetColor(ColorManager::s_Red);
    m_Disks[1].SetColor(ColorManager::s_Green);
    m_Disks[2].SetColor(ColorManager::s_Yellow);
}

void Game::DrawDisks() const
{
    for (int idx{}; idx < m_NrOfDisks; ++idx)
    {
        m_Disks[idx].Draw();
    }
}

void Game::UpdateDisks()
{
    for (int idx{0}; idx < m_NrOfDisks; ++idx)
    {
        m_Disks[idx].Update();
    }
}

void Game::DebugDiskHierarchy() const
{
    std::cout << "Disk Hierarchy: " << std::endl;
    for (int idx{}; idx < m_NrOfTowers; ++idx)
    {
        std::cout << "Tower " << idx << ": ";
        for (int diskID : m_Towers[idx].GetDiskIDs())
        {
            std::cout << diskID << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Disk TowerID: " << std::endl;
    for (int idx{}; idx < m_NrOfDisks; ++idx)
    {
        std::cout << "Disk " << idx << ": " << m_Disks[idx].GetTowerID() << std::endl;
    }

    std::cout << "Mouse is in use:" << MouseManager::IsInUse() << std::endl;
}

void Game::UpdateMouseStatus() const
{
    bool mouseIsInUse{false};
    for (int idx{}; idx < m_NrOfDisks; ++idx)
    {
        if (m_Disks[idx].IsSelected())
        {
            mouseIsInUse = true;
            break;
        }
    }
    if (not mouseIsInUse)
    {
        MouseManager::Release();
    }
}
