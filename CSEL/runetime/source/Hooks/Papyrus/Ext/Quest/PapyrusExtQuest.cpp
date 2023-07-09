#include "../../../../../../../OrbisUtil/include/Mutex.h"

#include "../Quest/PapyrusExtQuest.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/T/TESQuest.h"
#include "../../../../../../source/T/TESDataHandler.h"

#include <map>
namespace PapyrusExtQuest
{
	// I really hate doing this...
	using namespace ConsoleRE;

#pragma region
	std::vector<BGSBaseAlias*> GetAliases(TESQuest* thisQuest)
	{
		std::vector<BGSBaseAlias*> foundAliases;
		if (!thisQuest)
			return foundAliases;

		for (uint32_t n = 0; n < thisQuest->Unk48.m_size; n++)
		{
			BGSBaseAlias* alias = NULL;
			thisQuest->Unk48.Get(n, alias);
			if (alias)
			{
				foundAliases.push_back(alias);
			}
		}

		return foundAliases;
	}
#pragma endregion

	uint32_t g_invalidateQuestCache;
	xUtilty::Mutex	s_questCacheLock;
	typedef std::map<BSFixedString, TESQuest*> QuestCache;
	static QuestCache s_questCache;

	TESQuest* GetQuest(StaticFunctionTag*, BSFixedString editorID)
	{
		s_questCacheLock.Lock();

		if (g_invalidateQuestCache == 1) 
		{
			g_invalidateQuestCache = 0;
			s_questCache.clear();
		}

		if (s_questCache.empty()) 
		{
			TESDataHandler* pDataHandler = TESDataHandler::GetSingleton();
			BSTArray<TESQuest*>& quests = pDataHandler->GetFormArray<TESQuest>();
			for (uint32_t n = 0; n < quests.m_size; n++)
			{
				TESQuest* pQuest = NULL;
				quests.Get(n, pQuest);
				if (pQuest)
				{
					s_questCache.insert(QuestCache::value_type(BSFixedString(pQuest->formEditorID.c_str()), pQuest));
				}
			}
		}

		s_questCacheLock.Unlock();

		QuestCache::iterator it = s_questCache.find(editorID);
		TESQuest* pQuest = (it != s_questCache.end()) ? it->second : NULL;
		return pQuest;
	}

	BSFixedString GetId(TESQuest* thisQuest)
	{
		return (thisQuest) ? thisQuest->formEditorID.c_str() : NULL;
	}
	
	uint32_t GetPriority(TESQuest* thisQuest)
	{
		return (thisQuest) ? thisQuest->priority : 0;
	}

	uint32_t GetNumAliases(TESQuest* thisQuest)
	{
		return (thisQuest) ? thisQuest->Unk48.m_size : 0;
	}

	BGSBaseAlias* GetNthAlias(TESQuest* thisQuest, uint32_t n)
	{
		if (!thisQuest || n > thisQuest->Unk48.m_size)
			return NULL;

		BGSBaseAlias* alias = NULL;
		thisQuest->Unk48.Get(n, alias);
		if (alias) 
		{
			return alias;
		}

		return NULL;
	}

	BGSBaseAlias* GetAliasByName(TESQuest* thisQuest, BSFixedString s)
	{
		if (!thisQuest || !s.m_data)
			return NULL;

		for (uint32_t n = 0; n < thisQuest->Unk48.m_size; n++)
		{
			BGSBaseAlias* alias = NULL;
			thisQuest->Unk48.Get(n, alias);
			if (alias && alias->aliasName == s)
			{
				return alias;
			}
		}

		return NULL;
	}

	BGSBaseAlias* GetAliasById(TESQuest* thisQuest, uint32_t aliasId)
	{
		if (!thisQuest)
			return NULL;

		for (uint32_t n = 0; n < thisQuest->Unk48.m_size; n++)
		{
			BGSBaseAlias* alias = NULL;
			thisQuest->Unk48.Get(n, alias);
			if (alias && alias->aliasID == aliasId)
			{
				return alias;
			}
		}

		return NULL;
	}

	bool RegisterQuest(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		//
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetAliases),     TESQuest, std::vector<BGSBaseAlias*>>        ("GetAliases",     "Quest", GetAliases));
		//

		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetQuest),       StaticFunctionTag, TESQuest*, BSFixedString> ("GetQuest",       "Quest", GetQuest));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetId),          TESQuest, BSFixedString>                     ("GetId",          "Quest", GetId));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetPriority),    TESQuest, uint32_t>                          ("GetPriority",    "Quest", GetPriority));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetNumAliases),  TESQuest, uint32_t>                          ("GetNumAliases",  "Quest", GetNumAliases));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetNthAlias),    TESQuest, BGSBaseAlias*, uint32_t>           ("GetNthAlias",    "Quest", GetNthAlias));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetAliasByName), TESQuest, BGSBaseAlias*, BSFixedString>      ("GetAliasByName", "Quest", GetAliasByName));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetAliasById),   TESQuest, BGSBaseAlias*, uint32_t>           ("GetAliasById",   "Quest", GetAliasById));
		
		return true;
	}
}