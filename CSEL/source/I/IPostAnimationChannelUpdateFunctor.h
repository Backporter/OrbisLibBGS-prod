#pragma once

namespace ConsoleRE
{
	class IPostAnimationChannelUpdateFunctor
	{
	public:
		virtual ~IPostAnimationChannelUpdateFunctor();
		
		virtual void Unk_02();
	public:
	};
	static_assert(sizeof(IPostAnimationChannelUpdateFunctor) == 0x8);
}