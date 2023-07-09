#include "../TextureSets/PapyrusExtTextureSet.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/B/BGSTextureSet.h"

namespace PapyrusExtTextureSet
{
	// I really hate doing this...
	using namespace ConsoleRE;

	uint32_t GetNumTexturePaths(BGSTextureSet * thisTextureSet)
	{
		return thisTextureSet ? 8 : NULL;
	}

	BSFixedString GetNthTexturePath(BGSTextureSet* thisTextureSet, uint32_t n)
	{
		return (thisTextureSet && n < 8) ? thisTextureSet->Textures[n].textureName : NULL;
	}

	void SetNthTexturePath(BGSTextureSet * thisTextureSet, uint32_t n, BSFixedString texturePath)
	{
		if (thisTextureSet && n < 8)
		{
			thisTextureSet->Textures[n].textureName = texturePath;
		}
	}

	bool RegisterTextureSet(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetNumTexturePaths), BGSTextureSet, uint32_t>                      ("GetNumTexturePaths", "TextureSet", GetNumTexturePaths));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetNthTexturePath),  BGSTextureSet, BSFixedString, uint32_t>       ("GetNthTexturePath",  "TextureSet", GetNthTexturePath));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SetNthTexturePath),  BGSTextureSet, void, uint32_t, BSFixedString> ("SetNthTexturePath",  "TextureSet", SetNthTexturePath));

		return true;
	}
}