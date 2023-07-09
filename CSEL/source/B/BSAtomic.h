#pragma once

#include <stdint.h>
#include <pthread.h>

namespace ConsoleRE
{
	class BSCriticalSection
	{
	public:
		BSCriticalSection();
		~BSCriticalSection();
	public:
		pthread_mutex_t m_mutex;
	};
	static_assert(sizeof(BSCriticalSection) == 0x8);

	class BSEventFlag
	{
	public:
		BSEventFlag();
		~BSEventFlag();
	public:
		void* m_event;
	};
	static_assert(sizeof(BSEventFlag) == 0x8);

	class BSNonReentrantSpinLock
	{
	public:
		BSNonReentrantSpinLock() = default;
		~BSNonReentrantSpinLock() = default;
	public:
		volatile uint32_t m_lock{ 0 };
	};
	static_assert(sizeof(BSNonReentrantSpinLock) == 0x4);

	class BSSemaphoreBase
	{
	public:
		BSSemaphoreBase();
		~BSSemaphoreBase();
	public:
		void* m_semaphore;
	};
	static_assert(sizeof(BSSemaphoreBase) == 0x8);

	class BSSemaphore : public BSSemaphoreBase
	{
	public:
		BSSemaphore() = default;
		~BSSemaphore() = default;
	};
	static_assert(sizeof(BSSemaphore) == 0x8);

	class BSSpinLock
	{
	public:
		enum
		{
			kFastSpinThreshold = 10000,
		};

		BSSpinLock();

		void Lock(uint32_t PauseAttempts = 0);
		void Unlock();
	public:
		volatile pthread_t	m_ThreadID;		// 0
		volatile int32_t	m_LockCount;	// 8
	};
	static_assert(sizeof(BSSpinLock) == 0x10);

	class BSReadWriteLock
	{
	public:
		enum
		{
			kLockWrite = 0x80000000,
			kLockCountMask = 0xFFFFFFF
		};

		BSReadWriteLock();

		void LockForRead();
		void UnlockForRead();
		void LockForWrite();
		void UnlockForWrite();
	public:
		volatile pthread_t	m_ThreadID;		// 0
		volatile int32_t	m_LockCount;	// 8
	};
	static_assert(sizeof(BSReadWriteLock) == 0x10);

	class BSSpinLockGuard
	{
	public:
		explicit BSSpinLockGuard(BSSpinLock& a_lock);
		~BSSpinLockGuard();
	private:
		BSSpinLock& m_lock;
	};
	static_assert(sizeof(BSSpinLockGuard) == 0x8);

	class BSReadLockGuard
	{
	public:
		explicit BSReadLockGuard(BSReadWriteLock& a_lock);
		~BSReadLockGuard();
	private:
		BSReadWriteLock& m_lock;
	};
	static_assert(sizeof(BSReadLockGuard) == 0x8);

	class BSWriteLockGuard
	{
	public:
		explicit BSWriteLockGuard(BSReadWriteLock& a_lock);
		~BSWriteLockGuard();
	private:
		BSReadWriteLock& m_lock;
	};
	static_assert(sizeof(BSWriteLockGuard) == 0x8);
}