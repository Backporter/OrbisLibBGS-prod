#pragma once

namespace ConsoleRE
{
	class hkBaseObject
	{
	public:
		virtual ~hkBaseObject() = default;
	};
	static_assert(sizeof(hkBaseObject) == 0x8);
}