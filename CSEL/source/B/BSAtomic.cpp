#include "../../../OrbisUtil/include/Relocation.h"
#include "../../../OrbisUtil/include/SystemWrapper.h"

#include "../B/BSAtomic.h"

#include <emmintrin.h>

namespace ConsoleRE
{
	// BSCriticalSection
	BSCriticalSection::BSCriticalSection()
	{
		pthread_mutexattr_t attr;
		if (!scePthreadMutexattrInit(&attr))
		{
			scePthreadMutexattrSettype(&attr, 2);
			scePthreadMutexInit(&m_mutex, &attr, 0LL);
			scePthreadMutexattrDestroy(&attr);
		}
	}

	BSCriticalSection::~BSCriticalSection()
	{
		scePthreadMutexDestroy(&m_mutex);
	}

	// BSEventFlag
	BSEventFlag::BSEventFlag()
	{
		xUtilty::SystemWrapper::CreateEvent(&m_event, "eventflag", 33, 0, 0);
	}

	BSEventFlag::~BSEventFlag()
	{
		xUtilty::SystemWrapper::DeleteEvent(&m_event);
	}

	// BSSemaphoreBase
	BSSemaphoreBase::BSSemaphoreBase() : m_semaphore()
	{
		xUtilty::SystemWrapper::CreateSemaphore(&m_semaphore, "", 2, 0, 40, nullptr);
	}
	
	BSSemaphoreBase::~BSSemaphoreBase()
	{
		xUtilty::SystemWrapper::DeleteSemaphore(m_semaphore);
	}

	// BSSpinLock
	BSSpinLock::BSSpinLock() : m_ThreadID(0), m_LockCount(0)
	{}

	void BSSpinLock::Lock(uint32_t PauseAttempts)
	{
		int sleeptime;

		auto self = pthread_self();
		_mm_lfence();

		if (scePthreadEqual(m_ThreadID, self))
		{
			__sync_add_and_fetch(&m_LockCount, 1);
		}
		else
		{
			uint32_t attempts = 0;
			if (__sync_val_compare_and_swap(&m_LockCount, 0, 1))
			{
				_mm_pause();
				while (__sync_val_compare_and_swap(&m_LockCount, 0, 1))
				{

					if (attempts > kFastSpinThreshold)
					{
						sleeptime = 1000;
					}
					else
					{
						++attempts;
						sleeptime = 0;
					}

					sceKernelUsleep(sleeptime);
				}

				_mm_lfence();
			}

			m_ThreadID = self;
			_mm_sfence();
		}
	}

	void BSSpinLock::Unlock()
	{
		_mm_lfence();
		auto self = pthread_self();

		if (scePthreadEqual(m_ThreadID, self))
		{
			if (m_LockCount == 1)
			{
				m_ThreadID = NULL;
				_mm_lfence();
				__sync_val_compare_and_swap(&m_LockCount, 1, 0);
			}
			else
			{
				__sync_fetch_and_sub(&m_LockCount, 1);
			}
		}
	}
	
	// BSReadWriteLock
	BSReadWriteLock::BSReadWriteLock() : m_ThreadID(0), m_LockCount(0)
	{}

	void BSReadWriteLock::LockForRead()
	{
		using func_t = void(BSReadWriteLock* const);
		Relocation<func_t*> func("", 0xE201F0);
		return func(this);
	}

	void BSReadWriteLock::UnlockForRead()
	{
		using func_t = void(BSReadWriteLock* const);
		Relocation<func_t*> func("", 0xE205A0);
		return func(this);
	}

	void BSReadWriteLock::LockForWrite()
	{
		using func_t = void(BSReadWriteLock* const);
		Relocation<func_t*> func("", 0xE202A0);
		return func(this);
	}

	void BSReadWriteLock::UnlockForWrite()
	{
		using func_t = void(BSReadWriteLock* const);
		Relocation<func_t*> func("", 0xE205B0);
		return func(this);
	}
	
	// BSSpinLockGuard
	BSSpinLockGuard::BSSpinLockGuard(BSSpinLock& a_lock) : m_lock(a_lock)
	{
		m_lock.Lock();
	}

	BSSpinLockGuard::~BSSpinLockGuard()
	{
		m_lock.Unlock();
	}

	// BSReadLockGuard
	BSReadLockGuard::BSReadLockGuard(BSReadWriteLock& a_lock) : m_lock(a_lock)
	{
		m_lock.LockForRead();
	}

	BSReadLockGuard::~BSReadLockGuard()
	{
		m_lock.UnlockForRead();
	}
	
	// BSWriteLockGuard
	BSWriteLockGuard::BSWriteLockGuard(BSReadWriteLock& a_lock) : m_lock(a_lock)
	{
		m_lock.LockForWrite();
	}

	BSWriteLockGuard::~BSWriteLockGuard()
	{
		m_lock.UnlockForWrite();
	}
}