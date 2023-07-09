#pragma once

namespace ConsoleRE
{
	struct BGSSaveLoadBuffer
	{
	public:
		char* buffer;
	};
	static_assert(sizeof(BGSSaveLoadBuffer) == 0x8);

	struct BGSLoadGameSubBuffer
	{
	public:
		BGSSaveLoadBuffer buffer;
	};
	static_assert(sizeof(BGSLoadGameSubBuffer) == 0x8);
}