#pragma once

#include "../../../OrbisUtil/include/Types.h"

#include "../B/BSString.h"
#include "../B/BSFile.h"
#include "../B/BSTList.h"
#include "../T/TESObjectCELL.h"

namespace ConsoleRE
{
	class TESFile
	{
	public:
		uint32_t GetPartialIndex() 
		{ 
			return !IsLight() ? Unk478 : (0xFE000 | Unk47A); 
		}

		uint32_t GetFormID(uint32_t formLower) 
		{
			return !IsLight() ? uint32_t(Unk478) << 24 | (formLower & 0xFFFFFF) : 0xFE000000 | (uint32_t(Unk47A) << 12) | (formLower & 0xFFF); 
		}

		bool	 IsLight()
		{ 
			return (Unk438 & 512) == 512; 
		}

		bool	 IsActive() 
		{
			return Unk478 != 0xFF; 
		}

		bool IsFormInMod(uint32_t formID) 
		{
			if (!IsLight() && (formID >> 24) == Unk478)
				return true;

			if (IsLight() && (formID >> 24) == 0xFE && ((formID & 0x00FFF000) >> 12) == Unk47A)
				return true;

			return false;
		}
	public:
		uint32_t								Unk000;
		uint32_t								Unk004;
		TESFile*								Unk008;
		void*									Unk010;
		uint64_t								Unk018;
		uint64_t								Unk020;
		uint8_t									Unk028;
		uint8_t									Unk029;
		uint16_t								Unk02A;
		uint32_t								Unk02C;
		BSFile*									Unk030;
		BSFile*									Unk038;
		void*									Unk040;
		void*									Unk048;
		void*									Unk050;
		char									fileName[260];
		char									path[260];
		void*									Unk260;
		uint32_t								Unk268;
		uint32_t								Unk26C;
		uint32_t								Unk270;
		uint32_t								Unk274;
		TESObjectCELL*							Unk278;
		uint32_t								Unk280;
		uint32_t								Unk284;
		uint32_t								Unk288;
		uint32_t								Unk28C;
		uint32_t								Unk290;
		uint32_t								Unk294;
		uint16_t								Unk298;
		uint16_t								Unk29A;
		uint32_t								Unk29C;
		uint32_t								Unk2A0;
		uint32_t								Unk2A4;
		uint32_t								Unk2A8;
		uint32_t								Unk2AC;
		uint32_t								Unk2B0;
		uint32_t								Unk2B4;
		uint32_t								Unk2B8;
		uint32_t								Unk2BC;
		uint32_t								Unk2C0;
		uint32_t								Unk2C4;
		uint16_t								Unk2C8;
		uint16_t								Unk2CA;
		uint32_t								Unk2CC;
		uint32_t								Unk2D0;
		uint32_t								Unk2D4;
		uint64_t								Unk2D8;
		uint64_t								Unk2E0;
		bool									Unk2E8;
		bool									Unk2E9;
		uint8_t									Unk2EA;
		uint8_t									Unk2EB;
		WIN32_FIND_DATAA						Unk2EC;
		float									Unk42C;
		uint32_t								Unk430;
		uint32_t								Unk434;
		uint32_t								Unk438;
		uint32_t								Unk43C;
		BSSimpleList<const char*>				Unk440;
		BSSimpleList<uint64_t*>					Unk450;
		uint32_t								Unk460;
		uint32_t								Unk464;
		TESFile**								Unk468;
		uint64_t								Unk470;
		uint8_t									Unk478;
		uint8_t									Unk479;
		uint16_t								Unk47A;
		uint32_t								Unk47C;
		BSString								Creator;
		BSString								Summary;
		void*									Unk4A0;
		uint32_t								Unk4A8;
		uint32_t								Unk4AC;
		void*									Unk4B0;
		uint32_t								Unk4B8;
		uint32_t								Unk4BC;
		void*									Unk4C0;
	};

	static_assert(offsetof(TESFile, fileName) == 0x58, "#");
	static_assert(offsetof(TESFile, Unk2E8)   == 0x2E8, "#");
	static_assert(offsetof(TESFile, path)     == 0x15C, "#");
	static_assert(offsetof(TESFile, Creator)  == 0x480, "#");
	static_assert(offsetof(TESFile, Summary)  == 0x490, "#");
	static_assert(sizeof(TESFile) == 0x4C8, "");
}