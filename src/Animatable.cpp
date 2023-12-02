#include "Animatable.h"

Animatable::~Animatable()
{
	if (animationTileset != nullptr)
		delete animationTileset;
}