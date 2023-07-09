#include "../H/HUDObject.h"

namespace ConsoleRE
{
	HUDObject::HUDObject(GFxMovieView* a_view) :
		view(a_view),
		root()
	{}

	HUDObject::~HUDObject()
	{}

	bool HUDObject::ProcessMessage(UIMessage*)
	{
		return false;
	}

	void HUDObject::RegisterHUDComponent(FxDelegateArgs& a_params)
	{
		root = a_params[HudComponent::kThis];
	}

	void HUDObject::CleanUp()
	{
		return;
	}
}