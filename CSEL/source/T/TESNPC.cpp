#include "../../../OrbisUtil/include/Relocation.h"

#include "../T/TESNPC.h"

namespace ConsoleRE
{
	uint32_t TESNPC::GetNumActorBaseOverlays()
	{
		using func_t = decltype(&TESNPC::GetNumActorBaseOverlays);
		Relocation<func_t> func("", 0x3182B0);
		return func(this);
	}

	void TESNPC::ChangeHeadPart(BGSHeadPart* a_target)
	{
		using func_t = decltype(&TESNPC::ChangeHeadPart);
		Relocation<func_t> func("", 0x31D120);
		return func(this, a_target);
	}

	BGSHeadPart** TESNPC::GetBaseOverlays()
	{
		using func_t = decltype(&TESNPC::GetBaseOverlays);
		Relocation<func_t> func("", 0x31E030);
		return func(this);
	}

	BGSHeadPart* TESNPC::GetCurrentHeadPartByType(uint32_t a_type)
	{
		return HasOverlays() ? GetHeadPartOverlayByType(a_type) : GetHeadPartByType(a_type);
	}

	BGSHeadPart* TESNPC::GetHeadPartByType(uint32_t a_type)
	{
		if (headParts)
		{
			for (int i = 0; i < numHeadParts; i++)
			{
				if (headParts[i] && headParts[i]->type == a_type)
				{
					return headParts[i];
				}
			}
		}

		return nullptr;
	}

	BGSHeadPart* TESNPC::GetHeadPartOverlayByType(uint32_t a_type)
	{
		auto numOverlays = GetNumActorBaseOverlays();
		auto overlays = GetBaseOverlays();

		if (overlays)
		{
			for (int i = 0; i < numOverlays; i++)
			{
				if (overlays[i]->type == a_type)
				{
					return overlays[i];
				}
			}

		}

		return nullptr;
	}

	TESNPC* TESNPC::GetRootFaceNPC()
	{
		auto iter = this;
		while (iter->faceNPC) 
		{
			iter = iter->faceNPC;
		}
		return iter;
	}

	const TESNPC* TESNPC::GetRootFaceNPC() const
	{
		auto iter = this;
		while (iter->faceNPC) 
		{
			iter = iter->faceNPC;
		}
		return iter;
	}

	int TESNPC::GetSex()
	{
		using func_t = decltype(&TESNPC::GetSex);
		Relocation<func_t> func("", 0x300840);
		return func(this);
	}

	bool TESNPC::HasOverlays()
	{
		using func_t = decltype(&TESNPC::HasOverlays);
		Relocation<func_t> func("", 0x31DF20);
		return func(this);
	}

	void TESNPC::SetFaceTexture(BGSTextureSet* a_textureSet)
	{
		if (!headRelatedData && a_textureSet)
		{
			headRelatedData = new HeadRelatedData();
		}

		if (headRelatedData) 
		{
			headRelatedData->faceDetails = a_textureSet;
		}
	}

	void TESNPC::SetHairColor(BGSColorForm* a_hairColor)
	{
		if (!headRelatedData && a_hairColor) 
		{
			headRelatedData = new HeadRelatedData();
		}

		if (headRelatedData) 
		{
			headRelatedData->hairColor = a_hairColor;
		}
	}

	void TESNPC::SetSkinFromTint(NiColorA* a_result, TintMask* a_tintMask, bool a_fromTint)
	{
		using func_t = decltype(&TESNPC::SetSkinFromTint);
		Relocation<func_t> func("", 0x31B680);
		return func(this, a_result, a_tintMask, a_fromTint);
	}

	void TESNPC::UpdateNeck(BSFaceGenNiNode* a_faceNode)
	{
		using func_t = decltype(&TESNPC::UpdateNeck);
		Relocation<func_t> func("", 0x31B8E0);
		return func(this, a_faceNode);
	}
}