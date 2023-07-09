#pragma once

namespace ConsoleRE
{
	class GFxStateBagImpl
	{
	public:
		virtual ~GFxStateBagImpl();
		virtual void                    SetState(uint32_t a_stateType, void* a_state);
		virtual void*				    GetStateAddRef(uint32_t a_stateType);
		virtual void                    GetStatesAddRef(void** a_stateList, const uint32_t* a_stateTypes, uint32_t a_count);
	public:
	};
}