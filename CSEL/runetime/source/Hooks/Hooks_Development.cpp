#include "../../../../OrbisUtil/include/bitFlags.h"
#include "../../../../OrbisUtil/include/PersistentSocketConnection.h"

#include "../../../../OrbisUtil/include/Trampoline.h"
#include "../../../../OrbisUtil/include/Relocation.h"

#include "../Hooks/Hooks_Development.h"

//
#include <sys/socket.h>

#include <stdio.h>
#include <stdint.h>

#include <_fs.h>


namespace Runetime
{
	namespace Hooks
	{
#if false
		Relocation<uintptr_t> _OpenPLTAddress			("", 0x1715D58);
		Relocation<uintptr_t> _sceKernelOpenPLTAddress	("", 0x1716098);
		Relocation<uintptr_t> _statPLTAddress			("", 0x1716878);
		Relocation<uintptr_t> _sceKernelStatPLTAddress	("", 0x17160A8);

		//
		Relocation<uintptr_t> _writePLTAddress			("", 0x1715D68);
		Relocation<uintptr_t> _readPLTAddress			("", 0x1715D78);
		Relocation<uintptr_t> _lseekPLTAddress			("", 0x1715D48);
		Relocation<uintptr_t> _sceKernelReadPLTAddress	("", 0x17169B8);
		Relocation<uintptr_t> _sceKernelLseekPLTAddress	("", 0x17169A8);

		//
		Relocation<uintptr_t> _sceKernelClosePLTAddress	("", 0x1716088);
		Relocation<uintptr_t> _closePLTAddress			("", 0x1715D28);

		enum IORequest
		{
			kNone	= 0,
			kOpen	= 1 << 0,
			kClose	= 1 << 1,
			kStat	= 1 << 2,
			kRead	= 1 << 3,
			kWrite	= 1 << 4,
			kSeek	= 1 << 5,
			kUnkown = 1 << 6,
			kDebug	= 1 << 7,
		};

		int			_openHook(const char* path, int oflag, uint16_t mode)
		{
			//
			int handle = -1;
			
			//
			auto& socket = xUtilty::PersistentSocketConnection::get();

			//
			int request = IORequest::kOpen;

			//
			socket.SendT(&request);

			// 
			socket.SendT(&oflag);
			
			//
			socket.SendT(&mode);

			//
			size_t stringSize = strlen(path) + 1;

			//
			socket.SendT(&stringSize);

			//
			socket.Send(path, stringSize);

			//
			socket.ReciveT(&handle);

			PRINT_FMT("%s, %o, %d / %d", path, oflag, mode, handle);

			if (handle == -1)
			{
				PRINT_POS;

				return open(path, oflag, mode);
			}
			else
			{
				PRINT_POS;

				return handle;
			}
		}

		int			_sceKernelOpenHook(const char *path, int flags, uint16_t mode)
		{
			//
			int handle = -1;

			//
			auto& socket = xUtilty::PersistentSocketConnection::get();

			//
			int request = IORequest::kOpen;

			//
			socket.SendT(&request);

			// 
			socket.SendT(&flags);

			//
			socket.SendT(&mode);

			//
			size_t stringSize = strlen(path) + 1;

			//
			socket.SendT(&stringSize);

			//
			socket.Send(path, stringSize);

			//
			socket.ReciveT(&handle);

			PRINT_FMT("%s, %o, %d / %d", path, flags, mode, handle);

			if (handle == -1)
			{
				PRINT_POS;
				return sceKernelOpen(path, flags, mode);
			}
			else
			{
				PRINT_POS;
				return handle;
			}
		}

		int			_closeHook(int fd)
		{
			int ret = -1;

			//
			auto& socket = xUtilty::PersistentSocketConnection::get();

			//
			int request = IORequest::kClose;

			//
			socket.SendT(&request);

			//
			socket.SendT(&fd);

			//
			socket.ReciveT(&ret);

			PRINT_FMT("%d %d", fd, ret);

			if (ret == -1)
			{
				PRINT_POS;
				return close(fd);
			}
			else
			{
				PRINT_POS;
				return ret;
			}
		}

		int			_sceKernelCloseHook(int d)
		{
			int ret = -1;

			//
			auto& socket = xUtilty::PersistentSocketConnection::get();

			//
			int request = IORequest::kClose;

			//
			socket.SendT(&request);

			//
			socket.SendT(&d);

			//
			socket.ReciveT(&ret);

			PRINT_FMT("%d %d", d, ret);

			if (ret == -1)
			{
				PRINT_POS;
				return sceKernelClose(d);
			}
			else
			{
				PRINT_POS;
				return ret;
			}
		}

		off_t		_lseekHook(int fd, off_t offset, int whence)
		{
			//
			int64_t ret = -1;

			//
			auto& socket = xUtilty::PersistentSocketConnection::get();

			//
			int request = IORequest::kSeek;

			//
			socket.SendT(&request);

			// 
			socket.SendT(&fd);

			//
			socket.SendT(&offset);

			// 
			socket.SendT(&whence);

			//
			socket.ReciveT(&ret);


			PRINT_FMT("0x%lx %d 0x%lx %d", ret, fd, offset, whence);

			if (ret == -1)
			{
				PRINT_POS;
				return lseek(fd, offset, whence);
			}
			else
			{
				PRINT_POS;
				return ret;
			}
		}

		off_t		_sceKernelLseekHook(int fildes, off_t offset, int whence)
		{
			//
			int64_t ret = -1;

			//
			auto& socket = xUtilty::PersistentSocketConnection::get();

			//
			int request = IORequest::kSeek;

			//
			socket.SendT(&request);

			// 
			socket.SendT(&fildes);

			//
			socket.SendT(&offset);

			// 
			socket.SendT(&whence);

			//
			socket.ReciveT(&ret);

			PRINT_FMT("0x%lx %d 0x%lx %d", ret, fildes, offset, whence);

			if (ret == -1)
			{
				PRINT_POS;
				return sceKernelLseek(fildes, offset, whence);
			}
			else
			{
				PRINT_POS;
				return ret;
			}
		}

		ssize_t		_readHook(int fd, void* data, size_t size)
		{
			int ret = -1;

			//
			auto& socket = xUtilty::PersistentSocketConnection::get();

			//
			int request = IORequest::kRead;

			//
			socket.SendT(&request);

			//
			socket.SendT(&fd);

			//
			socket.SendT(&size);

			//
			socket.Recive(data, size);

			//
			socket.ReciveT(&ret);

			PRINT_FMT("%d, %d, %p, 0x%lx", ret, fd, data, size);

			if (ret == -1)
			{
				PRINT_POS;
				return read(fd, data, size);
			}
			else
			{
				PRINT_POS;
				return ret;
			}
		}

		ssize_t		_sceKernelReadHook(int d, void* buf, size_t nbytes)
		{
			int ret;

			//
			auto& socket = xUtilty::PersistentSocketConnection::get();

			//
			int request = IORequest::kRead;

			//
			socket.SendT(&request);

			//
			socket.SendT(&d);

			//
			socket.SendT(&nbytes);

			//
			socket.Recive(buf, nbytes);

			//
			socket.ReciveT(&ret);

			PRINT_FMT("%d, %d, %p, 0x%lx", ret, d, buf, nbytes);

			if (ret == -1)
			{
				PRINT_POS;
				return sceKernelRead(d, buf, nbytes);
			}
			else
			{
				PRINT_POS;
				return ret;
			}
		}
		
		int			_statHook(const char* rdi, struct stat* rsi)
		{
			//
			int ret = -1;

			//
			auto& socket = xUtilty::PersistentSocketConnection::get();

			//
			int request = IORequest::kStat;

			//
			socket.SendT(&request);

			//
			size_t stringSize = strlen(rdi) + 1;

			//
			socket.SendT(&stringSize);

			//
			socket.Send(rdi, stringSize);

			// ???
			socket.ReciveT(rsi);

			//
			socket.ReciveT(&ret);

			PRINT_FMT("%d, %s, %p", ret, rdi, rsi);

			if (ret == -1)
			{
				PRINT_POS;
				return stat(rdi, rsi);
			}
			else
			{
				PRINT_POS;
				return ret;
			}
		}

		int			_sceKernelStatHook(const char* path, struct stat* sb)
		{
			//
			int ret = -1;

			//
			auto& socket = xUtilty::PersistentSocketConnection::get();

			//
			int request = IORequest::kStat;

			//
			socket.SendT(&request);

			//
			size_t stringSize = strlen(path) + 1;

			//
			socket.SendT(&stringSize);

			//
			socket.Send(path, stringSize);

			// ???
			socket.ReciveT(sb);

			//
			socket.ReciveT(&ret);

			PRINT_FMT("%d, %s, %p", ret, path, sb);

			if (ret == -1)
			{
				PRINT_POS;
				return sceKernelStat(path, sb);
			}
			else
			{
				PRINT_POS;
				return ret;
			}
		}

		ssize_t		_writeHook(int fd, const void* data, size_t size)
		{
			PRINT_POS;

			//
			auto& socket = xUtilty::PersistentSocketConnection::get();

			//
			int request = IORequest::kWrite;

			//
			socket.SendT(&request);

			PRINT_POS;

			return write(fd, data, size);
		}
#endif

		void Init()
		{
#if false
			auto& trampoline = xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch);

			// open
			trampoline.write_branch<6>(_OpenPLTAddress.address(),			(uintptr_t)_openHook);
			trampoline.write_branch<6>(_sceKernelOpenPLTAddress.address(),	(uintptr_t)_sceKernelOpenHook);

			// close
			trampoline.write_branch<6>(_sceKernelClosePLTAddress.address(), (uintptr_t)_sceKernelCloseHook);
			trampoline.write_branch<6>(_closePLTAddress.address(),			(uintptr_t)_closeHook);
			
			// stat
			trampoline.write_branch<6>(_statPLTAddress.address(),			(uintptr_t)_statHook);
			trampoline.write_branch<6>(_sceKernelStatPLTAddress.address(),	(uintptr_t)_sceKernelStatHook);

			// read
			trampoline.write_branch<6>(_readPLTAddress.address(),			(uintptr_t)_readHook);
			trampoline.write_branch<6>(_sceKernelReadPLTAddress.address(),	(uintptr_t)_sceKernelReadHook);

			// lseek
			trampoline.write_branch<6>(_lseekPLTAddress.address(),			(uintptr_t)_lseekHook);
			trampoline.write_branch<6>(_sceKernelLseekPLTAddress.address(),	(uintptr_t)_sceKernelLseekHook);

			//
			trampoline.write_branch<6>(_writePLTAddress.address(),			(uintptr_t)_writeHook);
#endif
		}
	}
}