// Knapecz, Adam - 1DAE11
#pragma once
#include "Level.h"
#include "PowerUpManager.h"
#include "Avatar.h"
#include "BaseGame.h"

class HUD;
class Camera;

class Game : public BaseGame
{
public:
    explicit Game(const Window& window);
    Game(const Game& other) = delete;
    Game& operator=(const Game& other) = delete;
    Game(Game&& other) = delete;
    Game& operator=(Game&& other) = delete;
    ~Game();

    void Update(float elapsedSec);
    void Draw() const;

    // Event handling
    void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);
    void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);
    void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e);
    void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e);
    void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e);

private:
    // DATA MEMBERS
    void InitCamera();

    Level m_Level;
    PowerUpManager m_PowerUpManager;
    Avatar m_Avatar;
    Camera* m_pCamera;
    Texture* m_pTestTexture;
    HUD* m_pHUD;
    bool m_EndReached;


    // FUNCTIONS
    void Initialize();
    void Cleanup();
    void ClearBackground() const;
    void ShowTestMessage() const;
    void AddPowerUps();
    void DoCollisionTests();
};
