#include "../Race/PapyrusExtRace.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/T/TESRace.h"
#include "../../../../../../source/T/TESSpellList.h"
#include "../../../../../../source/S/SpellItem.h"
#include "../../../../../../source/T/TESDataHandler.h"
#include "../../../../../../source/T/TESObjectARMO.h"
#include "../../../../../../source/B/BSTArray.h"
#include "../../../../../../source/S/SpellItem.h"

#include "../../../../../../../OrbisUtil/include/Mutex.h"
#include <map>

namespace PapyrusExtRace
{
	// I really hate doing this...
	using namespace ConsoleRE;

	uint32_t g_invalidatePlayableRaceCache = 0;
	uint32_t g_invalidateRaceCache = 0;

	bool IsRaceFlagSet(TESRace* thisRace, uint32_t flag)
	{
		return (thisRace) ? (thisRace->data.flags & flag) == flag : false;
	}

	void SetRaceFlag(TESRace* thisRace, uint32_t flag)
	{
		if (thisRace)
		{
			thisRace->data.flags |= flag;

			if ((flag & 1) == 1)
				g_invalidatePlayableRaceCache = 1;
		}
	}

	void ClearRaceFlag(TESRace* thisRace, uint32_t flag)
	{
		if (thisRace) {
			thisRace->data.flags &= ~flag;

			if ((flag & 1) == 1)
				g_invalidatePlayableRaceCache = 1;
		}
	}


#pragma region
	typedef std::map<BSFixedString, TESRace*> RaceCache;
	static xUtilty::Mutex	s_raceCacheLock;
	static RaceCache s_raceCache;

	TESRace* GetRace(StaticFunctionTag*, BSFixedString editorID)
	{
		s_raceCacheLock.Lock();

		if (g_invalidateRaceCache == 1) 
		{
			s_raceCache.clear();
			g_invalidateRaceCache = 0;
		}

		if (s_raceCache.empty()) 
		{
			TESDataHandler* pDataHandler = TESDataHandler::GetSingleton();
			BSTArray<TESRace*>& races = pDataHandler->GetFormArray<TESRace>();
			for (uint32_t n = 0; n < races.m_size; n++) 
			{
				TESRace* pRace = NULL;
				races.Get(n, pRace);
				if (pRace) 
				{
					s_raceCache.insert(RaceCache::value_type(pRace->formEditorID, pRace));
				}
			}
		}

		s_raceCacheLock.Unlock();

		RaceCache::iterator it = s_raceCache.find(editorID);
		TESRace* pRace = (it != s_raceCache.end()) ? it->second : NULL;
		return pRace;
	}

	typedef std::vector<TESRace*> PlayableRaceCache;
	static xUtilty::Mutex	s_playableRaceCacheLock;
	static PlayableRaceCache s_playableRaceCache;

	uint32_t GetNumPlayableRaces(StaticFunctionTag * base)
	{
		s_playableRaceCacheLock.Lock();

		if (g_invalidatePlayableRaceCache == 1) 
		{
			s_playableRaceCache.clear();
			g_invalidatePlayableRaceCache = 0;
		}

		if (s_playableRaceCache.empty()) 
		{
			TESDataHandler* pDataHandler = TESDataHandler::GetSingleton();
			BSTArray<TESRace*>& races = pDataHandler->GetFormArray<TESRace>();
			for (uint32_t n = 0; n < races.m_size; n++) {
				TESRace* pRace = NULL;
				races.Get(n, pRace);
				if (pRace && IsRaceFlagSet(pRace, 1)) 
				{
					s_playableRaceCache.push_back(pRace);
				}
			}
		}

		s_playableRaceCacheLock.Unlock();
		return s_playableRaceCache.size();
	}

	TESRace * GetNthPlayableRace(StaticFunctionTag * base, int32_t n)
	{
		if (n < 0) 
		{
			return NULL;
		}

		s_playableRaceCacheLock.Lock();

		if (g_invalidatePlayableRaceCache == 1) 
		{
			s_playableRaceCache.clear();
			g_invalidatePlayableRaceCache = 0;
		}

		if (s_playableRaceCache.empty()) 
		{
			TESDataHandler* pDataHandler = TESDataHandler::GetSingleton();
			BSTArray<TESRace*>& races = pDataHandler->GetFormArray<TESRace>();
			for (uint32_t n = 0; n < races.m_size; n++)
			{
				TESRace* pRace = NULL;
				races.Get(n, pRace);
				if (pRace && IsRaceFlagSet(pRace, 1)) 
				{
					s_playableRaceCache.push_back(pRace);
				}
			}
		}

		s_playableRaceCacheLock.Unlock();
		return (n < s_playableRaceCache.size()) ? s_playableRaceCache.at(n) : NULL;
	}
#pragma endregion

	uint32_t GetSpellCount(TESRace* thisRace)
	{
		if (thisRace)
		{
			TESSpellList* a_parrent = static_cast<TESSpellList*>(thisRace);
			if (a_parrent->actorEffects)
			{
				return a_parrent->actorEffects->numSpells;
			}
		}

		return 0;
	}

	SpellItem* GetNthSpell(TESRace* thisRace, uint32_t n)
	{
		if (thisRace)
		{
			TESSpellList* cast = static_cast<TESSpellList*>(thisRace);
			if (cast->actorEffects && n < cast->actorEffects->numSpells)
			{
				return cast->actorEffects->spells[n];
			}
		}

		return NULL;
	}

	BGSVoiceType* GetDefaultVoiceType(TESRace* thisRace, bool female)
	{
		return (thisRace) ? thisRace->defaultVoiceTypes[female] : NULL;
	}

	void SetDefaultVoiceType(TESRace* thisRace, bool female, BGSVoiceType* voiceType)
	{
		if (thisRace) 
		{
			thisRace->defaultVoiceTypes[female] = voiceType;
		}
	}

	TESObjectARMO * GetSkin(TESRace* thisRace)
	{
		return (thisRace) ? static_cast<BGSSkinForm*>(thisRace)->skin : NULL;
	}

	void SetSkin(TESRace* thisRace, TESObjectARMO * skin)
	{
		if (thisRace) 
		{
			static_cast<BGSSkinForm*>(thisRace)->skin = skin;
		}
	}

	bool RegisterRace(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetSpellCount),		 TESRace, uint32_t>							("GetSpellCount",		"Race", GetSpellCount));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetNthSpell),		 TESRace, SpellItem*, uint32_t>				("GetNthSpell",			"Race", GetNthSpell));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(IsRaceFlagSet),		 TESRace, bool, uint32_t>					("IsRaceFlagSet",		"Race", IsRaceFlagSet));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(SetRaceFlag),		 TESRace, void, uint32_t>					("SetRaceFlag",			"Race", SetRaceFlag));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(ClearRaceFlag),		 TESRace, void, uint32_t>					("ClearRaceFlag",		"Race", ClearRaceFlag));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetDefaultVoiceType), TESRace, BGSVoiceType*, bool>				("GetDefaultVoiceType", "Race", GetDefaultVoiceType));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(SetDefaultVoiceType), TESRace, void, bool, BGSVoiceType*>		("SetDefaultVoiceType", "Race", SetDefaultVoiceType));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetSkin),			 TESRace, TESObjectARMO*>					("GetSkin",				"Race", GetSkin));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(SetSkin),			 TESRace, void, TESObjectARMO*>				("SetSkin",				"Race", SetSkin));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetRace),			 StaticFunctionTag, TESRace*, BSFixedString>("GetRace",				"Race", GetRace));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetNumPlayableRaces), StaticFunctionTag, uint32_t>				("GetNumPlayableRaces", "Race", GetNumPlayableRaces));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetNthPlayableRace),  StaticFunctionTag, TESRace*, uint32_t>		("GetNthPlayableRace",	"Race", GetNthPlayableRace));

		return true;
	}
}