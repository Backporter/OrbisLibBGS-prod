#pragma once

namespace ConsoleRE
{
	class MenuModeChangeEvent
	{
	public:
		enum class Mode
		{
			kNone = static_cast<std::underlying_type_t<Mode>>(-1),
			kHidden = 0,
			kDisplayed = 1
		};
	public:
		BSFixedString menu;
		uint8_t		  mode;
	};
}