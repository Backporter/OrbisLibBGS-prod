#pragma once

#include "../B/BSTriShape.h"
#include "../F/FormTypes.h"
#include "../H/hkpMoppCode.h"
#include "../N/NiPoint2.h"
#include "../N/NiSmartPointer.h"
#include "../T/TESChildCell.h"
#include "../T/TESForm.h"

namespace ConsoleRE
{
	struct OBJ_LAND
	{
	public:
		enum class Flag
		{
			kNone = 0,
			kVertexNormals_HeightMap = 1 << 0,
			kVertexColors = 1 << 1,
			kLayers = 1 << 2,
			kMPCD = 1 << 10
		};
	public:
		uint32_t flags;  // 0
	};
	static_assert(sizeof(OBJ_LAND) == 0x4);

	struct CHAR_NORM
	{
	public:
		int8_t x;
		int8_t y;
		int8_t z;
	};
	static_assert(sizeof(CHAR_NORM) == 0x3);

	class TESObjectLAND : public TESForm, public TESChildCell
	{
	public:
		static constexpr int TypeID = 72;

		struct LoadedLandData
		{
		public:
			NiNode*               mesh[4];
			float                 heights[4][289];
			int8_t				  percents[4][289][6];
			int8_t				  colors[4][289][3];
			CHAR_NORM             normals[4][289];
			NiPointer<BSTriShape> geom[4];
			NiPointer<BSTriShape> border;
			NiPoint2              heightExtents;
			TESLandTexture*       defQuadTextures[4];
			TESLandTexture*       quadTextures[4][6];
			hkpMoppCode           moppCode;
			uint64_t			  unk49B0;
			uint64_t			  unk49B8;
			uint64_t			  unk49C0;
			uint64_t			  unk49C8;
		};
		static_assert(sizeof(LoadedLandData) == 0x49D0);
	public:
		~TESObjectLAND() override;

		// override (TESForm)
		bool     Load(TESFile* a_mod) override;
		TESForm* CreateDuplicateForm(bool a_createEditorID, void* a_arg2) override;
		void     SetAltered(bool a_set) override;
		bool     BelongsInGroup(FORM* a_form, bool a_allowParentGroups, bool a_currentOnly) override;
		void     CreateGroupData(FORM* a_form, FORM_GROUP* a_group) override;

		 // override (TESChildCell)
		TESObjectCELL* GetSaveParentCell() override;
	public:
		OBJ_LAND				data;
		uint32_t				pad2C;
		TESObjectCELL*			parentCell;
		NiPointer<QueuedFile>	queuedTextures;
		LoadedLandData*			loadedData;
	};
	static_assert(sizeof(TESObjectLAND) == 0x48);
}