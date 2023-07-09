#include "../../../../OrbisUtil/include/Relocation.h"
#include "../../../../OrbisUtil/include/Logger.h"
#include "../../../../OrbisUtil/include/INIHandler.h"
#include "../../../../OrbisUtil/include/Trampoline.h"
#include "../../../../OrbisUtil/include/Macro.h"
#include "../../../../OrbisUtil/include/SystemWrapper.h"
#include "../../../../OrbisUtil/include/FileSystem.h"
#include "../../../../OrbisUtil/include/Macro.h"
#include "../../../../OrbisUtil/include/FramerateTracker.h"
#include "../../../../OrbisUtil/include/OrbisSFOHandler.h"
#include "../../../../OrbisUtil/include/Streams/IFIleStream.h"
#include "../../../../OrbisUtil/include/Streams/IMemoryStream.h"
#include "../../../../OrbisUtil/Third-Party/herumi/xbayk/6.00/xbyak.h"

//
#include "../../Internal/Interfaces/SerializationInterface/Serialization/Serialization.h"

#include "../Hooks/Hooks_Orbis.h"

#if defined(__OPENORBIS__)
#define submitAndFlipCommandBuffers_ sceGnmSubmitAndFlipCommandBuffers
#include <orbis/NpManager.h>
#include <orbis/VideoOut.h>
#include <orbis/SaveData.h>
#include <orbis/Pad.h>
#include <orbis/NpTrophy.h>
#include <orbis/libkernel.h>
#include <orbis/Http.h>
#include <orbis/GnmDriver.h>
#include <dirent.h>

typedef OrbisSaveDataMount2		     SceSaveDataMount2;
typedef OrbisSaveDataMountResult     SceSaveDataMountResult;
typedef OrbisVideoOutBufferAttribute SceVideoOutBufferAttribute;
typedef OrbisSaveDataMountPoint		 SceSaveDataMountPoint;
typedef OrbisPadData				 ScePadData;
typedef void ScePadOpenParam;
typedef OrbisNpOnlineId				 SceNpOnlineId;
#elif defined(__ORBIS__)
#define submitAndFlipCommandBuffers_ sce::Gnm::submitAndFlipCommandBuffers
#include <fios2.h>
#include <video_out.h>
#include <save_data.h>
#include <pad.h>
#include <np.h>
#include <kernel.h>
#include <np.h>
#include <libhttp.h>
#include <gpu_address.h>
#include <gnmx.h>
#include <gnm.h>
#include <razorcpu.h>
#include <razorcpu_debug.h>
#include <sys\dirent.h>
#endif

#include <stdio.h>
#include <stdlib.h>

namespace Runetime
{
	namespace Hooks
	{
		SceSaveDataStorage	   _SceSaveDataStorage;
		SceVideoOutDataStorage _SceVideoOutDataStorage;
		ScePadDataStorage	   _ScePadDataStorage;
		SceTrophyStorage	   _SceTrophyStorage;

		// IO
		Relocation<uintptr_t> OpenPLTAddress("open:PLT",																								0x1715D58);
		Relocation<uintptr_t> sceKernelOpenPLTAddress("sceKernelOpen:PLT",																				0x1716098);

		// SaveData
		Relocation<uintptr_t> sceSaveDataMount2PLTAddress("sceSaveDataMount2:PLT",																		0x1717218);
		Relocation<uintptr_t> sceSaveDataUmountPLTAddress("sceSaveDataUmount:PLT",																		0x1717258);

		// VideoOut
		Relocation<uintptr_t> sceGnmSubmitAndFlipCommandBuffersPLTAddress("sceGnmSubmitAndFlipCommandBuffers:PLT",										0x1717448);
		Relocation<uintptr_t> sceVideoOutOpenPLTAddress("sceVideoOutOpen:PLT",																			0x1716658);
		Relocation<uintptr_t> sceVideoOutSetFlipRatePLTAddress("sceVideoOutSetFlipRate:PLT",															0x1716688);
		Relocation<uintptr_t> sceVideoOutSetBufferAttributePLTAddress("sceVideoOutSetBufferAttribute:PLT",												0x1716678);
		Relocation<uintptr_t> sceVideoOutRegisterBuffersPLTAddress("sceVideoOutRegisterBuffers:PLT",													0x1716668);

		// scePad
		Relocation<uintptr_t> scePadReadStatePLTAddress("scePadReadState:PLT",																			0x17161E8);
		Relocation<uintptr_t> scePadOpenPLTAddress("scePadOpen:PLT",																					0x17161D8);

		// sceNP
		Relocation<uintptr_t> sceNpTrophyCreateContextPLTAddress		("sceNpTrophyCreateContext:PLT",												0x1716EB8);
		Relocation<uintptr_t> sceNpTrophyCreateHandlePLTAddress			("sceNpTrophyCreateHandle:PLT",													0x1716EC8);
		Relocation<uintptr_t> sceNpGetOnlineIdPLTAddress				("sceNpGetOnlineId:PLT",														0x17169E8);
		Relocation<uintptr_t> sceNpSetContentRestrictionPLTAddress		("sceNpSetContentRestriction:PLT",												0x1716FA8);
		Relocation<uintptr_t> sceNpPollAsyncPLTAddress					("sceNpPollAsync:PLT",															0x1716F98);
		Relocation<uintptr_t> sceNpDeleteRequestPLTAddress				("sceNpDeleteRequest:PLT",														0x1716F78);
		Relocation<uintptr_t> sceNpCreateAsyncRequestPLTAddress			("sceNpCreateAsyncRequest:PLT",													0x1716F68);
		Relocation<uintptr_t> sceNpAuthPollAsyncPLTAddress				("sceNpAuthPollAsync:PLT",														0x1716F48);
		Relocation<uintptr_t> sceNpAuthDeleteRequestPLTAddress			("sceNpAuthDeleteRequest:PLT",													0x1716AE8);
		Relocation<uintptr_t> sceNpAuthCreateRequestPLTAddress			("sceNpAuthCreateRequest:PLT",													0x1716AD8);
		Relocation<uintptr_t> sceNpAuthCreateAsyncRequestPLTAddress		("sceNpAuthCreateAsyncRequest:PLT",												0x1716F38);
		Relocation<uintptr_t> sceNpCheckNpAvailabilityPLTAddress		("sceNpCheckNpAvailability:PLT",		"sceNpCheckNpAvailabilityA:PLT",		0x1716F58);
		Relocation<uintptr_t> sceNpGetAccountCountryAPLTAddress			("sceNpGetAccountCountry:PLT",			"sceNpGetAccountCountryA:PLT",			0x17169D8);
		Relocation<uintptr_t> sceNpGetParentalControlInfoAPLTAddress	("sceNpGetParentalControlInfo:PLT",		"sceNpGetParentalControlInfoA:PLT",		0x1716F88);
		Relocation<uintptr_t> sceNpAuthGetAuthorizationCodePLTAddress	("sceNpAuthGetAuthorizationCode:PLT",	"sceNpAuthGetAuthorizationCodeA:PLT",	0x1716AF8);

		// http/net
		Relocation<uintptr_t> sceHttpCreateConnectionPLTAddress			("sceHttpCreateConnection:PLT",													0x1716C18);
		Relocation<uintptr_t> sceHttpReadDataPLTAddress					("sceHttpReadData:PLT",															0x1716BD8);
		Relocation<uintptr_t> sceHttpSendRequestPLTAddress				("sceHttpSendRequest:PLT",														0x1716BE8);
		Relocation<uintptr_t> sceNetSendPLTAddress						("sceNetSend:PLT",																0x1715E78);

		// pthread
		Relocation<uintptr_t> scePthreadCreatePLTAddress				("scePthreadCreate:PLT",														0x1716168);

		// kernel.
		Relocation<uintptr_t> sceKernelStatPLTAddress					("sceKernelStat:PLT",															0x17160A8);

		// libc
		Relocation<uintptr_t> statPLTAddress							("stat:PLT",																	0x1716878);

		Relocation<uintptr_t> fopenPLTAddress							("",																			0x1716078);
		Relocation<uintptr_t> fopen_sPLTAddress							("",																			0x17162D8);

		// fios2
		Relocation<uintptr_t> sceFiosDHOpenPLTAddress					("sceFiosDHOpen:PLT",															0x17163E8);
		Relocation<uintptr_t> sceFiosDHOpenSyncPLTAddress				("sceFiosDHOpenSync:PLT",														0x17163F8);
		Relocation<uintptr_t> sceFiosFHOpenSyncPLTAddress				("sceFiosFHOpenSync:PLT",														0x1716498);
		Relocation<uintptr_t> sceFiosFHOpenWithModeSyncPLTAddress		("sceFiosFHOpenWithModeSync:PLT",												0x17164A8);


		Relocation<uintptr_t> writePLTAddress							("", 0x1715D68);
		Relocation<uintptr_t> readPLTAddress							("", 0x1715D78);
		Relocation<uintptr_t> lseekPLTAddress							("", 0x1715D48);
		Relocation<uintptr_t> sceKernelReadPLTAddress					("", 0x17169B8);
		Relocation<uintptr_t> sceKernelLseekPLTAddress					("", 0x17169A8);

		// funcs.
		Relocation<int(**) (int, const NpOnlineId*, void*)>								_sceNpCheckNpAvailability;
		Relocation<int(**) (int32_t*, NpCountryCode*)>									_sceNpGetAccountCountry;
		Relocation<int(**) (int, const void*, NpAuthorizationCode*, int*)>				_sceNpAuthGetAuthorizationCode;
		Relocation<int(**) (int, const NpOnlineId*, int8_t*, NpParentalControlInfo*)>	_sceNpGetParentalControlInfo;
		//

		int			openHook(const char* path, int oflag, uint16_t mode)
		{
#if NDEBUG
			if (xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions()->IsDebugMode)
			{
#endif
				xUtilty::Log::GetSingleton(xUtilty::Log::LoggerInstance::kInputOutputLog)->Write(xUtilty::Log::logLevel::kTrace, "Open(%s, %d, %o)", path, oflag, mode);
#if NDEBUG
			}
#endif

			return open(path, oflag, mode);
		}

		int			statHook(const char* rdi, struct stat* rsi)
		{
#if NDEBUG
			if (xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions()->IsDebugMode)
			{
#endif
				xUtilty::Log::GetSingleton(xUtilty::Log::LoggerInstance::kInputOutputLog)->Write(xUtilty::Log::logLevel::kTrace, "stat(%s, %p", rdi, rsi);
#if NDEBUG
			}
#endif
			return stat(rdi, rsi);
		}

		int			sceKernelOpenHook(const char *path, int flags, mode_t mode)
		{
#if NDEBUG
			if (xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions()->IsDebugMode)
			{
#endif
				xUtilty::Log::GetSingleton(xUtilty::Log::LoggerInstance::kInputOutputLog)->Write(xUtilty::Log::logLevel::kTrace, "sceKernelOpen(%s, %d, %o)", path, flags, mode);
#if NDEBUG
			}
#endif
			return sceKernelOpen(path, flags, mode);
		}

		int			sceKernelStatHook(const char* path, struct stat* sb)
		{
#if NDEBUG
			if (xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions()->IsDebugMode)
			{
#endif
				xUtilty::Log::GetSingleton(xUtilty::Log::LoggerInstance::kInputOutputLog)->Write(xUtilty::Log::logLevel::kTrace, "sceKernelStat(%s, %p)", path, sb);
#if NDEBUG
			}
#endif
			return sceKernelStat(path, sb);

		}

		ssize_t		writeHook(int fd, const void* data, size_t size)
		{
#if NDEBUG
			if (xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions()->IsDebugMode)
			{
#endif
				xUtilty::Log::GetSingleton(xUtilty::Log::LoggerInstance::kInputOutputLog)->Write(xUtilty::Log::logLevel::kTrace, "write requested");
#if NDEBUG
			}
#endif
			return write(fd, data, size);
		}

		ssize_t		readHook(int fd, void* data, size_t size)
		{
#if NDEBUG
			if (xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions()->IsDebugMode)
			{
#endif
				xUtilty::Log::GetSingleton(xUtilty::Log::LoggerInstance::kInputOutputLog)->Write(xUtilty::Log::logLevel::kTrace, "read requested");
#if NDEBUG
			}
#endif
			return read(fd, data, size);
		}

		off_t		lseekHook(int fd, off_t offset, int whence)
		{
#if NDEBUG
			if (xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions()->IsDebugMode)
			{
#endif
				xUtilty::Log::GetSingleton(xUtilty::Log::LoggerInstance::kInputOutputLog)->Write(xUtilty::Log::logLevel::kTrace, "lseek requested");
#if NDEBUG
			}
#endif
			return lseek(fd, offset, whence);
		}

		ssize_t		sceKernelReadHook(int d, void* buf, size_t nbytes)
		{
#if NDEBUG
			if (xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions()->IsDebugMode)
			{
#endif
				xUtilty::Log::GetSingleton(xUtilty::Log::LoggerInstance::kInputOutputLog)->Write(xUtilty::Log::logLevel::kTrace, "kernelRead requested");
#if NDEBUG
			}
#endif
			return sceKernelRead(d, buf, nbytes);
		}

		off_t		sceKernelLseekHook(int fildes, off_t offset, int whence)
		{
#if NDEBUG
			if (xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions()->IsDebugMode)
			{
#endif
				xUtilty::Log::GetSingleton(xUtilty::Log::LoggerInstance::kInputOutputLog)->Write(xUtilty::Log::logLevel::kTrace, "kernelLseek requested");
#if NDEBUG
			}
#endif
			sceKernelLseek(fildes, offset, whence);
		}

#if __ORBIS__
		FILE*	fopenHook(const char *filename, const char *mode)
		{
#if NDEBUG
			if (xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions()->IsDebugMode)
			{
#endif
				xUtilty::Log::GetSingleton(xUtilty::Log::LoggerInstance::kInputOutputLog)->Write(xUtilty::Log::logLevel::kTrace, "fopen(%s, %s)", filename, mode);
#if NDEBUG
		}
#endif
			return fopen(filename, mode);
		}

		errno_t fopen_sHook(FILE** pFile, const char* filename, const char* mode)
		{
#if NDEBUG
			if (xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions()->IsDebugMode)
			{
#endif
				xUtilty::Log::GetSingleton(xUtilty::Log::LoggerInstance::kInputOutputLog)->Write(xUtilty::Log::logLevel::kTrace, "fopen_s(%p, %s, %s)", pFile, filename, mode);
#if NDEBUG
			}
#endif
			return fopen_s(pFile, filename, mode);
		}

		int     sceFiosDHOpenSyncHook(const SceFiosOpAttr* pAttr, SceFiosDH* pOutDH, const char* pPath, SceFiosBuffer buf)
		{
#if NDEBUG
			if (xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions()->IsDebugMode)
			{
#endif
				xUtilty::Log::GetSingleton(xUtilty::Log::LoggerInstance::kInputOutputLog)->Write(xUtilty::Log::logLevel::kTrace, "sceFiosDHOpenSync(%p, %p, %s, ??)", pAttr, pOutDH, pPath);
#if NDEBUG	
		}
#endif
			return sceFiosDHOpenSync(pAttr, pOutDH, pPath, buf);
		}

		int32_t sceFiosDHOpenHook(const SceFiosOpAttr* pAttr, SceFiosDH* pOutDH, const char* pPath, SceFiosBuffer buf)
		{
#if NDEBUG
			if (xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions()->IsDebugMode)
			{
#endif
				xUtilty::Log::GetSingleton(xUtilty::Log::LoggerInstance::kInputOutputLog)->Write(xUtilty::Log::logLevel::kTrace, "sceFiosDHOpen(%p, %p, %s, ??)", pAttr, pOutDH, pPath);
#if NDEBUG
			}
#endif
			return sceFiosDHOpen(pAttr, pOutDH, pPath, buf);
		}

		int		sceFiosFHOpenSyncHook(const SceFiosOpAttr* pAttr, SceFiosFH* pOutFH, const char* pPath, const SceFiosOpenParams* pOpenParams)
		{
#if NDEBUG
			if (xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions()->IsDebugMode)
			{
#endif
				xUtilty::Log::GetSingleton(xUtilty::Log::LoggerInstance::kInputOutputLog)->Write(xUtilty::Log::logLevel::kTrace, "sceFiosFHOpenSync(%p, %p, %s, %p)", pAttr, pOutFH, pPath, pOpenParams);

				// debug.
				if (!strcasecmp(pPath, "/app0/data/SCRIPTS/kpscriptactivator.pex"))
				{
					pPath = "/download0/data/Scripts/kpscriptactivator.pex";
					xUtilty::Log::GetSingleton(xUtilty::Log::LoggerInstance::kInputOutputLog)->Write(xUtilty::Log::logLevel::kTrace, "sceFiosFHOpenSync called with %s new path -> %s", "/app0/data/SCRIPTS/kpscriptactivator.pex", pPath);
				}
#if NDEBUG
			}
#endif
			return sceFiosFHOpenSync(pAttr, pOutFH, pPath, pOpenParams);

		}

		int		sceFiosFHOpenWithModeSyncHook(const SceFiosOpAttr *pAttr, SceFiosFH *pOutFH, const char *pPath, const SceFiosOpenParams *pOpenParams, int32_t nativeMode)
		{
#if NDEBUG
			if (xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions()->IsDebugMode)
			{
#endif
				xUtilty::Log::GetSingleton(xUtilty::Log::LoggerInstance::kInputOutputLog)->Write(xUtilty::Log::logLevel::kTrace, "sceFiosFHOpenWithModeSync(%p, %p, %s, %p, %d)", pAttr, pOutFH, pPath, pOpenParams, nativeMode);
#if NDEBUG	
		}
#endif
			return sceFiosFHOpenWithModeSync(pAttr, pOutFH, pPath, pOpenParams, nativeMode);
		}
#endif

#pragma region _IMPL_
		void	SetButtonID(int32_t ID)
		{
			if (ID == 0)
			{
				return;
			}

			_ScePadDataStorage.PreviousButton = _ScePadDataStorage.CurrentButton;
			_ScePadDataStorage.CurrentButton = ID;
		}

		void	HandleSerial()
		{
			/*
			xUtilty::IFileStream filestrea;
			
			auto& sh	= Serialization::SerializationHandler::get();
			auto& flags	= Serialization::SerializationHandler::GetBitFlags();
			auto ms		= sh.GetMemoryStream();
			
			// 
			auto newpos = ms->Seek(0, SEEK_SET);

#if _DEBUG
			auto curpos = ms->GetStreamPosition();
			PRINT_FMT("%p / %p [%d] : %d / %d", ms, ms->ToArray(), ms->ToArray()[0], curpos, newpos);
#endif

			uint8_t vaildFlag = 0;
			if (ms->Read((void*)&vaildFlag, sizeof(uint8_t)) != sizeof(uint8_t) && vaildFlag != 0xFF)
			{
				xUtilty::KernelPrintOut("SerialFlag not set... aborting. [%d]", vaildFlag);
				return;
			}
			
			//
			ms->Seek(1, SEEK_SET);

			// loading a save and serial file already exists? import.
			if (flags.TestFlags(Serialization::SerializationHandler::kFlags::kFlagRead))
			{	
				// "/savedata0/SAVEDATA.DAT.cosave"
				filestrea.Open(Serialization::SerializationHandler::SAVEPATH, xUtilty::IFileStream::kFlags::kFlagReadMode);
				if (filestrea.IsVaild())
				{
					if (ms->Resize(filestrea.GetStreamLength(), ms->GetStreamLength()))
					{
						filestrea.Read(ms->ToArray(), ms->GetStreamLength());
						filestrea.Dispose();
					}
				}
			}
			
			// new save/auto-save? create and write it to disk.
			else if (flags.TestFlags(Serialization::SerializationHandler::kFlags::kFlagWrite))
			{	
				// "/savedata0/SAVEDATA.DAT.cosave"
				filestrea.Open(Serialization::SerializationHandler::SAVEPATH, xUtilty::IFileStream::kFlags::kFlagReadWriteMode | xUtilty::IFileStream::kFlags::kFlagCreate);
				if (filestrea.IsVaild())
				{
					filestrea.Write(ms->ToArray(), ms->GetStreamLength());
					filestrea.Flush();
					filestrea.Dispose();
				}
			}
			else
			{
				PRINT_FMT("%d", flags.GetFlags());
			}
			*/
		}

		void	HandleCompression()
		{			
			/*
			IMemoryStream uncompressedbuffer(false);
			IMemoryStream compressedbuffer(false);
			
			IFileStream		file("/savedata0/SAVEDATA.DAT", IFileStream::kFlags::kFlagReadWriteMode);
			if (file.IsVaild())
			{
				SaveGame::SAVE	save;
				uint32_t		magic;
				unsigned long	size;
			
				if (file.Read(&magic, sizeof(uint32_t)) == 4)
				{
					// compressed
					if (magic == __bswap32('TESC'))
					{
						file.Seek(0, SEEK_SET);
						file.Read(&save, sizeof(SaveGame::SAVE));
			
						compressedbuffer.Initialize(save.CompressedSize);
						uncompressedbuffer.Initialize(save.OrginalSize);
			
						file.Read(compressedbuffer.ToArray(), save.CompressedSize);
			
						size = save.OrginalSize;
						int ret = SystemWrapper::uncompress(uncompressedbuffer.ToArray(), &size, compressedbuffer.ToArray(), save.CompressedSize);
			
						file.Seek(0, SEEK_SET);
						file.Truncate(0);
						file.Write(uncompressedbuffer.ToArray(), size);
					}
			
					// uncompressed.
					else
					{
						size = (file.GetStreamLength() * 1.1) + 12;
			
						uncompressedbuffer.Initialize(file.GetStreamLength());
						compressedbuffer.Initialize(size);
			
						file.Seek(0, SEEK_SET);
						file.Read(uncompressedbuffer.ToArray(), file.GetStreamLength());
						file.Seek(0, SEEK_SET);
			
						int ret = SystemWrapper::compress(compressedbuffer.ToArray(), &size, uncompressedbuffer.ToArray(), file.GetStreamLength());
			
						save.Magic = __bswap32('TESC');
						save.Version = 1;
						save.OrginalSize = file.GetStreamLength();
						save.CompressedSize = size;
			
						file.Truncate(0);
						file.Write(&save, sizeof(save));
						file.Write(compressedbuffer.ToArray(), size);
					}
				}
			}
			
			uncompressedbuffer.Dispose();
			compressedbuffer.Dispose();
			file.Dispose();
			*/
		}

		void	HandleSaveCopy(char* a_dstdir, char* a_basedir)
		{
			SceRtcDateTime now;
			char buffer[260] { 0 };

			for (auto& s_enties : xUtilty::FileSystem::GetDirectoryEntries(a_basedir, nullptr, false, xUtilty::FileSystem::Full, true))
			{
				if (s_enties.m_filetype == DT_DIR)
				{
					HandleSaveCopy(a_dstdir, (char*)s_enties.m_filename.c_str());
				}
				else if (s_enties.m_filetype == DT_REG)
				{
					xUtilty::SystemWrapper::UpdateRTC(&now);
					sprintf(buffer, "%s/%d%d%d%d%d/%s", a_dstdir, now.month, now.day, now.year, now.hour, now.minute, s_enties.m_filename.c_str());
					xUtilty::FileSystem::CreateDirectoryPath(buffer);

					xUtilty::IFileStream srcfileStream((char*)s_enties.m_filename.c_str(), xUtilty::IFileStream::kFlags::kFlagReadMode);
					xUtilty::IFileStream dstfileStream(buffer, xUtilty::IFileStream::kFlags::kFlagReadWriteMode | xUtilty::IFileStream::kFlags::kFlagCreate | xUtilty::IFileStream::kFlags::kFlagTruncate);

					if (!srcfileStream.IsVaild() || !dstfileStream.IsVaild())
						return;

					while (srcfileStream.GetStreamPosition() != srcfileStream.GetStreamLength())
					{
						int8_t val;
						srcfileStream.Read(&val, sizeof(int8_t));
						dstfileStream.Write(&val, sizeof(int8_t));
					}
				}
			}
		}
#pragma endregion


		int32_t sceSaveDataMount2Hook(SceSaveDataMount2* mount, SceSaveDataMountResult* mountResult)
		{
			_SceSaveDataStorage.SaveDataMountMode = mount->mountMode;
			_SceSaveDataStorage.SaveDataRequestedBlockSize = mount->blocks;

#if _DEBUG
			//
			xUtilty::BitFlags<uint32_t> flags = mount->mountMode;

			// check for read flag
			if (flags.TestFlags(0x00000001))
			{
				// remove the read only flag.
				flags.ClearFlags(0x00000001);
			}

			// add the read write flag.
			flags.SetFlags(0x00000002);

			// swap flags
			mount->mountMode = flags.GetFlags();

			// swap
			_SceSaveDataStorage.SaveDataMountMode2 = flags;

			//
			int32_t ret = sceSaveDataMount2(mount, mountResult);
#elif NDEBUG
			int32_t ret = sceSaveDataMount2(mount, mountResult);
#endif

#if _DEBUG
			xUtilty::KernelPrintOut("sceSaveDataMount2 has been called! [%s, %d, %d]", mount->dirName, _SceSaveDataStorage.SaveDataMountMode.GetFlags(), _SceSaveDataStorage.SaveDataMountMode2.GetFlags());
#elif NDEBUG
			if (xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions()->IsDebugMode)
			{
				xUtilty::KernelPrintOut("sceSaveDataMount2 has been called! [%s, %d, %d]", mount->dirName, _SceSaveDataStorage.SaveDataMountMode.GetFlags(), _SceSaveDataStorage.SaveDataMountMode2.GetFlags());
			}
#endif
			_SceSaveDataStorage.SaveDataRequiredBlockSize = mountResult->requiredBlocks;

			return ret;

		}

		int32_t sceSaveDataUmountHook(SceSaveDataMountPoint* mountPoint)
		{
			auto options = xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions();
		
#if _DEBUG
			xUtilty::KernelPrintOut("sceSaveDataUmount has been called! [%s / %d / %d / %d]", mountPoint->data, Serialization::SerializationHandler::get().GetBitFlags().GetFlags(), _SceSaveDataStorage.SaveDataMountMode.GetFlags(), _SceSaveDataStorage.SaveDataMountMode2.GetFlags());
#elif NDEBUG
			if (options->IsDebugMode)
			{
				xUtilty::KernelPrintOut("sceSaveDataUmount has been called! [%s / %d / %d / %d]", mountPoint->data, Serialization::SerializationHandler::get().GetBitFlags().GetFlags(), _SceSaveDataStorage.SaveDataMountMode.GetFlags(), _SceSaveDataStorage.SaveDataMountMode2.GetFlags());
			}
#endif
			if (options->AutoDumpSaveData)
			{
				char buffer[260] { 0 };
				xUtilty::FileSystem::CreateFullPath(buffer, options->SaveDataDumpDirType, options->SaveDataDumpdir);
				xUtilty::FileSystem::CreateDirectoryPath(buffer);

				if (xUtilty::FileSystem::PathExists(xUtilty::FileSystem::Full, buffer, true))
				{
					HandleSaveCopy(buffer, mountPoint->data);
				}
			}

			/*
#if __ORBIS__ && _DEBUG
		
			xUtilty::IFileStream localStreams[2];
	
			localStreams[0].Open("/savedata0/SAVEDATA.DAT", xUtilty::IStream::kFlags::kFlagReadMode);
			localStreams[1].Open("/savedata0/SAVEDATA.DAT.cosave", xUtilty::IStream::kFlags::kFlagReadMode);

			auto* log = xUtilty::Log::GetSingleton(xUtilty::Log::kNetwork);

			log->Send(xUtilty::Log::logLevel::kNone,

				"==================START============================"

"\nDefault SaveData info:\n"
				"\tFlags:\t\t\t\t\t\t%d\n"
				"\tRequested Block Size:\t\t%d\n"
				"\tRequired Block Size:\t\t%d\n"
				"\tMount Name:\t\t\t\t\t\"%s\"\n"
				"\tSave Size:\t\t\t\t\t%2.1f MB(0x%LX Bytes)\n"
				"\tCo-Save Size:\t\t\t\t%2.1f(0x%LX Bytes)\n"
"BitWise Flags:\n"
				"\tREAD ONLY:\t\t\t\t\t%s\n"
				"\tREAD/WRITE:\t\t\t\t\t%s\n"
				"\tCREATE:\t\t\t\t\t\t%s\n"
				"\tDESTRUCT OFF:\t\t\t\t%s\n"
				"\tCOPY ICON:\t\t\t\t\t%s\n"
				"\tCREATE 2:\t\t\t\t\t%s\n"

"\nNew SaveData info:\n"
				"\tFlags:\t\t\t\t\t\t%d\n"
				"\tRequested Block Size:\t\t%d\n"
				"\tRequired Block Size:\t\t%d\n"
				"\tMount Name:\t\t\t\t\t\"%s\"\n"
				"\tSave Size:\t\t\t\t\t%2.1f MB(0x%LX)\n"
				"\tCo-Save Size:\t\t\t\t%2.1f MB(0x%LX)\n"
"BitWise Flags:\n"
				"\tREAD ONLY:\t\t\t\t\t%s\n"
				"\tREAD/WRITE:\t\t\t\t\t%s\n"
				"\tCREATE:\t\t\t\t\t\t%s\n"
				"\tDESTRUCT OFF:\t\t\t\t%s\n"
				"\tCOPY ICON:\t\t\t\t\t%s\n"
				"\tCREATE 2:\t\t\t\t\t%s\n"

				"==================END==============================",

				// default:
				_SceSaveDataStorage.SaveDataMountMode.GetFlags(), // %d

				_SceSaveDataStorage.SaveDataRequestedBlockSize, // %d

				_SceSaveDataStorage.SaveDataRequiredBlockSize, // %d

				mountPoint->data, // %s

				localStreams[0].GetStreamCapacity() / 1000.0f / 1000.0f, // %2.1f

				localStreams[0].GetStreamCapacity(), // 0x%lx

				localStreams[1].GetStreamCapacity() / 1000.0f / 1000.0f, // %2.1f

				localStreams[1].GetStreamCapacity(), // 0x%lx

				BOOL_TYPE_AS_STRING(_SceSaveDataStorage.SaveDataMountMode.TestFlags(SCE_SAVE_DATA_MOUNT_MODE_RDONLY)), // %s
				BOOL_TYPE_AS_STRING(_SceSaveDataStorage.SaveDataMountMode.TestFlags(SCE_SAVE_DATA_MOUNT_MODE_RDWR)), // %s
				BOOL_TYPE_AS_STRING(_SceSaveDataStorage.SaveDataMountMode.TestFlags(SCE_SAVE_DATA_MOUNT_MODE_CREATE)), // %s
				BOOL_TYPE_AS_STRING(_SceSaveDataStorage.SaveDataMountMode.TestFlags(SCE_SAVE_DATA_MOUNT_MODE_DESTRUCT_OFF)), // %s
				BOOL_TYPE_AS_STRING(_SceSaveDataStorage.SaveDataMountMode.TestFlags(SCE_SAVE_DATA_MOUNT_MODE_COPY_ICON)), // %s
				BOOL_TYPE_AS_STRING(_SceSaveDataStorage.SaveDataMountMode.TestFlags(SCE_SAVE_DATA_MOUNT_MODE_CREATE2)), // %s

				// new:
				_SceSaveDataStorage.SaveDataMountMode2.GetFlags(), // %d

				_SceSaveDataStorage.SaveDataRequestedBlockSize, // %d

				_SceSaveDataStorage.SaveDataRequiredBlockSize, // %d

				mountPoint->data, // %s

				localStreams[0].GetStreamCapacity() / 1000.0f / 1000.0f, // %2.1f

				localStreams[0].GetStreamCapacity(), // 0x%lx

				localStreams[1].GetStreamCapacity() / 1000.0f / 1000.0f, // %2.1f

				localStreams[1].GetStreamCapacity(), // 0x%lx

				BOOL_TYPE_AS_STRING(_SceSaveDataStorage.SaveDataMountMode2.TestFlags(SCE_SAVE_DATA_MOUNT_MODE_RDONLY)), // %s
				BOOL_TYPE_AS_STRING(_SceSaveDataStorage.SaveDataMountMode2.TestFlags(SCE_SAVE_DATA_MOUNT_MODE_RDWR)), // %s
				BOOL_TYPE_AS_STRING(_SceSaveDataStorage.SaveDataMountMode2.TestFlags(SCE_SAVE_DATA_MOUNT_MODE_CREATE)), // %s
				BOOL_TYPE_AS_STRING(_SceSaveDataStorage.SaveDataMountMode2.TestFlags(SCE_SAVE_DATA_MOUNT_MODE_DESTRUCT_OFF)), // %s
				BOOL_TYPE_AS_STRING(_SceSaveDataStorage.SaveDataMountMode2.TestFlags(SCE_SAVE_DATA_MOUNT_MODE_COPY_ICON)), // %s
				BOOL_TYPE_AS_STRING(_SceSaveDataStorage.SaveDataMountMode2.TestFlags(SCE_SAVE_DATA_MOUNT_MODE_CREATE2)) // %s

			);

			// close all the file streams.
			for (auto& filestream : localStreams)
			{
				filestream.Dispose();
			}

#if _DEBUG
			// confirm savedata is RW
			if (_SceSaveDataStorage.SaveDataMountMode2.TestFlags(0x00000002)) // RW
			{
				HandleSerial();
			}
#endif

#endif
			*/

			sceKernelSleep(xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions()->SaveUnmountSleep);
			return sceSaveDataUmount(mountPoint);
		}

		int32_t sceVideoOutOpenHook(int32_t userId, int32_t type, int32_t index, void *param)
		{
			int32_t ret = sceVideoOutOpen(userId, type, index, param);

			_SceVideoOutDataStorage.UserID = userId;
			_SceVideoOutDataStorage.VideobusType = type;
			_SceVideoOutDataStorage.VideoEnabled = true;

			return ret;
		}

		int32_t sceVideoOutSetFlipRateHook(int32_t handle, int32_t rate)
		{
			auto attr = xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions();
			auto log = xUtilty::Log::GetSingleton();

			switch (attr->FlipRate)
			{
			case 0:
				log->Write(xUtilty::Log::logLevel::kInfo, "Flip Rate: %d(%s)", attr->FlipRate, "60 FPS");
				break;
			case 1:
				log->Write(xUtilty::Log::logLevel::kInfo, "Flip Rate: %d(%s)", attr->FlipRate, "30 FPS");
				break;
			case 2:
				log->Write(xUtilty::Log::logLevel::kInfo, "Flip Rate: %d(%s)", attr->FlipRate, "20 FPS");
				break;
			default:
				log->Write(xUtilty::Log::logLevel::kWarning, "unsupported flip-rate, deafulting to 60 FPS.");
				attr->FlipRate = 0;
			}

			int32_t ret = sceVideoOutSetFlipRate(handle, attr->FlipRate);
			_SceVideoOutDataStorage.OrginalFlipRate = rate;
			return ret;
		}

		void	sceVideoOutSetBufferAttributeHook(SceVideoOutBufferAttribute* attribute, uint32_t pixelFormat, uint32_t tilingMode, uint32_t aspectRatio, uint32_t width, uint32_t height, uint32_t pitchInPixel)
		{
			auto attr = xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions();

			if (attr->IsDebugMode)
			{
				xUtilty::Log::GetSingleton(xUtilty::Log::LoggerInstance::kModuleLog)->Write(xUtilty::Log::logLevel::kDebug, "sceVideoOutSetBufferAttribute invoked: pixelFormat [0x%x], tilingMode [0x%x], aspectRatio [0x%x], Width [0x%x] Height [0x%x], pitchInPixel [0x%x]", pixelFormat, tilingMode, aspectRatio, width, height, pitchInPixel);
			}

			_SceVideoOutDataStorage.OrginalAspectRatio     = aspectRatio;
			_SceVideoOutDataStorage.OrginalWidth           = width;
			_SceVideoOutDataStorage.OrginalHeight          = height;
			_SceVideoOutDataStorage.OrginalPitch           = pitchInPixel;
			_SceVideoOutDataStorage.OrginalVideoTilingType = tilingMode;
			_SceVideoOutDataStorage.OrginalPixelFormat     = pixelFormat;

			sceVideoOutSetBufferAttribute(attribute, (attr->PixelFormat == -1 ? pixelFormat : attr->PixelFormat), (attr->TilingMode == -1 ? tilingMode : attr->TilingMode), (attr->AspectRatio == -1 ? aspectRatio : attr->AspectRatio), (attr->Width == -1 ? width : attr->Width), (attr->Height == -1 ? height : attr->Height), (attr->pitchInPixel == -1 ? pitchInPixel : attr->pitchInPixel));

		}

		int32_t sceVideoOutRegisterBuffersHook(int32_t handle, int32_t startIndex, void** addresses, int32_t bufferNum, SceVideoOutBufferAttribute *attribute)
		{
			auto ret = sceVideoOutRegisterBuffers(handle, startIndex, addresses, bufferNum, attribute);
			
			_SceVideoOutDataStorage.VideoBufferSize = _SceVideoOutDataStorage.OrginalWidth * _SceVideoOutDataStorage.OrginalHeight;
			_SceVideoOutDataStorage.VideoBufferAddr = (*addresses);

			return ret;
		}

		int		scePadReadStateHook(int32_t handle, ScePadData *pData)
		{
			int ret = scePadReadState(handle, pData);
			if (ret == 0)
			{
				_ScePadDataStorage.ControllerDataRead = true;
				SetButtonID(pData->buttons);
			}

			return ret;
		}

		int		scePadOpenHook(int32_t userId, int32_t type, int32_t index, ScePadOpenParam* pParam)
		{
			int ret = scePadOpen(userId, type, index, pParam);

			_ScePadDataStorage.UserID = userId;
			_ScePadDataStorage.PadHandle = ret;
			_ScePadDataStorage.ControllerType = type;
			_ScePadDataStorage.ControllerEnabled = true;

			return ret;
		}

		int		sceNpTrophyCreateHandleHook(int32_t *handle)
		{
			int ret = sceNpTrophyCreateHandle(handle);

			_SceTrophyStorage.handle = *handle;

			return ret;
		}

		int		sceNpTrophyCreateContextHook(int32_t *context, int32_t userId, uint32_t serviceLabel, uint64_t options)
		{
			int ret = sceNpTrophyCreateContext(context, userId, serviceLabel, options);

			_SceTrophyStorage.context = *context;
			_SceTrophyStorage.UserID = userId;
			_SceTrophyStorage.serviceLabel = serviceLabel;
			_SceTrophyStorage.options = options;

			return ret;
		}

		int		sceHttpCreateConnectionHook(int tmplId, const char *serverName, const char *scheme, uint16_t port, int isEnableKeepalive)
		{
#if _DEBUG
#else
			if (xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions()->IsDebugMode)
#endif
			{
				xUtilty::KernelPrintOut("sceHttpCreateConnectionHook called, serverName [%s], scheme [%s], port [%isEnableKeepalive [%s]", serverName, scheme, port, BOOL_TYPE_AS_STRING(isEnableKeepalive));
			}

			return sceHttpCreateConnection(tmplId, serverName, scheme, port, isEnableKeepalive);
		}
		
		int		sceHttpCreateConnectionWithURLHook(int tmplId, const char *url, int isEnableKeepalive)
		{
#if _DEBUG
#else
			if (xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions()->IsDebugMode)
#endif
			{
				xUtilty::KernelPrintOut("sceHttpCreateConnectionWithURLHook called, url [%s], isEnableKeepalive [%s]", url, BOOL_TYPE_AS_STRING(isEnableKeepalive));
			}

			return sceHttpCreateConnectionWithURL(tmplId, url, isEnableKeepalive);
		}

		int		sceHttpReadDataHook(int reqId, void* data, size_t size)
		{
			int ret = sceHttpReadData(reqId, data, size);
#if _DEBUG
#else
			if (xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions()->IsDebugMode && size < 1024)
#endif
			{
				char buffer[1024 * 8] { 0 };
				memcpy(buffer, data, size);
				xUtilty::KernelPrintOut("%s", buffer);
			}

			return ret;
		}
		
		int		sceHttpSendRequestHook(int reqId, const void *postData, size_t size)
		{
			int ret = sceHttpSendRequest(reqId, postData, size);
#if _DEBUG
#else
			if (xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions()->IsDebugMode && size < 1024)
#endif
			{
				char buffer[1024 * 8] { 0 };
				memcpy(buffer, postData, size);
				xUtilty::KernelPrintOut("%s", buffer);
			}

			return ret;
		}

		int		sceNetSendHook(int s, const void *msg, size_t len, int flags)
		{
			int ret = sceNetSend(s, msg, len, flags);
			
#if _DEBUG
#else
			if (xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions()->IsDebugMode && len < 1024)
#endif
			{
				char buffer[1024 * 8] { 0 };
				memcpy(buffer, msg, len);
				xUtilty::KernelPrintOut("%s", buffer);
			}

			return ret;
		}

		int32_t submitAndFlipCommandBuffersHook(uint32_t count, void *dcbGpuAddrs[], uint32_t *dcbSizesInBytes, void *ccbGpuAddrs[], uint32_t *ccbSizesInBytes, uint32_t videoOutHandle, uint32_t displayBufferIndex, uint32_t flipMode, int64_t flipArg)
		{	
			auto ret = submitAndFlipCommandBuffers_(count, dcbGpuAddrs, dcbSizesInBytes, ccbGpuAddrs, ccbSizesInBytes, videoOutHandle, displayBufferIndex, flipMode, flipArg);
			// FrameUtil::Tracker::GetSingleton()->Update();
			return ret;
		}

#if __ORBIS__
		int		sceNpGetOnlineIdHook(int32_t userId, SceNpOnlineId* onlineId)
		{	
			auto attr = xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions();
			if (attr->BypassPSN)
			{
				memcpy(onlineId->data, attr->UserID, 16);
				onlineId->term = '\0';
				return 0;
			}
			else
			{
				return sceNpGetOnlineId(userId, onlineId);
			}
		}

		int		sceNpCheckNpAvailabilityHook(int reqId, const SceNpOnlineId* pOnlineId, void* pReserved)
		{
			auto attr = xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions();
			if (attr->BypassPSN)
			{
				xUtilty::Log::GetSingleton()->Write(xUtilty::Log::logLevel::kTrace, "sceNpCheckNpAvailabilityAHook Called!");
				return 0;
			}
			else
			{
				return (*_sceNpCheckNpAvailability)(reqId, pOnlineId, pReserved);
			}
		}

		int		sceNpDeleteRequestHook(int reqId)
		{
			auto attr = xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions();
			if (attr->BypassPSN)
			{
				xUtilty::Log::GetSingleton()->Write(xUtilty::Log::logLevel::kTrace, "sceNpDeleteRequestHook Called!");
				return 0;
			}
			else
			{
				return sceNpDeleteRequest(reqId);
			}
		}

		int		sceNpPollAsyncHook(int reqId, int *result)
		{
			auto attr = xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions();
			if (attr->BypassPSN)
			{
				xUtilty::Log::GetSingleton()->Write(xUtilty::Log::logLevel::kTrace, "sceNpPollAsyncHook Called!");
				*result = 0;
				return 0;
			}
			else
			{
				return sceNpPollAsync(reqId, result);
			}

		}

		int		sceNpGetAccountCountryHook(SceUserServiceUserId* userId, SceNpCountryCode* countryCode)
		{
			auto attr = xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions();
			if (attr->BypassPSN)
			{
				memcpy(countryCode->data, attr->CountryCode, 2);
				countryCode->term = '\0';
				return 0;
			}
			else
			{
				//
				return (*_sceNpGetAccountCountry)(userId, countryCode);
			}
		}

		int		sceNpCreateAsyncRequestHook(const SceNpCreateAsyncRequestParameter *param)
		{
			auto attr = xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions();
			if (attr->BypassPSN)
			{
				xUtilty::Log::GetSingleton()->Write(xUtilty::Log::logLevel::kTrace, "sceNpPollAsyncHook Called!");
				return 1;
			}
			else
			{
				return sceNpCreateAsyncRequest(param);
			}

		}

		int		sceNpAuthGetAuthorizationCodeHook(int reqId, const void* pParam, SceNpAuthorizationCode* pAuthCode, int* pIssuerId)
		{
			auto attr = xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions();
			if (attr->BypassPSN)
			{
				return 0;
			}
			else
			{
				//
				return (*_sceNpAuthGetAuthorizationCode)(reqId, pParam, pAuthCode, pIssuerId);
			}
		}

		int		sceNpAuthDeleteRequestHook(int reqId)
		{
			auto attr = xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions();
			if (attr->BypassPSN)
			{
				xUtilty::Log::GetSingleton()->Write(xUtilty::Log::logLevel::kTrace, "sceNpAuthDeleteRequestHook Called!");
				return 0;
			}
			else
			{
				return sceNpAuthDeleteRequest(reqId);
			}
		}

		int		sceNpAuthCreateRequestHook(void)
		{
			auto attr = xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions();
			if (attr->BypassPSN)
			{
				xUtilty::Log::GetSingleton()->Write(xUtilty::Log::logLevel::kTrace, "sceNpAuthCreateRequestHook Called!");
				return 1;
			}
			else
			{
				return sceNpAuthCreateRequest();
			}
		}

		int		sceNpAuthCreateAsyncRequestHook(const SceNpAuthCreateAsyncRequestParameter *param)
		{
			auto attr = xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions();
			if (attr->BypassPSN)
			{
				xUtilty::Log::GetSingleton()->Write(xUtilty::Log::logLevel::kTrace, "sceNpAuthCreateAsyncRequestHook Called!");
				return 1;
			}
			else
			{
				return sceNpAuthCreateAsyncRequest(param);
			}
		}

		int		sceNpSetContentRestrictionHook(const SceNpContentRestriction *pRestriction)
		{
			auto attr = xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions();
			if (attr->BypassPSN)
			{
				xUtilty::Log::GetSingleton()->Write(xUtilty::Log::logLevel::kTrace, "sceNpSetContentRestrictionHook Called!");
				return 0;
			}
			else
			{
				return sceNpSetContentRestriction(pRestriction);
			}
		}

		int		sceNpGetParentalControlInfoHook(int reqId, const SceNpOnlineId *pOnlineId, int8_t *pAge, SceNpParentalControlInfo *pInfo)
		{
			auto attr = xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions();
			if (attr->BypassPSN)
			{
				*pAge = attr->Age;
				memset(pInfo, (int)false, sizeof(SceNpParentalControlInfo));
				return 0;
			}
			else
			{
				//
				return (*_sceNpGetParentalControlInfo)(reqId, pOnlineId, pAge, pInfo);
			}
		}

		int		sceNpAuthPollAsyncHook(int reqId, int *result)
		{
			auto attr = xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions();
			if (attr->BypassPSN)
			{
				xUtilty::Log::GetSingleton()->Write(xUtilty::Log::logLevel::kTrace, "sceNpAuthPollAsyncHook Called!");
				*result = 0;
				return 0;
			}
			else
			{
				return sceNpAuthPollAsync(reqId, result);
			}

		}
#endif

		void	ApplyOrbisHooks()
		{
			_SceVideoOutDataStorage = SceVideoOutDataStorage();
			_ScePadDataStorage		= ScePadDataStorage();
			_SceTrophyStorage		= SceTrophyStorage();
			_SceSaveDataStorage		= SceSaveDataStorage();

			auto& trampoline = xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch);

			// SaveData
			trampoline.write_branch<6>(sceSaveDataMount2PLTAddress.address(),					(uintptr_t)sceSaveDataMount2Hook);
			trampoline.write_branch<6>(sceSaveDataUmountPLTAddress.address(),					(uintptr_t)sceSaveDataUmountHook);
			
			// VideoOut
			trampoline.write_branch<6>(sceGnmSubmitAndFlipCommandBuffersPLTAddress.address(),	(uintptr_t)submitAndFlipCommandBuffersHook);
			trampoline.write_branch<6>(sceVideoOutOpenPLTAddress.address(),						(uintptr_t)sceVideoOutOpenHook);
			trampoline.write_branch<6>(sceVideoOutSetFlipRatePLTAddress.address(),				(uintptr_t)sceVideoOutSetFlipRateHook);
			trampoline.write_branch<6>(sceVideoOutSetBufferAttributePLTAddress.address(),		(uintptr_t)sceVideoOutSetBufferAttributeHook);
			trampoline.write_branch<6>(sceVideoOutRegisterBuffersPLTAddress.address(),			(uintptr_t)sceVideoOutRegisterBuffersHook);

			// scePad
			trampoline.write_branch<6>(scePadReadStatePLTAddress.address(),						(uintptr_t)scePadReadStateHook);
			trampoline.write_branch<6>(scePadOpenPLTAddress.address(),							(uintptr_t)scePadOpenHook);
			
			// SceNpTrophy
			trampoline.write_branch<6>(sceNpTrophyCreateHandlePLTAddress.address(),				(uintptr_t)sceNpTrophyCreateHandleHook);
			trampoline.write_branch<6>(sceNpTrophyCreateContextPLTAddress.address(),			(uintptr_t)sceNpTrophyCreateContextHook);

			// sceHttp
			trampoline.write_branch<6>(sceHttpCreateConnectionPLTAddress.address(),				(uintptr_t)sceHttpCreateConnectionHook);
			trampoline.write_branch<6>(sceHttpReadDataPLTAddress.address(),						(uintptr_t)sceHttpReadDataHook);
			trampoline.write_branch<6>(sceHttpSendRequestPLTAddress.address(),					(uintptr_t)sceHttpSendRequestHook);
			trampoline.write_branch<6>(sceNetSendPLTAddress.address(),							(uintptr_t)sceNetSendHook);
			
			// debug
			if (xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions()->IsDebugMode)
			{
				trampoline.write_branch<6>(OpenPLTAddress.address(),							(uintptr_t)openHook);
				trampoline.write_branch<6>(sceKernelOpenPLTAddress.address(),					(uintptr_t)sceKernelOpenHook);

				trampoline.write_branch<6>(statPLTAddress.address(),							(uintptr_t)statHook);
				trampoline.write_branch<6>(sceKernelStatPLTAddress.address(),					(uintptr_t)sceKernelStatHook);

				trampoline.write_branch<6>(writePLTAddress.address(),							(uintptr_t)writeHook);

				trampoline.write_branch<6>(lseekPLTAddress.address(),							(uintptr_t)lseekHook);
				trampoline.write_branch<6>(sceKernelLseekPLTAddress.address(),					(uintptr_t)sceKernelLseekHook);

				trampoline.write_branch<6>(readPLTAddress.address(),							(uintptr_t)readHook);
				trampoline.write_branch<6>(sceKernelReadPLTAddress.address(),					(uintptr_t)sceKernelReadHook);
				

#if __ORBIS__
				trampoline.write_branch<6>(fopenPLTAddress.address(),							(uintptr_t)fopenHook);
				trampoline.write_branch<6>(fopen_sPLTAddress.address(),							(uintptr_t)fopen_sHook);

				trampoline.write_branch<6>(sceFiosDHOpenPLTAddress.address(),					(uintptr_t)sceFiosDHOpenHook);
				trampoline.write_branch<6>(sceFiosDHOpenSyncPLTAddress.address(),				(uintptr_t)sceFiosDHOpenSyncHook);
				trampoline.write_branch<6>(sceFiosFHOpenSyncPLTAddress.address(),				(uintptr_t)sceFiosFHOpenSyncHook);
				trampoline.write_branch<6>(sceFiosFHOpenWithModeSyncPLTAddress.address(),		(uintptr_t)sceFiosFHOpenWithModeSyncHook);
#endif

			}

			if (xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions()->BypassPSN)
			{
#if __ORBIS__
				xUtilty::Notify("Applying PSN bypass hooks");

				trampoline.write_branch<6>(sceNpGetOnlineIdPLTAddress.address(),				(uintptr_t)sceNpGetOnlineIdHook);
				trampoline.write_branch<6>(sceNpSetContentRestrictionPLTAddress.address(),		(uintptr_t)sceNpSetContentRestrictionHook);
				trampoline.write_branch<6>(sceNpPollAsyncPLTAddress.address(),					(uintptr_t)sceNpPollAsyncHook);
				trampoline.write_branch<6>(sceNpDeleteRequestPLTAddress.address(),				(uintptr_t)sceNpDeleteRequestHook);
				trampoline.write_branch<6>(sceNpCreateAsyncRequestPLTAddress.address(),			(uintptr_t)sceNpCreateAsyncRequestHook);
				trampoline.write_branch<6>(sceNpAuthPollAsyncPLTAddress.address(),				(uintptr_t)sceNpAuthPollAsyncHook);
				trampoline.write_branch<6>(sceNpAuthDeleteRequestPLTAddress.address(),			(uintptr_t)sceNpAuthDeleteRequestHook);
				trampoline.write_branch<6>(sceNpAuthCreateRequestPLTAddress.address(),			(uintptr_t)sceNpAuthCreateRequestHook);
				trampoline.write_branch<6>(sceNpAuthCreateAsyncRequestPLTAddress.address(),		(uintptr_t)sceNpAuthCreateAsyncRequestHook);

				//
				_sceNpCheckNpAvailability		= trampoline.write_branch<6>(sceNpCheckNpAvailabilityPLTAddress.address(),			(uintptr_t)sceNpCheckNpAvailabilityHook);
				_sceNpGetAccountCountry			= trampoline.write_branch<6>(sceNpGetAccountCountryAPLTAddress.address(),			(uintptr_t)sceNpGetAccountCountryHook);
				_sceNpAuthGetAuthorizationCode	= trampoline.write_branch<6>(sceNpAuthGetAuthorizationCodePLTAddress.address(),		(uintptr_t)sceNpAuthGetAuthorizationCodeHook);
				_sceNpGetParentalControlInfo	= trampoline.write_branch<6>(sceNpGetParentalControlInfoAPLTAddress.address(),		(uintptr_t)sceNpGetParentalControlInfoHook);
				//
#endif
			}
		}
	}
}