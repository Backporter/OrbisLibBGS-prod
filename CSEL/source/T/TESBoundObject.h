#pragma once

#include "../B/BSString.h"
#include "../F/FormTypes.h"
#include "../N/NiSmartPointer.h"
#include "../T/TESObject.h"

#include <stdint.h>

namespace ConsoleRE
{
	class NiAVObject;
	class TESObjectREFR;

	class NiNPShortPoint3
	{
	public:
		int16_t x;
		int16_t y;
		int16_t z;
	};
	static_assert(sizeof(NiNPShortPoint3) == 0x6);

	class TESBoundObject : public TESObject
	{
	public:
		struct BOUND_DATA
		{
		public:
			NiNPShortPoint3 boundMin;
			NiNPShortPoint3 boundMax;
		};
		static_assert(sizeof(BOUND_DATA) == 0xC);
	public:
		~TESBoundObject() override;

		// override (TESObject)
		void        LoadObjectBound(TESFile* a_mod) override;
		bool        IsBoundObject() const override;
		bool        Activate(TESObjectREFR* a_targetRef, TESObjectREFR* a_activatorRef, uint8_t a_arg3, TESBoundObject* a_object, int32_t a_targetCount) override;
		NiAVObject* Clone3D(TESObjectREFR* a_ref, bool a_arg3) override;
		bool        ReplaceModel() override;

		// add
		virtual void                        SetObjectVoiceType(BGSVoiceType* a_voiceType);
		virtual BGSVoiceType*				GetObjectVoiceType() const;
		virtual NiAVObject*                 Clone3D(TESObjectREFR* a_ref);
		virtual bool                        ReplaceModel(const char* a_str);
		virtual bool                        GetActivateText(TESObjectREFR* a_activator, BSString& a_dst);
		virtual bool                        CalculateDoFavor(Actor* a_activator, bool a_arg2, TESObjectREFR* a_toActivate, float a_arg3);
		virtual void                        HandleRemoveItemFromContainer(TESObjectREFR* a_container);
		virtual void                        OnRemove3D(NiAVObject* a_obj3D);
		virtual void                        OnCheckModels();
		virtual void                        OnCopyReference();
		virtual void                        OnFinishScale();
	public:
		BOUND_DATA boundData;
	};
	static_assert(sizeof(TESBoundObject) == 0x28);
}