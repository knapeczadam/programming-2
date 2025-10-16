// Knapecz, Adam - 1DAE11
#pragma once
#include "Texture.h"
#include "BaseGame.h"

class SoundEffect;
class SoundStream;

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

    //Which test series
    bool m_StreamTest;

    // SoundStream and SoundEffect objects.

    // Textures and fonts for the menu
    Texture* m_pStreamMenuText;
    Texture* m_pEffectMenuText;
    Texture* m_pSwitchText;
    TTF_Font* m_pConsolasFont;
    SoundStream* m_pDonkeyKongSoundStream;
    SoundStream* m_pMarioSoundStream;
    SoundEffect* m_pLaserSoundEffect;
    SoundEffect* m_pJinglesSoundEffect;
    SoundEffect* m_pPowerUpSoundEffect;


    // FUNCTIONS
    void Initialize();
    void Cleanup();
    void ClearBackground() const;

    void DrawMenu() const;
    void SwitchTest();
    void TestStreams(const SDL_KeyboardEvent& e);
    void TestEffects(const SDL_KeyboardEvent& e);
};
