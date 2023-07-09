#pragma once

/* WIP (disable code gen) */
namespace Runetime
{
	namespace Hooks
	{
		//
		int			_openHook(const char* path, int oflag, uint16_t mode);
		int			_sceKernelOpenHook(const char *path, int flags, mode_t mode);

		int			_closeHook(int fd);
		int			_sceKernelCloseHook(int d);


		int			_statHook(const char* rdi, struct stat* rsi);
		int			_sceKernelStatHook(const char* path, struct stat* sb);

		ssize_t		_writeHook(int fd, const void* data, size_t size);
		ssize_t		_readHook(int fd, void* data, size_t size);
		off_t		_lseekHook(int fd, off_t offset, int whence);
		ssize_t		_sceKernelReadHook(int d, void* buf, size_t nbytes);
		off_t		_sceKernelLseekHook(int fildes, off_t offset, int whence);
		//




		//
		void Init();
	}
}