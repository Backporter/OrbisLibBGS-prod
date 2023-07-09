#pragma once

#include "../B/BSISoundDescriptor.h"

namespace ConsoleRE
{
	class BGSSoundCategory;
	class TESFile;
	class TESForm;

	class BGSSoundDescriptor : public BSISoundDescriptor
	{
	public:
		~BGSSoundDescriptor() override;

		// add
		virtual void                        InitSound(TESForm* a_src);
		virtual bool                        LoadSound(TESFile* a_mod);
		virtual uint32_t					GetType() const = 0;
		virtual void                        Unk_07(void) = 0;
	public:
		BGSSoundCategory*	category;
		uint32_t			alternateSoundFormID;
	};
	static_assert(sizeof(BGSSoundDescriptor) == 0x18);
}