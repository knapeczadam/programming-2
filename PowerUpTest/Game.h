// Knapecz, Adam - 1DAE11

#pragma once
#include "BaseGame.h"
#include "PowerUp.h"

class Game final : public BaseGame
{
public:
    explicit Game(const Window& window);
    Game(const Game& other) = delete;
    Game& operator=(const Game& other) = delete;
    Game(Game&& other) = delete;
    Game& operator=(Game&& other) = delete;
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
    Point2f m_MousePos;
    static const int m_NrPowerUps{10};
    PowerUp* m_pPowerUps[m_NrPowerUps];
    Point2f m_PowerUpsCenters[m_NrPowerUps];
    PowerUp::Type m_PowerUpTypes[m_NrPowerUps];
    bool m_PowerUpsDestroyed[m_NrPowerUps];
    float m_PowerUpRadius;
    int m_ActNrPowerUps;
    Rectf m_Destroyer;
    // FUNCTIONS
    void Initialize();
    void Cleanup();
    void ClearBackground() const;

    void ShowTestMessage() const;
    void ShowNrPowerUps() const;
    void CreatePowerUps();
    void UpdatePowerUps(float elapsedSec);
    void DrawPowerUps() const;
    void DeletePowerUps();

    void MoveDestroyer(const Point2f& newCenter);
    void DrawDestroyer() const;
    void VerifyOverlapping();
};
