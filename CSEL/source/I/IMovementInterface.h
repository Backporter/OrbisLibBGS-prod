#pragma once

namespace ConsoleRE
{
	class IMovementInterface
	{
	public:
		virtual ~IMovementInterface();
	public:
	};
	static_assert(sizeof(IMovementInterface) == 0x8);
}