#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"
#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	class ActorCause;

	class ExtraActorCause : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kActorCause>;
	public:
		~ExtraActorCause() override;

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		NiPointer<ActorCause> actorCause;
	};
	static_assert(sizeof(ExtraActorCause) == 0x18);
}