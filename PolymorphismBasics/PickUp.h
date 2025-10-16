// Knapecz, Adam - 1DAE11
#pragma once
#include "GameObject.h"
#include <string>


class PickUp : public GameObject
{
public:
	PickUp( );
	~PickUp( ) override;

	std::string ToString( ) const override;

private:
	static int m_InstanceCounter;
};
