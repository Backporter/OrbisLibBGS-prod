#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"
#include "../N/NiPoint3.h"

namespace ConsoleRE
{
	class ExtraRefrPath : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kRefrPath>;
	public:
		~ExtraRefrPath();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		NiPoint3	startPos;
		NiPoint3	startTangent;
		NiPoint3	startEuler;
		NiPoint3	goalPos;
		NiPoint3	goalTangent;
		NiPoint3	goalEuler;
		float		speed;
		float		maxRotSpeed;
		float		currentParameter;
		uint32_t	type;
	};
	static_assert(sizeof(ExtraRefrPath) == 0x68);
}