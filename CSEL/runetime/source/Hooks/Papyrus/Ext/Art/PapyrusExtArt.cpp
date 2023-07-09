#include "../Art/PapyrusExtArt.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/B/BGSArtObject.h"

namespace PapyrusExtArt
{
	// I really hate doing this...
	using namespace ConsoleRE;

	BSFixedString GetModelPath(BGSArtObject* thisArt)
	{
		return (thisArt) ? thisArt->GetModel() : NULL;
	}

	void SetModelPath(BGSArtObject* thisArt, BSFixedString nuPath)
	{
		if (thisArt) 
		{
			thisArt->SetModel(nuPath.m_data);
		}
	}

	bool RegisterArt(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetModelPath), BGSArtObject, BSFixedString>      ("GetModelPath", "Art", GetModelPath));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetModelPath), BGSArtObject, void, BSFixedString>("SetModelPath", "Art", SetModelPath));

		return true;
	}
}