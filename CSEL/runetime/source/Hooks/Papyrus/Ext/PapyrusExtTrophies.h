#pragma once

#include "../../../../../source/V/VirtualMachine.h"

#if __ORBIS__
#include <system_service.h>
#include <np.h>
#include <np\np_trophy.h>
#elif __OPENORBIS__
#include <orbis/SystemService.h>
#include <orbis/NpTrophy.h>
typedef OrbisNpTrophyDetails SceNpTrophyDetails;
typedef OrbisNpTrophyData	 SceNpTrophyData;
#endif

#ifndef TROP
#define TROP
struct TrophyStorage
{
public:
	SceNpTrophyDetails  m_details;
	SceNpTrophyData		m_data;
public:
	TrophyStorage(SceNpTrophyDetails& a_details, SceNpTrophyData& a_data)
	{
		memcpy(&m_details, &a_details, sizeof(SceNpTrophyDetails));
		memcpy(&m_data,    &a_data,    sizeof(SceNpTrophyData));
	}

	TrophyStorage(const char* a_tropyshortname, const char* a_trophyfullname, int32_t a_trophyid)
	{
		m_details.size = sizeof(SceNpTrophyDetails);
		m_data.size = sizeof(SceNpTrophyData);
		
		m_details.trophyId = a_trophyid;
		m_data.trophyId = a_trophyid;

		strncpy(m_details.name, a_tropyshortname, sizeof(m_details.name));
	}	
};
#endif

namespace PapyrusExtTrophies
{
	extern std::vector<TrophyStorage*> StoredTrophyData;

	void InitEnderal();
	void InitDefault();

	bool RegisterTrophies(ConsoleRE::BSScript::Internal::VirtualMachine*);
}