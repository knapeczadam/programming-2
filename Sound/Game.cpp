// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "Game.h"
#include "Texture.h"
#include "SoundEffect.h"
#include "SoundStream.h"

Game::Game(const Window& window)
    : BaseGame{window}
      , m_StreamTest{true},
      // TODO: 1. Create the DonkeyKong and Mario SoundStream objects
      m_pDonkeyKongSoundStream(new SoundStream("Sounds/DonkeyKong.mp3")),
      m_pMarioSoundStream(new SoundStream("Sounds/Mario.mp3")),
      // TODO: 4. Create the Laser and Jingles SoundEffect objects
      m_pLaserSoundEffect(new SoundEffect("Sounds/laser.ogg")),
      m_pJinglesSoundEffect(new SoundEffect("Sounds/jingles.ogg")),
      m_pPowerUpSoundEffect(new SoundEffect("Sounds/powerUp.mp3"))
{
    Initialize();
}

Game::~Game()
{
    Cleanup();
}

void Game::Initialize()
{
    m_pConsolasFont = TTF_OpenFont("Fonts/Inconsolata.ttf", 24);
    m_pSwitchText = new Texture("Press left arrow to switch", m_pConsolasFont, Color4f{1, 1, 1, 1});
    m_pStreamMenuText = new Texture("Images/StreamsMenu.png");
    m_pEffectMenuText = new Texture("Images/EffectsMenu.png");
}

void Game::Cleanup()
{
    delete m_pStreamMenuText;
    delete m_pEffectMenuText;
    delete m_pSwitchText;
    TTF_CloseFont(m_pConsolasFont);

    delete m_pDonkeyKongSoundStream;
    delete m_pMarioSoundStream;
    delete m_pLaserSoundEffect;
    delete m_pJinglesSoundEffect;
    delete m_pPowerUpSoundEffect;
}

void Game::Update(float elapsedSec)
{
}

void Game::Draw() const
{
    ClearBackground();
    DrawMenu();
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
    switch (e.keysym.sym)
    {
    case SDLK_RIGHT:
    case SDLK_LEFT:
        SwitchTest();
        break;
    default:
        // Handle user request
        if (m_StreamTest)
        {
            TestStreams(e);
        }
        else
        {
            TestEffects(e);
        }
    }
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
}

void Game::ClearBackground() const
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Game::DrawMenu() const
{
    if (m_StreamTest)
    {
        m_pStreamMenuText->Draw();
    }
    else
    {
        m_pEffectMenuText->Draw();
    }
    m_pSwitchText->Draw(Point2f(20, GetViewPort().height - 50));
}

void Game::SwitchTest()
{
    if (m_StreamTest)
    {
        // TODO: 3. User switches to the "Effect test", stop the music
        SoundStream::Stop();
    }
    else
    {
        // TODO: 6. User switches to the "Stream test", stop the effects
        SoundEffect::StopAll();
    }
    m_StreamTest = !m_StreamTest;
}

void Game::TestStreams(const SDL_KeyboardEvent& e)
{
    // TODO: 2. Handle the user requests in the "Stream test" menu 
    switch (e.keysym.sym)
    {
    case SDLK_1:
    case SDLK_KP_1:
        // Play Donkey Kong (repeated)
        if (m_pDonkeyKongSoundStream->IsLoaded()) m_pDonkeyKongSoundStream->Play(true);
        break;
    case SDLK_2:
    case SDLK_KP_2:
        // Play Mario (not repeated)
        if (m_pMarioSoundStream->IsLoaded()) m_pMarioSoundStream->Play(false);
        break;
    case SDLK_p:
        // Pause the SoundStream
        SoundStream::Pause();
        break;
    case SDLK_r:
        // Resume the SoundStream
        SoundStream::Resume();
        break;
    case SDLK_s:
        // Stop the SoundStream
        SoundStream::Stop();
        break;
    case SDLK_UP:
        {
            // Increase volume of SoundStream
            SoundStream::SetVolume(SoundStream::GetVolume() + 1);
            break;
        }
    case SDLK_DOWN:
        {
            // Decrease volume of SoundStream
            SoundStream::SetVolume(SoundStream::GetVolume() - 1);
            break;
        }
    }
}

void Game::TestEffects(const SDL_KeyboardEvent& e)
{
    // TODO: 5. Handle the user requests in the "Effect test" menu 
    switch (e.keysym.sym)
    {
    case SDLK_1:
    case SDLK_KP_1:
        // Play laser (repeated)
        m_pLaserSoundEffect->Play(-1);
        break;
    case SDLK_2:
    case SDLK_KP_2:
        // Play jingles (a number of times)
        m_pJinglesSoundEffect->Play(2);
        break;
    case SDLK_3:
    case SDLK_KP_3:
        // Play powerup (once)
        m_pPowerUpSoundEffect->Play(0);
        break;
    case SDLK_p:
        // Pause all soundEffects
        SoundEffect::PauseAll();
        break;
    case SDLK_r:
        // Resume all soundEffects
        SoundEffect::ResumeAll();
        break;
    case SDLK_s:
        // Stop  all soundEffects
        SoundEffect::StopAll();
        break;
    case SDLK_UP:
        // Increase volume of all SoundEffects
        m_pJinglesSoundEffect->SetVolume(m_pJinglesSoundEffect->GetVolume() + 1);
        m_pLaserSoundEffect->SetVolume(m_pLaserSoundEffect->GetVolume() + 1);
        break;
    case SDLK_DOWN:
        // Decrease volume of all SoundEffects
        m_pJinglesSoundEffect->SetVolume(m_pJinglesSoundEffect->GetVolume() - 1);
        m_pLaserSoundEffect->SetVolume(m_pLaserSoundEffect->GetVolume() - 1);
        break;
    }
}
