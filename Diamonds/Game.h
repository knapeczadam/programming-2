// Knapecz, Adam - 1DAE11

#pragma once
#include "BaseGame.h"
#include "Vector2f.h"
#include <vector>

class Diamond;

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
	
	void UpdateTransformation();
	void OnMouseDown(const Point2f& pos);
	void ResetDiamonds();
	void DrawDiamonds() const;
	void TransformDiamonds();
	void InitDiamonds();
	void DeleteDiamonds();
	void SetRotation(float elapsedSec, bool clockwise);
	void SetScaling(float elapsedSec, bool downScaling);
	void SetHorizontalTranslation(float elapsedSec, bool left);
	void SetVerticalTranslation(float elapsedSec, bool down);
	Point2f GetRandomPosition() const;

	const int m_NrOfDiamonds;
	std::vector<Diamond*> m_Diamonds;
	
	Vector2f m_Translation;
	float m_ScalingFactor;
	float m_Angle;
};
