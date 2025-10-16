// Knapecz, Adam - 1DAE11
#pragma once
#include "BaseGame.h"
#include "Vector2f.h"
#include <vector>
#include "Matrix2x3.h"

class Texture;

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

	std::vector<Point2f> m_Vertices;
	std::vector<Point2f> m_TransVertices;
	float m_Angle;
	float m_Scale;
	Vector2f m_Translation;
	
	Matrix2x3 m_TranslationMatrix;
	Matrix2x3 m_RotatingMatrix;
	Matrix2x3 m_ScaleMatrix;
	Matrix2x3 m_CenterMatrix;

	bool m_IsClicked;
	
	Texture* m_pTexture;

	void InitDiamond();
	void InitializeMatrix();
	void TRSOnKey(float elapsedSec);
	void CheckIfPressed(const SDL_MouseButtonEvent& e);
	void DrawDiamondTexture() const;
};