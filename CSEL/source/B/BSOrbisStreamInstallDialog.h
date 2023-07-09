#pragma once
#include <stdint.h>

namespace ConsoleRE
{
	class BSOrbisStreamInstallDialog
	{
	public:
		virtual ~BSOrbisStreamInstallDialog();
	private:
	};
	static_assert(sizeof(BSOrbisStreamInstallDialog) != 0, "class size mismatch");
}