// Knapecz, Adam - 1DAE11
// The query type (const) methods are not indicated as such, 
// but we expect you to indicate these using const.

// -- Smiley.h file --
#pragma once

#include "Vector2f.h"


class  Texture; // class forward declaration

enum class State
{
	happy,
	neutral,
	scared,
	sleeping
};

class Smiley
{
public:
	explicit Smiley( const Point2f& position );
	~Smiley( );

	void Draw( ) const;
	void Update( float elapsedSec, const Rectf& boundingRect, const Rectf& safeRect );
	void HitTest( const Point2f& pos );
	bool IsSleeping( ) const;
	Point2f GetPosition( ) const;
	void SetHighest( bool isHighest );
	void IncreaseSpeed( );
	void DecreaseSpeed( );

	static void LoadTexture();
	static void DeleteTexture();
	static float GetSmileyWidth();
	static float GetSmileyHeight();

private:
	// DATA MEMBERS
	static Texture* m_pSmileyTexture;
	static int m_InstanceCounter;
	static int m_NrSmileys;

	Point2f m_Position;
	Vector2f m_Velocity;
	bool m_IsHighest;
	bool m_IsSleeping;
	bool m_IsInSafeArea;
	State m_State;


	// FUNCTIONS
	bool IsInSafeArea( const Rectf& safeRect );
};



