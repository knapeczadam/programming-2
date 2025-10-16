// Knapecz, Adam - 1DAE11
#pragma once
#include "GameObject.h"
#include <string>


class Enemy : public GameObject
{
public:
	Enemy( );
	~Enemy( ) override;

	std::string ToString( ) const override;

private:
	static int m_InstanceCounter;
};


 
