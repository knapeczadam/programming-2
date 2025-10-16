// Knapecz, Adam - 1DAE11

#pragma once
#include "BaseGame.h"
#include <vector>

class Smiley;

class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:

	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;

	void CreateSmileys();
	void DeleteSmileys();
	void DrawSmileys() const;
	void UpdateSmileys(float elapsedSec);
	void DrawSafeArea() const;
	void HitTestSmileys(const SDL_MouseButtonEvent& e);
	void DetermineHighestSmiley();
	void IncreaseSmileysSpeed();
	void DecreaseSmileysSpeed();
	void DeleteSleepers();

	std::vector<Smiley*> m_pSmileys;
	Rectf m_BoundingRect;
	Rectf m_SafeRect;
};

