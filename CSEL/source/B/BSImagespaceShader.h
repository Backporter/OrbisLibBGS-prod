#pragma once

#include "../B/BSShader.h"
#include "../I/ImageSpaceEffect.h"

namespace ConsoleRE
{
	class BSImagespaceShader : public BSShader, public ImageSpaceEffect
	{
	public:
		~BSImagespaceShader() override;
	public:
	};
}