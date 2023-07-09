#pragma once

#include "../B/BSReloadShaderI.h"
#include "../N/NiBoneMatrixSetterI.h"
#include "../N/NiRefObject.h"

namespace ConsoleRE
{
	class BSShader : public NiRefObject, public NiBoneMatrixSetterI, public BSReloadShaderI
	{
	public:
		~BSShader() override;

		virtual void Unk_04() = 0;
		virtual void Unk_05() = 0;
		virtual void Unk_06();
		virtual void Unk_07();
		virtual void Unk_08() = 0;
		virtual void Unk_09() = 0;
		virtual void Unk_10();
		virtual void Unk_11();
	public:
	};
}