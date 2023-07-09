#pragma once

#include "../../../OrbisUtil/include/Relocation.h"

#include "../A/ActorValueInfo.h"
#include "../A/ActorValues.h"

namespace ConsoleRE
{
	class ActorValueList
	{
	public:
		ActorValueList();
		~ActorValueList();
		
		static ActorValueList* GetSingleton()
		{
			Relocation<ActorValueList**> singleton("ActorValueList::Singleton", 0x20BEC10);
			return *singleton;
		}

		ActorValueInfo* GetActorValue(ActorValue a_actorvalue)
		{
			return a_actorvalue < ActorValue::kTotal ? m_values[static_cast<uint32_t>(a_actorvalue)] : nullptr;
		}

		ActorValue LookupActorValueByName(const char* a_name)
		{
			for (int i = 0; i < static_cast<uint32_t>(ActorValue::kTotal); i++)
			{
				if (strlen(a_name) == strlen(m_values[i]->enumName) && !strcasecmp(m_values[i]->enumName, a_name))
				{
					return static_cast<ActorValue>(i);
				}
			}

			return ActorValue::kNone;
		}
	public:
		ActorValueInfo* m_values[static_cast<uint32_t>(ActorValue::kTotal)];
	};
}