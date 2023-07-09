#pragma once
#include <stdint.h>

namespace ConsoleRE
{
	class ActorPackageData
	{
	public:
		ActorPackageData();
		virtual ~ActorPackageData();
	public:
		virtual void	 Unk_02() = 0;	// pure 
		virtual int32_t	 Unk_03();		// return 0;
		virtual void	 Unk_04();		// return;
		virtual void	 Unk_05();		// return;
		virtual void	 Unk_06() = 0;	// pure
		virtual void	 Unk_07() = 0;	// pure
		virtual void	 Unk_08();		// return
		virtual void	 Unk_09();		// return;
	public:
		//
	};
}