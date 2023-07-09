#pragma once

#include "../B/BSAudioManagerThread.h"
#include "../B/BSFixedString.h"
#include "../B/BSTHashMap.h"

namespace ConsoleRE
{
	class BSISoundDescriptor;
	class BSXAudio2GameSound;
	struct BSSoundHandle;

	// 0x150
	class BSAudioManager
	{
	public:
		// 0xE09C40
		static BSAudioManager* GetSingleton();

		bool Play(uint32_t a_soundFormID);
		bool Play(BSISoundDescriptor* a_descriptor);
		bool BuildSoundDataFromDescriptor(BSSoundHandle& a_soundHandle, BSISoundDescriptor* a_descriptor, uint32_t a_flags = 0x1A);
	public:
	};
}