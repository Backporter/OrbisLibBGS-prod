#pragma once

#include "../G/GFxValue.h"

#include <stdint.h>

namespace ConsoleRE
{
	class FxDelegateHandler;
	class FxResponseArgsBase;
	class GFxMovieView;

	class FxDelegateArgs
	{
	public:
		FxDelegateArgs(GFxValue a_responseID, FxDelegateHandler* a_handler, GFxMovieView* a_movie, const GFxValue* a_vals, uint32_t a_numArgs);

		void                             Respond(FxResponseArgsBase& a_params) const;
		const GFxValue&                  operator[](size_t a_pos) const;
		FxDelegateHandler*				 GetHandler() const;
		GFxMovieView*					 GetMovie() const;
		uint32_t						 GetArgCount() const;
	protected:
		GFxValue			m_responseID;
		FxDelegateHandler*	m_handler;
		GFxMovieView*		m_movieView;
		const GFxValue*		m_args;
		uint32_t			m_numArgs;
	};
	static_assert(sizeof(FxDelegateArgs) == 0x38);
}