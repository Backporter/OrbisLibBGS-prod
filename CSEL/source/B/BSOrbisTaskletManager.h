#pragma once
#include <stdint.h>

namespace ConsoleRE
{
	class BSOrbisTaskletManager
	{
	public:
		virtual ~BSOrbisTaskletManager();
	private:
	};
	static_assert(sizeof(BSOrbisTaskletManager) != 0, "class size mismatch");
}