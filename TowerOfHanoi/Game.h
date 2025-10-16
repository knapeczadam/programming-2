// Knapecz, Adam - 1DAE11

#pragma once
#include "BaseGame.h"
#include "UI.h"
#include "Tower.h"


class Game : public BaseGame
{
public:
    explicit Game(const Window& window);
    Game(const Game& other) = delete;
    Game& operator=(const Game& other) = delete;
    Game(Game&& other) = delete;
    Game& operator=(Game&& other) = delete;
    // http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
    ~Game();

    void Update(float elapsedSec) override;
    void Draw() const override;

    // Event handling
    void ProcessKeyDownEvent(const SDL_KeyboardEvent& e) override;
    void ProcessKeyUpEvent(const SDL_KeyboardEvent& e) override;
    void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e) override;
    void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e) override;
    void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e) override;

private:
    // FUNCTIONS
    void Initialize();
    void Cleanup();
    void ClearBackground() const;

    void InitTowers();
    void DrawTowers() const;
    void UpdateTowers();
    void UpdateRelations();
    void UpdateDiskHierarchy();
    void InitDisks();
    void DrawDisks() const;
    void UpdateDisks();
    void DebugDiskHierarchy() const;
    void UpdateMouseStatus() const;

    UI m_UI;

    const static int m_NrOfTowers{3};
    Tower m_Towers[m_NrOfTowers];

    const static int m_NrOfDisks{3};
    Disk m_Disks[m_NrOfDisks];

    float m_TowerWidth;
    float m_TowerThickness;
};
