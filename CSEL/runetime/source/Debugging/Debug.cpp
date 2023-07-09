#if __ORBIS__ || __OPENORBIS__
#include "../../../../OrbisUtil/include/ASSERT.h"
#include "../../../../OrbisUtil/include/Relocation.h"
#include "../../../../OrbisUtil/include/Macro.h"
#include "../../../../OrbisUtil/include/MessageHandler.h"
#include "../../../../OrbisUtil/include/MemoryHandler.h"
#include "../../../../OrbisUtil/include/FileSystem.h"
#include "../../../../OrbisUtil/include/SystemWrapper.h"
#include "../../../../OrbisUtil/include/Trampoline.h"
#include "../../../../OrbisUtil/include/Macro.h"
#include "../../../../OrbisUtil/include/Logger.h"
#include "../../../../OrbisUtil/include/PersistentSocketConnection.h"

#endif

//
#include "../Hooks/Hooks_Development.h"

#include "../../Internal/Interfaces/SerializationInterface/Serialization/Serialization.h"
//

// #include "../../../source/Skyrim.h"

#include "Debug.h"
#include <iostream>

#if defined(__ORBIS__)
#include <video_out.h>
#include <gnm.h>
#include <gnmx.h>
#include <coredump.h>
#include <coredump_structureddata.h>
#include <system_service.h>
#include <videodec.h>
#include <sys\stat.h>
#include <fios2.h>
#elif defined(__SWITCH__) || defined(PLATFORM_NX)
#endif

bool g_bool = false;

namespace Runetime
{
	namespace Debug
	{
		int32_t CoredumpHandler(void* arg)
		{
			xUtilty::CoredumpPrintOut("[CSEL] ---SKYRIM_HAS_CRASHED---\n");
			return 0;
		}

		void InitCrashDumpOverride()
		{
#if defined(__ORBIS__)
			xUtilty::SystemWrapper::sceCoredumpRegisterCoredumpHandler(CoredumpHandler, 0x4000LL, nullptr);
#endif
		}

		void DebugCode(void* ptr = 0)
		{
		}

		void Init()
		{
			InitCrashDumpOverride();
			
			DebugCode();
		}
	}
}
