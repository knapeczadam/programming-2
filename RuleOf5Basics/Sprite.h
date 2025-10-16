// Knapecz, Adam - 1DAE11
#pragma once
#include <string>

class Texture;

class Sprite final
{
public:
	explicit Sprite( const std::string& filename, int nrCols = 1, int nrRows = 1, float frameSec = 0 );
	~Sprite( );
	Sprite(const Sprite& other); // copy constructor
	Sprite(Sprite&& other) noexcept; // move constructor
	Sprite& operator=(const Sprite& other); // copy assignment
	Sprite& operator=(Sprite&& other) noexcept; // move assignment
	void Update( float elapsedSec );
	void Draw( const Point2f& pos, float scale = 1.0f );

	float GetFrameWidth( );
	float GetFrameHeight( );

private:
	Texture *m_pTexture;
	int m_Cols;
	int m_Rows;
	float m_FrameSec;
	float m_AccuSec;
	int   m_ActFrame;
	std::string m_Path;

};


