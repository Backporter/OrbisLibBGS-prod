#include "../I/IMenu.h"

#include "../B/BSInputDeviceManager.h"
#include "../B/BSUIScaleformData.h"
#include "../G/GFxValue.h"
#include "../U/UIMessage.h"

#include <array>

namespace ConsoleRE
{
	void IMenu::Accept(CallbackProcessor*)
	{}

	void IMenu::PostCreate()
	{}

	void IMenu::Unk_04()
	{}

	uint32_t IMenu::ProcessMessage(UIMessage& a_message)
	{
		//
		if (a_message.type == UI_MESSAGE_TYPE::kScaleformEvent)
		{
			if (uiMovie)
			{
				if (a_message.data)
				{
					uiMovie->HandleEvent(*static_cast<BSUIScaleformData*>(a_message.data)->scaleformEvent);
					return (uint32_t)UI_MESSAGE_RESULTS::kHandled;
				}
			}
		}

		return (uint32_t)UI_MESSAGE_RESULTS::kPassOn;
	}

	void IMenu::AdvanceMovie(float, uint32_t a_currentTime)
	{
		if (uiMovie)
		{
			GFxValue currentTime(static_cast<double>(a_currentTime));
			uiMovie->SetVariable("CurrentTime", currentTime, GFxMovie::SetVarType::SV_Normal);
			uiMovie->Advance(static_cast<float>(currentTime.GetNumber()));
		}
	}

	void IMenu::PostDisplay()
	{
		if (uiMovie)
		{
			uiMovie->Display();
		}
	}

	void IMenu::PreDisplay()
	{}

	void IMenu::RefreshPlatform()
	{
		if (uiMovie && uiMovie->IsAvailable("_root.SetPlatform"))
		{
			std::array<GFxValue, 2> args;

			args[0] = 1.0;
			args[1] = false;

			uiMovie->Invoke("_root.SetPlatform", nullptr, args.data(), static_cast<uint32_t>(args.size()));
		}
	}
}