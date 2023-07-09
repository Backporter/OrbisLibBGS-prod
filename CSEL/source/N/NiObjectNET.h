#pragma once
#include "../B/BSFixedString.h"
#include "../N/NiSmartPointer.h"
#include "../N/NiTimeController.h"
#include "../N/NiExtraData.h"

#include "NiObject.h"

namespace ConsoleRE
{
	class NiTimeController;

	class NiObjectNET : public NiObject
	{
	public:
		~NiObjectNET() override;

		// override (NiObject)
		const NiRTTI* GetRTTI() const override;
		void          LoadBinary(NiStream& a_stream) override;
		void          LinkObject(NiStream& a_stream) override;
		bool          RegisterStreamables(NiStream& a_stream) override;
		void          SaveBinary(NiStream& a_stream) override;
		bool          IsEqual(NiObject* a_object) override;
		void          ProcessClone(NiCloningProcess& a_cloning) override;
		void          PostLinkObject(NiStream& a_stream) override;
	public:
		BSFixedString               name;
		NiPointer<NiTimeController> controllers;
		NiExtraData**               extra;
		uint16_t					extraDataSize;
		uint16_t					maxSize;
		uint32_t					pad2C;
	};
}