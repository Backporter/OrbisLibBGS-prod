#pragma once

#include "../T/TESForm.h"

#include <stdint.h>

namespace ConsoleRE
{
	class NiAVObject;
	class TESObjectREFR;

	class TESObject : public TESForm
	{
	public:
		struct ChangeFlags
		{
			enum ChangeFlag : uint32_t
			{
				kObjectValue = 1 << 1,
				kObjectFullName = 1 << 2
			};
		};
	public:
		~TESObject() override;

		// override (TESForm)
		bool		IsObject() const override;
		uint32_t	GetRefCount() const override;

		// add
		virtual void                        Unk_3B(void);
		virtual bool                        IsBoundAnimObject();
		virtual TESWaterForm*				GetWaterType() const;
		virtual bool						IsAutoCalc() const;
		virtual void                        SetAutoCalc(bool a_autoCalc);
		virtual NiAVObject*                 Clone3D(TESObjectREFR* a_ref, bool a_arg3);
		virtual void                        UnClone3D(TESObjectREFR* a_ref);
		virtual bool                        IsMarker();
		virtual bool                        IsOcclusionMarker();
		virtual bool                        ReplaceModel();
		virtual uint32_t					IncRef();
		virtual uint32_t					DecRef();
		virtual NiAVObject*                 LoadGraphics(TESObjectREFR* a_ref);
	public:
	};
	static_assert(sizeof(TESObject) == 0x20);
}