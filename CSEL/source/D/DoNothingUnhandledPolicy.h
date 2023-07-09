#pragma once

namespace ConsoleRE
{
	template <typename T>
	class DoNothingUnhandledPolicy
	{
	public:
		DoNothingUnhandledPolicy();
		virtual ~DoNothingUnhandledPolicy();
	public:
	};
	static_assert(sizeof(DoNothingUnhandledPolicy<void*>) == 0x8, "");
}