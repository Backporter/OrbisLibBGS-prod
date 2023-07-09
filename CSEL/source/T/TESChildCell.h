#pragma once

namespace ConsoleRE
{
	class TESObjectCELL;

	class TESChildCell
	{
	public:
		virtual ~TESChildCell();

		// add
		virtual TESObjectCELL* GetSaveParentCell() = 0;
	public:
	};
	static_assert(sizeof(TESChildCell) == 0x8);
}