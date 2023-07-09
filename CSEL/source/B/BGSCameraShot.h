#pragma once

#include "../T/TESForm.h"
#include "../T/TESImageSpaceModifiableForm.h"
#include "../T/TESModel.h"

namespace ConsoleRE
{
	class BGSCameraShot :
		public TESForm,
		public TESModel,
		public TESImageSpaceModifiableForm
	{
	public:
		static constexpr int TypeID = 96;
		struct CAMERA_SHOT_DATA
		{
		public:
			enum class Flag
			{
				kNone = 0,
				kPositionFollowsLocation = 1 << 0,
				kRotationFollowsTarget = 1 << 1,
				kDontFollowBone = 1 << 2,
				kFirstPersonCamera = 1 << 3,
				kNoTracer = 1 << 4,
				kStartAtTimeZero = 1 << 5
			};
		public:
			uint32_t cameraAction;
			uint32_t location;
			uint32_t target;
			uint32_t flags;
			float	 playerTimeMult;
			float	 targetTimeMult;
			float	 globalTimeMult;
			float	 maxTime;
			float	 minTime;
			float	 targetPercentBetweenActors;
			float	 nearTargetDistance;
		};
		static_assert(sizeof(CAMERA_SHOT_DATA) == 0x2C);
	public:
		~BGSCameraShot() override;

		// override (TESForm)
		void InitializeData() override;
		bool Load(TESFile* a_mod) override;
		void InitItemImpl() override;
	public:
		CAMERA_SHOT_DATA data;
		uint32_t		 pad84;
		void*            unk88;
		void*            unk90;
		uint32_t         unk98;
		uint32_t		 unk9C;
		void*            unkA0;
		void*            unkA8;
		uint64_t		 unkB0;
		void*            unkB8;
	};
	static_assert(sizeof(BGSCameraShot) == 0xC0);
}