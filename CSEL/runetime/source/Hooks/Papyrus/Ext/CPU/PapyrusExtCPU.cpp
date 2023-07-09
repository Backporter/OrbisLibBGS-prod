#include "../../../../../../../OrbisUtil/include//FileSystem.h"
#include "../../../../../../../OrbisUtil/include/SystemWrapper.h"
#include "../../../../../../../OrbisUtil/include/CPU.h"

#include "../CPU/PapyrusExtCPU.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"

namespace PapyrusExtCPU
{
	// I really hate doing this...
	using namespace ConsoleRE;
	
	float GetCPUClockSpeed(StaticFunctionTag* tag)
	{
		float ret = xUtilty::CPU::GetFrequency();
		return ret;
	}

	// static SystemWrapper::proc Stat_Data[3072];

	uint32_t GetCPUUsage(int threadidx = 0)
	{
		// unsigned int Idle_Thread_ID[8];
		// int Thread_Count = 3072;
		// 
		// if (!SystemWrapper::sceKernelGetCpuUsage(Stat_Data, &Thread_Count) && Thread_Count > 0)
		// {
		// 	char Thread_Name[0x40];
		// 	int Core_Count = 0;
		// 	for (int i = 0; i < Thread_Count; i++)
		// 	{
		// 		if (!SystemWrapper::sceKernelGetThreadName(Stat_Data[i].td_tid, Thread_Name) && sscanf(Thread_Name, "SceIdleCpu%d", &Core_Count) == 1 && Core_Count <= 7)
		// 		{
		// 			//klog("[System Monitor][SceIdleCpu%-> %i\n", Core_Count, Stat_Data[i].td_tid);
		// 			Idle_Thread_ID[Core_Count] = Stat_Data[i].td_tid;
		// 		}
		// 	}
		// }

		return 0;
	}

	bool RegisterCPU(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetCPUClockSpeed),   StaticFunctionTag, uint32_t> ("GetFrequency", "CPU", GetCPUClockSpeed));
		
		VM->SetCallableFromTasklets("CPU", "GetFrequency",	true);

		return true;
	}
}