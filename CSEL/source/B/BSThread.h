#pragma once

#include <stdint.h>
#include <pthread.h>
#include <stddef.h>

#if defined (__ORBIS__)
#include <kernel.h>
#elif defined(__OPENORBIS__)
#include <orbis/libkernel.h>
typedef OrbisKernelEventFlag SceKernelEventFlag;
#endif

#include <pthread.h>

namespace ConsoleRE
{
	class BSThread
	{
	public:
		virtual ~BSThread();

		// add
		virtual uint32_t WaitForEx();
		virtual void	 SetEx();
	public:
		pthread_mutex_t lock;
	};
}