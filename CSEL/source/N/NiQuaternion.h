#pragma once

namespace ConsoleRE
{
	class NiQuaternion
	{
	public:
		float w;
		float x;
		float y;
		float z;
	};
	static_assert(sizeof(NiQuaternion) == 0x10, "#");
}