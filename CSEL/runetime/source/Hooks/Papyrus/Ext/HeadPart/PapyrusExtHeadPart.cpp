#include "../../../../../../../OrbisUtil/include/Mutex.h"

#include "../HeadPart/PapyrusExtHeadPart.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/B/BGSHeadPart.h"
#include "../../../../../../source/T/TESDataHandler.h"

#include <map>

namespace PapyrusExtHeadPart
{
	// I really hate doing this...
	using namespace ConsoleRE;

	xUtilty::Mutex	s_headPartCacheLock;
	typedef std::map<BSFixedString, BGSHeadPart*> HeadPartCache;
	static HeadPartCache s_headPartCache;

	BGSHeadPart* GetHeadPart(StaticFunctionTag*, BSFixedString editorID)
	{
		s_headPartCacheLock.Lock();

		if (s_headPartCache.empty()) 
		{
			TESDataHandler* pDataHandler = TESDataHandler::GetSingleton();
			BSTArray<BGSHeadPart*>& headParts = pDataHandler->GetFormArray<BGSHeadPart>();
			for (uint32_t n = 0; n < headParts.m_size; n++) 
			{
				BGSHeadPart* pHeadPart = NULL;
				headParts.Get(n, pHeadPart);
				if (pHeadPart) 
				{
					s_headPartCache.insert(HeadPartCache::value_type(BSFixedString(pHeadPart->formEditorID), pHeadPart));
				}
			}
		}

		s_headPartCacheLock.Unlock();

		HeadPartCache::iterator it = s_headPartCache.find(editorID);
		BGSHeadPart* pHeadPart = (it != s_headPartCache.end()) ? it->second : NULL;
		return pHeadPart;
	}


	uint32_t GetType(BGSHeadPart* thisPart)
	{
		if (!thisPart)
			return 0;

		return thisPart->type;
	}

	uint32_t GetNumExtraParts(BGSHeadPart* thisPart)
	{
		return (thisPart) ? thisPart->extraParts.m_size : 0;
	}

	BGSHeadPart* GetNthExtraPart(BGSHeadPart* thisPart, uint32_t n)
	{
		BGSHeadPart* headPart;
		if (!thisPart || !thisPart->extraParts.Get(n, headPart))
			return NULL;

		return headPart;
	}

	bool IsExtraPart(BGSHeadPart* thisPart)
	{
		return (thisPart && (thisPart->flags & 8) == 8) ? true : false;
	}

	bool HasExtraPart(BGSHeadPart* thisPart, BGSHeadPart* extraPart)
	{
		return (thisPart && thisPart->extraParts.Get(extraPart) != -1) ? true : false;
	}

	uint32_t GetIndexOfExtraPart(BGSHeadPart* thisPart, BGSHeadPart* extraPart)
	{
		return (thisPart) ? thisPart->extraParts.Get(extraPart) : 0;
	}

	BGSListForm* GetValidRaces(BGSHeadPart* thisPart)
	{
		return (thisPart) ? thisPart->validRaces : NULL;
	}

	void SetValidRaces(BGSHeadPart* thisPart, BGSListForm* raceList)
	{
		if (thisPart && raceList) 
		{
			thisPart->validRaces = raceList;
		}
	}

	BSFixedString GetPartName(BGSHeadPart* thisPart)
	{
		return thisPart ? thisPart->formEditorID : "";
	}

	bool RegisterHeadPart(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction <false,  NFDLSE(GetHeadPart),         StaticFunctionTag, BGSHeadPart*, BSFixedString>("GetHeadPart",         "HeadPart", GetHeadPart));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction <false,  NFDLSE(GetType),		       BGSHeadPart, uint32_t>                         ("GetType",             "HeadPart", GetType));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction <false,  NFDLSE(GetNumExtraParts),    BGSHeadPart, uint32_t>                         ("GetNumExtraParts",    "HeadPart", GetNumExtraParts));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction <false,  NFDLSE(GetNthExtraPart),     BGSHeadPart, BGSHeadPart*, uint32_t>           ("GetNthExtraPart",     "HeadPart", GetNthExtraPart));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction <false,  NFDLSE(HasExtraPart),        BGSHeadPart, bool, BGSHeadPart*>               ("HasExtraPart",        "HeadPart", HasExtraPart));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction <false,  NFDLSE(IsExtraPart),         BGSHeadPart, bool>                             ("IsExtraPart",         "HeadPart", IsExtraPart));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction <false,  NFDLSE(GetIndexOfExtraPart), BGSHeadPart, uint32_t, BGSHeadPart*>           ("GetIndexOfExtraPart", "HeadPart", GetIndexOfExtraPart));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction <false,  NFDLSE(GetValidRaces),       BGSHeadPart, BGSListForm*>                     ("GetValidRaces",       "HeadPart", GetValidRaces));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction <false,  NFDLSE(SetValidRaces),       BGSHeadPart, void, BGSListForm*>               ("SetValidRaces",       "HeadPart", SetValidRaces));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction <false,  NFDLSE(GetPartName),         BGSHeadPart, BSFixedString>                    ("GetPartName",         "HeadPart", GetPartName));

		return true;
	}
}