#include "../F/FxDelegateArgs.h"

#include "../F/FxResponseArgsBase.h"
#include "../G/GFxMovieView.h"

namespace ConsoleRE
{
	FxDelegateArgs::FxDelegateArgs(GFxValue a_responseID, FxDelegateHandler* a_handler, GFxMovieView* a_movie, const GFxValue* a_vals, uint32_t a_numArgs) : 
		m_responseID(a_responseID), m_handler(a_handler), m_movieView(a_movie), m_args(a_vals), m_numArgs(a_numArgs)
	{
	}

	void FxDelegateArgs::Respond(FxResponseArgsBase& a_params) const
	{
		GFxValue* values = nullptr;
		const uint32_t numValues = a_params.GetValues(std::addressof(values));
		if (values) 
		{
			values[0] = m_responseID;
			m_movieView->InvokeNoReturn((char*)"respond", values, numValues);
		}
	}

	const GFxValue& FxDelegateArgs::operator[](size_t a_pos) const
	{
		assert(a_pos < m_numArgs);
		return m_args[a_pos];
	}

	FxDelegateHandler* FxDelegateArgs::GetHandler() const
	{
		return m_handler;
	}

	GFxMovieView* FxDelegateArgs::GetMovie() const
	{
		return m_movieView;
	}

	uint32_t FxDelegateArgs::GetArgCount() const
	{
		return m_numArgs;
	}
}