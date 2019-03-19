#pragma once

#include "ggl.h"
#include "sprite.h"

class Ground: public Sprite
{
public:
	Ground();

	void Init();

	void Draw() override;
};

