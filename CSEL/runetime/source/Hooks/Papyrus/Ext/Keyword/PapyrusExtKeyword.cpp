#include "../../../../../../../OrbisUtil/include/Mutex.h"

#include "../Keyword/PapyrusExtKeyword.h"

#include "../../../../../../source/T/TESDataHandler.h"
#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/B/BGSKeyword.h"

#include <map>

namespace PapyrusExtKeyword
{
	// I really hate doing this...
	using namespace ConsoleRE;

	typedef std::map <BSFixedString, BGSKeyword *> KeywordCache;
	static xUtilty::Mutex	s_keywordCacheLock;
	static KeywordCache s_keywordCache;
	
	BGSKeyword* GetKeyword(StaticFunctionTag*, BSFixedString keyword)
	{
		s_keywordCacheLock.Lock();
		
		if (s_keywordCache.empty()) 
		{
			TESDataHandler* pDataHandler = TESDataHandler::GetSingleton();
			BSTArray<BGSKeyword*>& keywords = pDataHandler->GetFormArray<BGSKeyword>();
			for (uint32_t n = 0; n < keywords.m_size; n++) 
			{
				BGSKeyword* pKeyword = NULL;
				keywords.Get(n, pKeyword);
				if (pKeyword) 
				{
					s_keywordCache.insert(KeywordCache::value_type(BSFixedString(pKeyword->keyword.c_str()), pKeyword));
				}
			}
		}
	
		s_keywordCacheLock.Unlock();
	
		KeywordCache::iterator it = s_keywordCache.find(keyword);
		BGSKeyword* pKeyword = (it != s_keywordCache.end()) ? it->second : NULL;
		return pKeyword;
	}

	BSFixedString GetString(BGSKeyword* thisKeyword)
	{
		return (thisKeyword) ? thisKeyword->keyword.c_str() : NULL;
	}

	bool RegisterKeyword(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetString),  BGSKeyword, BSFixedString>                    ("GetString",  "Keyword", GetString));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetKeyword), StaticFunctionTag, BGSKeyword*, BSFixedString>("GetKeyword", "Keyword", GetKeyword));

		return true;
	}
}