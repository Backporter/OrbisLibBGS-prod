#include "../B/BSSoundHandle.h"

namespace ConsoleRE
{
	BSSoundHandle::BSSoundHandle() :
		soundID(kInvalidID),
		assumeSuccess(false),
		pad05(0),
		pad06(0),
		state(static_cast<uint32_t>(AssumedState::kInitialized))
	{}

	bool BSSoundHandle::IsValid()
	{
		using func_t = decltype(&BSSoundHandle::IsValid);
		Relocation<func_t> func("", 0xE16F80);
		return func(this);
	}

	bool BSSoundHandle::SetPosition(NiPoint3 a_pos)
	{
		using func_t = decltype(&BSSoundHandle::SetPosition);
		Relocation<func_t> func("", 0xE16E00);
		return func(this, a_pos);
	}

	void BSSoundHandle::SetObjectToFollow(NiAVObject* a_node)
	{
		using func_t = decltype(&BSSoundHandle::SetObjectToFollow);
		Relocation<func_t> func("", 0xE17190);
		return func(this, a_node);
	}

	bool BSSoundHandle::Stop()
	{
		using func_t = decltype(&BSSoundHandle::Stop);
		Relocation<func_t> func("", 0xE16B80);
		return func(this);
	}

	bool BSSoundHandle::Play()
	{
		using func_t = decltype(&BSSoundHandle::Play);
		Relocation<func_t> func("", 0xE16AC0);
		return func(this);
	}
}