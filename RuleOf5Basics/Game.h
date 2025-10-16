// Knapecz, Adam - 1DAE11

#pragma once
#include "BaseGame.h"
#include "Container.h"
#include "Sprite.h"

#include <vector>

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

	Container CreateContainer(int nrElements, int min, int max);
	void TestContainer();
	Sprite CreateSprite(std::string path, int nrOfRows, int nrOfCols, float frameSec);
	void TestSpriteClass();
	std::vector<Sprite> m_Sprites;
	std::vector<Sprite*> m_pSprites;
};
