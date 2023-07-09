#pragma once

namespace ConsoleRE
{
	class BSOrbisTaskletData
	{
	public:
		virtual ~BSOrbisTaskletData();
	private:
	};
	static_assert(sizeof(BSOrbisTaskletData) != 0, "class size mismatch");
}