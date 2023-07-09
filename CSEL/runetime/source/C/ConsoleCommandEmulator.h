#pragma once

#include "../Hooks/Hooks_Orbis.h"

#include <stdint.h>
#include <pthread.h>

#ifndef PREV_MAGIC
// TRIANGLE
#define PREV_MAGIC 0x00001000
#endif


#ifndef CURR_MAGIC
// SQUARE
#define CURR_MAGIC 0x00008000
#endif

#ifndef PREV_EXMAGIC
// DOWN ARROW
#define PREV_EXMAGIC 0x00000040
#endif

#ifndef CURR_EXMAGIC
// CIRCLE
#define CURR_EXMAGIC 0x00002000
#endif

namespace Runetime
{
	class CCE
	{
	public:
		CCE();
		~CCE();

		int32_t StartCCET();
		bool	InvokeCC(char* command);
		void	ThreadCleanUp();

		static CCE* GetSingleton()
		{
			static CCE _CCE;
			return &_CCE;
		}

	public:
		bool				t_ThreadActive;
		bool				t_Exit;
		pthread_t			CCEPthread;
		pthread_attr_t		CCEPthreadAttr;
	};
}