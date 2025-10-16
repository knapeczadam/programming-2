// Knapecz, Adam - 1DAE11

#include "pch.h"
#include "Card.h"
#include "Texture.h"
#include "Matrix2x3.h"

#include <iostream>

const int Card::m_MinRank{1};
const int Card::m_MaxRank{13};


Card::Card(Suit suit, int rank)
	: m_Width{0}
	  , m_Height{0}
	  , m_pTexture{nullptr}
	  , m_Suit{suit}
	  , m_Rank{rank}
	  , m_RotationalSpeed{0}
	  , m_Angle{0}
{
	m_pTexture = new Texture{GetImagePath(suit, rank)};
	m_Width = m_pTexture->GetWidth();
	m_Height = m_pTexture->GetHeight();
}

Card::Card(Suit suit, int rank, float angle, const Circlef& circle)
	: m_Width{0}
	  , m_Height{0}
	  , m_pTexture{nullptr}
	  , m_Suit{suit}
	  , m_Rank{rank}
	  , m_RotationalSpeed{10.0f}
	  , m_Angle{angle}
	  , m_Circle{circle}
{
	m_pTexture = new Texture{GetImagePath(suit, rank)};
	m_Width = m_pTexture->GetWidth();
	m_Height = m_pTexture->GetHeight();
}

Card::~Card()
{
	delete m_pTexture;
}

void Card::Draw(const Rectf& destRect) const
{
	m_pTexture->Draw(destRect);
}

void Card::Draw() const
{
	const float scale{ 0.5f };
	Rectf dst;
	dst.width = m_Width * scale;
	dst.height = m_Height * scale;
	glPushMatrix();
		glTranslatef(m_Circle.center.x, m_Circle.center.y, 0);
		glRotatef(m_Angle, 0, 0, 1);
		glTranslatef(m_Circle.radius,0, 0);
		m_pTexture->Draw(dst);
	glPopMatrix();
}

void Card::Update(float elapsedSec)
{
	m_Angle += m_RotationalSpeed * elapsedSec;
	m_RotationMatrix.SetAsRotate(m_Angle);
}

float Card::GetWidth() const
{
	return m_Width;
}

float Card::GetHeight() const
{
	return m_Height;
}

std::string Card::GetImagePath(Suit suit, int rank) const
{
	return "Images/Cards/" + std::to_string((int)suit * 100 + rank) + ".png";;
}
