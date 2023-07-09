#pragma once

#include "../G/GTexture.h"

namespace ConsoleRE
{
	class GTextureImplNode : public GTexture
	{
	public:
		GTextureImplNode();
		virtual ~GTextureImplNode();
		
		// GTexture
		virtual void Unk_02() = 0;
		virtual void Unk_03() = 0;
		virtual void Unk_04() = 0;
		virtual void Unk_05() = 0;
		virtual void Unk_06() = 0;
		virtual void Unk_07() = 0;
		virtual void Unk_08() = 0;

		// override (GTexture)
		virtual void Unk_09() override;
		virtual void Unk_10() override;
		virtual void Unk_11() override;
		virtual void Unk_12() override;
	public:
		void* UserHandle;
		bool  HandlerArrayFlag;
		
		// sure.
		union
		{
			ChangeHandler pHandler;
			void*		  pHandlerArray;
		};
	};
}