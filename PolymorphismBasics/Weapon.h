// Knapecz, Adam - 1DAE11
#pragma once
#include "GameObject.h"
#include <string>


class Weapon : public GameObject
{
public:
	Weapon( );
	~Weapon( ) override; 

	std::string ToString( ) const override;

private:
	static int m_InstanceCounter;
};

 
