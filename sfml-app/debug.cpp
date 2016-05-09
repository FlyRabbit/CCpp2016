#include "stdafx.h"
#include "debug.h"


debug::debug()
{
}

float debug::PrintPosition(sf::Sprite mPlayer)
{
	printf("%.f %.f\n", mPlayer.getPosition().x,
		mPlayer.getPosition().y);
}

debug::~debug()
{
}
