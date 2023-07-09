#if __ORBIS__ || __OPENORBIS__
#include "../../../../../../OrbisUtil/include/MessageHandler.h"
#endif

#include "../../../../../source/B/BSFixedString.h"
#include "../../../../../source/N/NativeFunction.h"

#if __ORBIS__ || __OPENORBIS__
#include "../../../../../source/B/BSORBISAwardsSystemUtility.h"
#endif

#include "../Ext/PapyrusExtTrophies.h"

#include "../../../../source/Enderal/Enderal.h"

namespace PapyrusExtTrophies
{
#if __ORBIS__ || __OPENORBIS__
	std::vector<TrophyStorage*> StoredTrophyData;
#endif

	// ye i know, this needs to be cleaned up... ill do that later.
	void InitEnderal()
	{
#if __ORBIS__ || __OPENORBIS__
		StoredTrophyData.push_back(new TrophyStorage("null", "Platinum Trophy", 0));
		StoredTrophyData.push_back(new TrophyStorage("END_COMPLETE_MQP01_01", "Burnt Flesh", 1));
		StoredTrophyData.push_back(new TrophyStorage("END_STARLING_PUZZLE_01", "Nimble Feet", 2));
		StoredTrophyData.push_back(new TrophyStorage("END_LISHARI_TAVERN_01", "A Fine Drink", 3));
		StoredTrophyData.push_back(new TrophyStorage("END_COMPLETE_MQ06_01", "Keeper of the Holy Order", 4));
		StoredTrophyData.push_back(new TrophyStorage("END_PROTO_BEACON_01", "A Sliver of Hope", 5));
		StoredTrophyData.push_back(new TrophyStorage("END_WORD_OF_THE_DEAD_01", "Voices of the Dead", 6));
		StoredTrophyData.push_back(new TrophyStorage("END_HALFMOON_ISLAND_01", "Halfmoon Island", 7));
		StoredTrophyData.push_back(new TrophyStorage("END_DREAM_02", "Aren't we beautiful?", 8));
		StoredTrophyData.push_back(new TrophyStorage("END_STARLINGSPHERE_01", "Good shot", 9));
		StoredTrophyData.push_back(new TrophyStorage("END_SILVERGROVE_01", "The Grove", 10));
		StoredTrophyData.push_back(new TrophyStorage("END_BUTTERFLIES_01", "Thorough", 11));
		StoredTrophyData.push_back(new TrophyStorage("END_RYNEUS_SILVERGROVE_01", "What dreams may come", 12));
		StoredTrophyData.push_back(new TrophyStorage("END_BLACK_STONES_01", "Onyx", 13));
		StoredTrophyData.push_back(new TrophyStorage("END_SIEGE_01", "Invasion", 14));
		StoredTrophyData.push_back(new TrophyStorage("END_DREAM_03", "Goodbye, Daddy", 15));
		StoredTrophyData.push_back(new TrophyStorage("END_STARSHIP_01", "Gertrude's Wings", 16));
		StoredTrophyData.push_back(new TrophyStorage("END_NAEA_01", "Näea", 17));
		StoredTrophyData.push_back(new TrophyStorage("END_DREAMFLOWER_01", "The Dreamflower", 18));
		StoredTrophyData.push_back(new TrophyStorage("END_COMPLETE_CALIA_01", "One Soul", 19));
		StoredTrophyData.push_back(new TrophyStorage("END_COMPLETE_JESPAR_01", "Part of Something", 20));
		StoredTrophyData.push_back(new TrophyStorage("END_ROMANCE_JESPAR_01", "Lethonia", 21));
		StoredTrophyData.push_back(new TrophyStorage("END_BLACK_GUARDIAN_01", "The Black Guardian", 22));
		StoredTrophyData.push_back(new TrophyStorage("END_COMPLETE_MQ18B_01", "Free At Last", 23));
		StoredTrophyData.push_back(new TrophyStorage("END_COMPLETE_MQ18A_01", "A Better World", 24));
		StoredTrophyData.push_back(new TrophyStorage("END_ROMANCE_CALIA_01", "The Beast Overcome", 25));
		StoredTrophyData.push_back(new TrophyStorage("END_COMPLETE_MQ18C_01", "What's reality, anyway?", 26));
		StoredTrophyData.push_back(new TrophyStorage("END_QUESTS_01", "Adventurous", 27));
		StoredTrophyData.push_back(new TrophyStorage("END_BOUNTY_01", "Bounty Hunter", 28));
		StoredTrophyData.push_back(new TrophyStorage("END_MIRELL_03", "Sleep, My Child", 29));
		StoredTrophyData.push_back(new TrophyStorage("END_MIRELL_01", "There's Always Hope", 30));
		StoredTrophyData.push_back(new TrophyStorage("END_MIRELL_02", "Coup De Grace", 31));
		StoredTrophyData.push_back(new TrophyStorage("END_MYTHS_01", "Slayer of Beasts", 32));
		StoredTrophyData.push_back(new TrophyStorage("END_MASTER_SKULL_01", "Cosmic Harmony", 33));
		StoredTrophyData.push_back(new TrophyStorage("END_WHIRLWIND_01", "Whirlwind", 34));
		StoredTrophyData.push_back(new TrophyStorage("END_HOME_01", "Home, Sweet Home", 35));
		StoredTrophyData.push_back(new TrophyStorage("END_ROCIO_01", "What We Deserve", 36));
		StoredTrophyData.push_back(new TrophyStorage("END_ESME_01", "Rememberance", 37));
		StoredTrophyData.push_back(new TrophyStorage("END_HORST_01", "Vanquisher of Horst", 38));
		StoredTrophyData.push_back(new TrophyStorage("END_MANFRED_01", "Cuthbert the Spirit Pig", 39));
		StoredTrophyData.push_back(new TrophyStorage("END_PROTECTOR_01", "Protector", 40));
		StoredTrophyData.push_back(new TrophyStorage("END_FINDERSKEEPERS_01", "Finders Keepers", 41));
		StoredTrophyData.push_back(new TrophyStorage("END_DIJAAM_NO_BLACKMAIL_01", "Steadfast", 42));
		StoredTrophyData.push_back(new TrophyStorage("END_SIDED_DIJAAM_01", "The Scorpion's Tail", 43));
		StoredTrophyData.push_back(new TrophyStorage("END_SIDED_MAEL_01	", "The Lion's Roar", 44));
		StoredTrophyData.push_back(new TrophyStorage("END_DIJAAM_ESCAPE_01", "Worth it", 45));
		StoredTrophyData.push_back(new TrophyStorage("END_QALIAN_01", "The Price of Sin", 46));
		StoredTrophyData.push_back(new TrophyStorage("END_QALIAN_02", "He Already Paid the Price", 47));
		StoredTrophyData.push_back(new TrophyStorage("END_ORPHANAGE_01", "The Treasures of the Destitute", 48));
		StoredTrophyData.push_back(new TrophyStorage("END_MOUNT_01", "Direwolf", 49));
		StoredTrophyData.push_back(new TrophyStorage("END_THARAEL_NO_SUICIDE_01", "Repentance", 50));
		StoredTrophyData.push_back(new TrophyStorage("END_SYNERGY_01", "Synergetic", 51));
		StoredTrophyData.push_back(new TrophyStorage("END_AFFINITY_01", "Legendary", 52));
		StoredTrophyData.push_back(new TrophyStorage("END_AFFINITY_02", "Mythical", 53));
		StoredTrophyData.push_back(new TrophyStorage("END_MEMORY_TREE_01", "Proficient", 54));
		StoredTrophyData.push_back(new TrophyStorage("END_RHETORIC_01", "Witty", 55));
		StoredTrophyData.push_back(new TrophyStorage("END_WEREWOLF_01", "Claws", 56));
		StoredTrophyData.push_back(new TrophyStorage("END_HIDDEN_SLOT_01", "Nifty", 57));
		StoredTrophyData.push_back(new TrophyStorage("END_MYTHICAL_SPELL_01", "Master of the Arcane", 58));
		StoredTrophyData.push_back(new TrophyStorage("END_APPARITION_01", "The Spectral Horde", 59));
		StoredTrophyData.push_back(new TrophyStorage("END_FROZEN_01", "Icy Embrace", 60));
		StoredTrophyData.push_back(new TrophyStorage("END_TALENT_BOOK_01", "Hidden Powers", 61));
		StoredTrophyData.push_back(new TrophyStorage("END_MYRAD_01", "Wings", 62));
		StoredTrophyData.push_back(new TrophyStorage("END_LOCATIONS_01", "Behind the Horizon", 63));
		StoredTrophyData.push_back(new TrophyStorage("END_ORE_01", "Goldrush", 64));
		StoredTrophyData.push_back(new TrophyStorage("END_SET_01", "Well-equipped", 65));
		StoredTrophyData.push_back(new TrophyStorage("END_ARCANISTS_FEVER_01", "Mage-bane", 66));
		StoredTrophyData.push_back(new TrophyStorage("END_PRINCE_MITH_02", "Lyrical Outpours and Other Bodily Fluids", 67));
		StoredTrophyData.push_back(new TrophyStorage("END_PRINCE_MITH_01", "Philistine", 68));
		StoredTrophyData.push_back(new TrophyStorage("END_ARROW_01", "We're Sorry", 69));
		StoredTrophyData.push_back(new TrophyStorage("END_BREEEAD_01", "Crunchy Pleasures", 70));
		StoredTrophyData.push_back(new TrophyStorage("END_DICEGOD_01", "Dice God", 71));
		StoredTrophyData.push_back(new TrophyStorage("END_CARDSHARK_01", "Card Shark", 72));
		StoredTrophyData.push_back(new TrophyStorage("END_DRAGON_01", "Yes, We Got Them Too", 73));
		StoredTrophyData.push_back(new TrophyStorage("END_PEAK_01", "Reach for the Stars", 74));
		StoredTrophyData.push_back(new TrophyStorage("END_KOPPOPHON_01", "Music of the Lightborn", 75));
		StoredTrophyData.push_back(new TrophyStorage("END_BANKACCOUNT_01", "Mammon", 76));
		StoredTrophyData.push_back(new TrophyStorage("END_LUKE_SKYWALKER_01", "Come On, You Stupid Rod", 77));
		StoredTrophyData.push_back(new TrophyStorage("END_FETCHQUEST_01", "Fetchquest", 78));
		StoredTrophyData.push_back(new TrophyStorage("END_FETCHQUEST_02", "Fetchquest, Vol. 2.", 79));
		StoredTrophyData.push_back(new TrophyStorage("END_KNOWLEDGE_01", "Knowledge Is Power", 80));
		StoredTrophyData.push_back(new TrophyStorage("END_BUTCHER_01", "Chronicles of Blood", 81));
		StoredTrophyData.push_back(new TrophyStorage("END_EGGS_01", "Master of Eggs", 82));
		StoredTrophyData.push_back(new TrophyStorage("END_APPARITION_02", "Catch 'Em All", 83));
		StoredTrophyData.push_back(new TrophyStorage("END_VATYRA_01", "The Queen of the Forsaken", 84));
#endif
	}
	
	void InitDefault()
	{
#if __ORBIS__ || __OPENORBIS__
		xUtilty::KernelPrintOut("The PS4 is about to spam the log... sry :(");
		ConsoleRE::BSORBISAwardsSystemUtility* TrophieSystem = ConsoleRE::BSORBISAwardsSystemUtility::GetSingleton();
		
		SceNpTrophyDetails details;
		SceNpTrophyData data;
		
		details.size = sizeof(SceNpTrophyDetails);
		data.size = sizeof(SceNpTrophyData);

		for (int i = 0; i < INT32_MAX; i++)
		{
			int ret = sceNpTrophyGetTrophyInfo(TrophieSystem->Context, TrophieSystem->handle, i, &details, &data);
			if (ret != 0)
			{	
				// 0x8055160A just means i > total torphy count
				if (ret == 0x8055160A) { break; }

				xUtilty::KernelPrintOut("sceNpTrophyGetTrophyInfo Failed With 0x%lx", ret);
				break;
			}

			StoredTrophyData.push_back(new TrophyStorage(details, data));
		}
#endif
	}

	bool ShowAchievements(ConsoleRE::StaticFunctionTag* tag)
	{
#if __ORBIS__ || __OPENORBIS__
		auto Awards = ConsoleRE::BSORBISAwardsSystemUtility::GetSingleton();
		if (sceNpTrophyShowTrophyList(Awards->Context, Awards->handle) != 0)
		{
			return false;
		}
#endif
		return true;
	}

	int  QueryAchievementCount(ConsoleRE::StaticFunctionTag* tag)
	{
#if __ORBIS__ || __OPENORBIS__
		return StoredTrophyData.size();
#endif
	}

	bool UnlockAchievement(ConsoleRE::StaticFunctionTag* tag, ConsoleRE::BSFixedString trophyname)
	{
#if __ORBIS__ || __OPENORBIS__
		xUtilty::Notify("UnlockAchievement invoked with %s", trophyname.c_str());
#endif
		for (int i = 0; i < StoredTrophyData.size(); i++)
		{
#if __ORBIS__ || __OPENORBIS__
			if (strcasecmp(StoredTrophyData[i]->m_details.name, trophyname.c_str()) == 0)
			{
				ConsoleRE::BSORBISAwardsSystemUtility::GetSingleton()->UnlockAchievement(StoredTrophyData[i]->m_details.trophyId);
				return true;
			}
		}
#endif
		return false;
	}

	bool LockAchievement(ConsoleRE::StaticFunctionTag* tag, ConsoleRE::BSFixedString trophyname)
	{
		return true;
	}

	int	 QueryAchievementState(ConsoleRE::StaticFunctionTag* tag, ConsoleRE::BSFixedString trophyname, int flag)
	{
		int ID = 0;
		int ret = -1;

		for (int i = 0; i < StoredTrophyData.size(); i++)
		{
#if __ORBIS__ || __OPENORBIS__
			if (strcasecmp(StoredTrophyData[i]->m_details.name, trophyname.c_str()) == 0)
			{
				ID = i;
				break;
			}
#endif
		}

		if (ID < 0)
		{
			return ret;
		}

		switch (flag)
		{
			// Locked State... locked/unlocked
			case 0:
#if __ORBIS__ || __OPENORBIS__
				ret = StoredTrophyData[ID]->m_data.unlocked;
#endif
				break;
			
			// Visable state.. Viewable/Non-Viewable unless unlocked
			case 1:
#if __ORBIS__ || __OPENORBIS__
				ret = StoredTrophyData[ID]->m_details.hidden;
#endif
				break;

			// Grade... unkown(0)/Platinum(1)/Gold(2)/Silver(3)/Bronze(4)
			case 2:
#if __ORBIS__ | __OPENORBIS__
				ret = StoredTrophyData[ID]->m_details.trophyGrade;
#endif
				break;
				
			// ID.. trophy ID in int form
			case 3:
#if __ORBIS__ || __OPENORBIS__
				ret = StoredTrophyData[ID]->m_details.trophyId;
#endif
				break;
		}

		return ret;
	}

	pthread_t initthread;
	void* ThreadedInit(void*)
	{
		if (Runetime::Enderal::IsEnderal)
		{
			xUtilty::KernelPrintOut("Enderal Detected! swapping to Enderal specific trophy logic!");
			InitEnderal();
		}
		else
		{
			InitDefault();
		}

		scePthreadExit(nullptr);
	}

	bool RegisterTrophies(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{				
		scePthreadCreate(&initthread, nullptr, ThreadedInit, nullptr, "Papyrus Trophy Init Thread");

		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction <false,  NFDLSE(ShowAchievements),      ConsoleRE::StaticFunctionTag, bool>							       ("ShowAchievements",	      "PS4",	ShowAchievements));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction <false,  NFDLSE(QueryAchievementCount), ConsoleRE::StaticFunctionTag, int>								       ("QueryAchievementCount",  "PS4",	QueryAchievementCount));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction <false,  NFDLSE(UnlockAchievement),     ConsoleRE::StaticFunctionTag, bool, ConsoleRE::BSFixedString>	       ("UnlockAchievement",	  "PS4",	UnlockAchievement));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction <false,  NFDLSE(LockAchievement),       ConsoleRE::StaticFunctionTag, bool, ConsoleRE::BSFixedString>	       ("LockAchievement",		  "PS4",	LockAchievement));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction <false,  NFDLSE(QueryAchievementState), ConsoleRE::StaticFunctionTag, int,  ConsoleRE::BSFixedString, int>    ("QueryAchievementState",  "PS4",	QueryAchievementState));
		VM->RegisterFunction(new ConsoleRE::BSScript::NativeFunction <false,  NFDLSE(UnlockAchievement),     ConsoleRE::StaticFunctionTag, bool, ConsoleRE::BSFixedString>		   ("UnlockAchievement",	  "Game",	UnlockAchievement));
		
		return true;
	}
}