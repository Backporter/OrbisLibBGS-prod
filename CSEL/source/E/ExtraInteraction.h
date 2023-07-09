#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSTSmartPointer.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class RefrInteraction;

	class ExtraInteraction : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kInteraction>;
	public:
		~ExtraInteraction();

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		BSTSmartPointer<RefrInteraction> interaction;
	};
}