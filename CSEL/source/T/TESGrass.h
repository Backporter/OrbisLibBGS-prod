#pragma once

#include "../F/FormTypes.h"
#include "../T/TESBoundObject.h"
#include "../T/TESModel.h"

namespace ConsoleRE
{
	class TESGrass :public TESBoundObject, public TESModel
	{
	public:
		struct GRASS_DATA
		{
		public:
			enum class Flag
			{
				kNone = 0,
				kVertexLighting = 1 << 0,
				kUniformScale = 1 << 1,
				kFitSlope = 1 << 2
			};
		public:
			int8_t												density;
			int8_t												minSlopeDegrees;
			int8_t												maxSlopeDegrees;
			uint8_t												pad03;
			uint16_t											distanceFromWaterLevel;
			uint16_t											pad06;
			uint32_t											underwater;
			float												positionRange;
			float												heightRange;
			float												colorRange;
			float												wavePeriod;
			uint8_t												flags;
			uint8_t												pad1D;
			uint16_t											pad1E;
		};
		static_assert(sizeof(GRASS_DATA) == 0x20);
	public:
		static constexpr int TypeID = 37;
	public:
		~TESGrass() override;

		// override (TESBoundObject)
		void InitializeData() override;
		bool Load(TESFile* a_mod) override;
		void InitItemImpl() override;

		// add
		virtual uint8_t							GetDensity() const;
		virtual bool                            SetDensity(uint8_t a_density);
		virtual uint8_t							GetMinSlopeDegrees() const;
		virtual bool                            SetMinSlopeDegrees(uint8_t a_minSlope);
		virtual uint8_t							GetMaxSlopeDegrees() const;
		virtual bool                            SetMaxSlopeDegrees(uint8_t a_maxSlope);
		virtual float							GetMinSlope() const;
		virtual float							GetMaxSlope() const;
		virtual uint16_t						GetDistanceFromWaterLevel() const;
		virtual void                            SetDistanceFromWaterLevel(uint16_t a_unitsFromWater);
		virtual uint32_t					    GetUnderwaterState() const;
		virtual void                            SetUnderwaterState(uint32_t a_waterState);
		virtual float							GetPositionRange() const;
		virtual bool                            SetPositionRange(float a_positionRange);
		virtual float							GetHeightRange() const;
		virtual bool                            SetHeightRange(float a_heightRange);
		virtual float							GetColorRange() const;
		virtual bool                            SetColorRange(float a_colorRange);
		virtual float							GetWavePeriod() const;
		virtual bool                            SetWavePeriod(float a_wavePeriod);
		virtual bool							GetVertexLighting() const;
		virtual void                            SetVertexLighting(bool a_set);
		virtual bool							GetUniformScaling() const;
		virtual void                            SetUniformScaling(bool a_set);
		virtual bool							GetFitToSlope() const;
		virtual void                            SetFitToSlope(bool a_set);
	public:
		GRASS_DATA data;
	};
	static_assert(sizeof(TESGrass) == 0x70);
}