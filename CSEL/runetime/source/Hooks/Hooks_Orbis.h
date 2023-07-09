#pragma once

#include "../../../../OrbisUtil/include/bitFlags.h"

#include <stdio.h>
#include <stdint.h>

#ifndef AVIO_H
#define AVIO_H

struct SceVideoOutDataStorage
{
	bool				 VideoEnabled;
	int32_t				 UserID;
	int32_t				 VideobusType;

	// these are the params that are passed to the function, we ignore ones that are patched them
	int32_t				 OrginalFlipRate;		// 0 = 60 FPS | 1 = 30 FPS | 2 = 20 FPS
	uint32_t			 OrginalAspectRatio;
	uint32_t			 OrginalWidth;
	uint32_t			 OrginalHeight;
	uint32_t			 OrginalPitch;
	uint32_t			 OrginalVideoTilingType;
	uint32_t			 OrginalPixelFormat;

	uint32_t			 OrginalPixelDepth;
	void*				 VideoBufferAddr;
	size_t				 VideoBufferSize;
};

struct ScePadDataStorage
{
	int32_t				 UserID;
	int32_t				 PadHandle;

	int32_t				 ControllerType;		// 0 = DS4 controller | 1 = special controllers
	bool				 ControllerEnabled;
	bool				 ControllerDataRead;

	volatile int32_t	 PreviousButton;
	volatile int32_t	 CurrentButton;
};

struct SceTrophyStorage
{
	int32_t			platinumId;
	int32_t			handle;
	int32_t			context;
	int32_t			UserID;
	uint32_t		serviceLabel;
	uint64_t		options;
};

struct SceSaveDataStorage
{
	xUtilty::BitFlags<uint32_t>	SaveDataMountMode;			// Orginal Mount Mode
	xUtilty::BitFlags<uint32_t>	SaveDataMountMode2;			// New Mount Mode
	uint64_t					SaveDataRequestedBlockSize;	// Orginal
	uint64_t					SaveDataRequiredBlockSize;	// Orginal
};
#endif

namespace Runetime
{
	namespace Hooks
	{
		void ApplyOrbisHooks();

		extern SceSaveDataStorage	  _SceSaveDataStorage;
		extern SceVideoOutDataStorage _SceVideoOutDataStorage;
		extern ScePadDataStorage	  _ScePadDataStorage;
		extern SceTrophyStorage		  _SceTrophyStorage;
	}
}