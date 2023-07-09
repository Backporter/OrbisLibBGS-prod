#pragma once

#include "../G/GTextureImplNode.h"

namespace ConsoleRE
{
	class GTextureOrbisImplYUV : public GTextureImplNode
	{
	public:
		GTextureOrbisImplYUV();
		virtual ~GTextureOrbisImplYUV();

		// override (GTextureImplNode)
		virtual void Unk_02() override;
		virtual void Unk_03() override;
		virtual void Unk_04() override;
		virtual void Unk_05() override;
		virtual void Unk_06() override;
		virtual void Unk_07() override;
		virtual void Unk_08() override;

		// add
		virtual void Unk_13();
		virtual void Unk_14();
		virtual void Unk_15();
		virtual void Unk_16();
		virtual void Unk_17();
	private:
	};
	static_assert(sizeof(GTextureOrbisImplYUV) != 0, "class size mismatch");
}