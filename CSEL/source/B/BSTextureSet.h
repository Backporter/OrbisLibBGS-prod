#pragma once

#include "../N/NiObject.h"

namespace ConsoleRE
{
	class NiSourceTexture;

	class BSTextureSet : public NiObject
	{
	public:
		struct Textures
		{
			enum Texture : uint32_t
			{
				kDiffuse = 0,
				kNormal,
				kGloss = kNormal,
				kEnvironmentMask,
				kSubsurfaceTint = kEnvironmentMask,
				kGlowMap,
				kDetailMap = kGlowMap,
				kHeight,
				kEnvironment,
				kMultilayer,
				kBacklightMask,
				kSpecular = kBacklightMask,

				kTotal
			};
		};
		using Texture = Textures::Texture;
	public:
		~BSTextureSet() override;

		// override (NiObject)
		const NiRTTI* GetRTTI() const override;
		void          LoadBinary(NiStream& a_stream) override;
		void          LinkObject(NiStream& a_stream) override;
		bool          RegisterStreamables(NiStream& a_stream) override;
		void          SaveBinary(NiStream& a_stream) override;
		bool          IsEqual(NiObject* a_object) override;

		// add
		virtual const char* GetTexturePath(Texture a_texture) = 0;
		virtual void        SetTexture(Texture a_texture, NiSourceTexture* a_srcTexture) = 0;
		virtual void        SetTexturePath(Texture a_texture, const char* a_path) = 0; 
	public:
	};
	static_assert(sizeof(BSTextureSet) == 0x10);
}