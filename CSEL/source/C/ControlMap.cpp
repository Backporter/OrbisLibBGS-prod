#include "../../../OrbisUtil/include/Relocation.h"

#include "../C/ControlMap.h"

#include <assert.h>

namespace ConsoleRE
{
	int8_t		ControlMap::AllowTextInput(bool a_allow)
	{
		if (a_allow)
		{
			if (textEntryCount != -1)
				textEntryCount++;
		}
		else
		{
			if (textEntryCount != 0)
				textEntryCount--;
		}

		return textEntryCount;
	}

	uint32_t	ControlMap::GetMappedKey(const char* a_eventID, INPUT_DEVICE a_device, InputContextID a_context)
	{
		assert(a_device < INPUT_DEVICE::kTotal);
		assert(a_context < InputContextID::kTotal);

		if (controlMap[a_context])
		{
			const auto& mappings = controlMap[a_context]->deviceMappings[a_device];
			BSFixedString eventID(a_eventID);

			for (auto& mapping : mappings)
			{
				if (mapping.eventID == eventID)
				{
					return mapping.inputKey;
				}
			}
		}

		return kInvalid;

	}

	const char*	ControlMap::GetUserEventName(uint32_t a_buttonID, INPUT_DEVICE a_device, InputContextID a_context)
	{
		assert(a_device < INPUT_DEVICE::kTotal);
		assert(a_context < InputContextID::kTotal);

		if (a_device == INPUT_DEVICE::kNone)
			return "";

		if (controlMap[a_context]) 
		{
			const auto&      mappings = controlMap[a_context]->deviceMappings[a_device];
			UserEventMapping tmp{};
			tmp.inputKey = static_cast<uint16_t>(a_buttonID);
			auto range = std::equal_range(mappings.begin(), mappings.end(), tmp, [](auto&& a_lhs, auto&& a_rhs) { return a_lhs.inputKey < a_rhs.inputKey; });

			if (std::distance(range.first, range.second) == 1) 
			{
				return range.first->eventID;
			}
		}

		return "";
	}
}