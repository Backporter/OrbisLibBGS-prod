#pragma once

#include "../B/BSTArray.h"
#include "../N/NiExtraData.h"
#include "../N/NiPoint3.h"

namespace ConsoleRE
{
	class BSFurnitureMarker
	{
	public:
		enum class AnimationType
		{
			kSit = 1 << 0,
			kSleep = 1 << 1,
			kLean = 1 << 2
		};

		enum class EntryProperties
		{
			kFront = 1 << 0,
			kBehind = 1 << 1,
			kRight = 1 << 2,
			kLeft = 1 << 3,
			kUp = 1 << 4
		};
	public:
		NiPoint3 offset;
		float    heading;
		uint16_t animationType;
		uint16_t entryProperties;
	};

	class BSFurnitureMarkerNode : public NiExtraData
	{
	public:
		BSTArray<BSFurnitureMarker> markers;
	};
	static_assert(sizeof(BSFurnitureMarkerNode) == 0x28);
}