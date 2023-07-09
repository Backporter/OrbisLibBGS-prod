#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	class BSAudio
	{
	public:
		BSAudio();
		virtual ~BSAudio();
		
		virtual bool	 Unk_02();
		virtual void	 Unk_03();

		virtual void*	 Unk_04() = 0;
		virtual void	 Unk_05() = 0;
		virtual void*	 Unk_06() = 0;

		virtual void	 Unk_07();
		virtual void	 Unk_08();

		virtual uint32_t Unk_09();
		virtual void	 Unk_0A();
		virtual void*	 Unk_0B();
	public:
		bool Unk08;
	};
}