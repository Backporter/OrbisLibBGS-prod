#pragma once

namespace ConsoleRE
{
	class IMapCameraCallbacks
	{
	public:
		// add
		virtual void Unk_02();
		virtual void Unk_03();

		virtual ~IMapCameraCallbacks();
	};
	static_assert(sizeof(IMapCameraCallbacks) == 0x8);
}