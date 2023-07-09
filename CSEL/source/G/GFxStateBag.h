#pragma once

#include "../G/GFxFileConstants.h"
#include "../G/GFxState.h"
#include "../G/GPtr.h"

namespace ConsoleRE
{
	class GFxStateBag : public GFxFileConstants
	{
	public:
		// add
		virtual GFxStateBag* GetStateBagImpl();
		
		// add
		virtual ~GFxStateBag();
		
		// add
		virtual void		SetState(GFxState::StateType, GFxState*);
		virtual GFxState*	GetStateAddRef(GFxState::StateType) const;
		virtual void		GetStatesAddRef(GFxState**, GFxState::StateType*, uint32_t) const;

		template <class T>
		T* GetStateAddRef(GFxState::StateType a_state) const
		{
			return static_cast<T*>(GetStateAddRef(a_state));
		}
	};
}