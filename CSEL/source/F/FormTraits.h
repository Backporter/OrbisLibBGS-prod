#pragma once

#include "../A/Actor.h"
#include "../A/ActorValueInfo.h"
#include "../A/AlchemyItem.h"
#include "../A/ArrowProjectile.h"
#include "../B/BGSAcousticSpace.h"
#include "../B/BGSAction.h"
#include "../B/BGSAddonNode.h"
#include "../B/BGSApparatus.h"
#include "../B/BGSArtObject.h"
#include "../B/BGSAssociationType.h"
#include "../B/BGSBodyPartData.h"
#include "../B/BGSCameraPath.h"
#include "../B/BGSCameraShot.h"
#include "../B/BGSCollisionLayer.h"
#include "../B/BGSColorForm.h"
#include "../B/BGSConstructibleObject.h"
#include "../B/BGSDebris.h"
#include "../B/BGSDefaultObjectManager.h"
#include "../B/BGSDialogueBranch.h"
#include "../B/BGSDualCastData.h"
#include "../B/BGSEncounterZone.h"
#include "../B/BGSEquipSlot.h"
#include "../B/BGSExplosion.h"
#include "../B/BGSFootstep.h"
#include "../B/BGSFootstepSet.h"
#include "../B/BGSHazard.h"
#include "../B/BGSHeadPart.h"
#include "../B/BGSIdleMarker.h"
#include "../B/BGSImpactData.h"
#include "../B/BGSImpactDataSet.h"
#include "../B/BGSKeyword.h"
#include "../B/BGSLensFlare.h"
#include "../B/BGSLightingTemplate.h"
#include "../B/BGSListForm.h"
#include "../B/BGSLocation.h"
#include "../B/BGSLocationRefType.h"
#include "../B/BGSMaterialObject.h"
#include "../B/BGSMaterialType.h"
#include "../B/BGSMenuIcon.h"
#include "../B/BGSMessage.h"
#include "../B/BGSMovableStatic.h"
#include "../B/BGSMovementType.h"
#include "../B/BGSMusicTrackFormWrapper.h"
#include "../B/BGSMusicType.h"
#include "../B/BGSNote.h"
#include "../B/BGSOutfit.h"
#include "../B/BGSPerk.h"
#include "../B/BGSProjectile.h"
#include "../B/BGSRagdoll.h"
#include "../B/BGSReferenceEffect.h"
#include "../B/BGSRelationship.h"
#include "../B/BGSReverbParameters.h"
#include "../B/BGSScene.h"
#include "../B/BGSShaderParticleGeometryData.h"
#include "../B/BGSSoundCategory.h"
#include "../B/BGSSoundDescriptorForm.h"
#include "../B/BGSSoundOutput.h"
#include "../B/BGSStaticCollection.h"
#include "../B/BGSStoryManagerBranchNode.h"
#include "../B/BGSStoryManagerEventNode.h"
#include "../B/BGSStoryManagerQuestNode.h"
#include "../B/BGSTalkingActivator.h"
#include "../B/BGSTextureSet.h"
#include "../B/BGSVoiceType.h"
#include "../B/BGSVolumetricLighting.h"
#include "../B/BarrierProjectile.h"
#include "../B/BeamProjectile.h"
#include "../C/Character.h"
#include "../C/ConeProjectile.h"
#include "../E/EffectSetting.h"
#include "../E/EnchantmentItem.h"
#include "../F/FlameProjectile.h"
#include "../G/GrenadeProjectile.h"
#include "../H/Hazard.h"
#include "../I/IngredientItem.h"
#include "../M/MissileProjectile.h"
#include "../N/NavMesh.h"
#include "../N/NavMeshInfoMap.h"
#include "../P/PlayerCharacter.h"
#include "../S/Script.h"
#include "../S/ScrollItem.h"
#include "../S/SpellItem.h"
#include "../T/TESAmmo.h"
#include "../T/TESClass.h"
#include "../T/TESClimate.h"
#include "../T/TESCombatStyle.h"
#include "../T/TESEffectShader.h"
#include "../T/TESEyes.h"
#include "../T/TESFaction.h"
#include "../T/TESFlora.h"
#include "../T/TESForm.h"
#include "../T/TESFurniture.h"
#include "../T/TESGlobal.h"
#include "../T/TESGrass.h"
#include "../T/TESIdleForm.h"
#include "../T/TESImageSpace.h"
#include "../T/TESImageSpaceModifier.h"
#include "../T/TESKey.h"
#include "../T/TESLandTexture.h"
#include "../T/TESLevCharacter.h"
#include "../T/TESLevItem.h"
#include "../T/TESLevSpell.h"
#include "../T/TESLoadScreen.h"
#include "../T/TESNPC.h"
#include "../T/TESObjectACTI.h"
#include "../T/TESObjectANIO.h"
#include "../T/TESObjectARMA.h"
#include "../T/TESObjectARMO.h"
#include "../T/TESObjectBOOK.h"
#include "../T/TESObjectCELL.h"
#include "../T/TESObjectCONT.h"
#include "../T/TESObjectDOOR.h"
#include "../T/TESObjectLAND.h"
#include "../T/TESObjectLIGH.h"
#include "../T/TESObjectMISC.h"
#include "../T/TESObjectREFR.h"
#include "../T/TESObjectSTAT.h"
#include "../T/TESObjectTREE.h"
#include "../T/TESObjectWEAP.h"
#include "../T/TESPackage.h"
#include "../T/TESQuest.h"
#include "../T/TESRace.h"
#include "../T/TESRegion.h"
#include "../T/TESShout.h"
#include "../T/TESSoulGem.h"
#include "../T/TESSound.h"
#include "../T/TESTopic.h"
#include "../T/TESTopicInfo.h"
#include "../T/TESWaterForm.h"
#include "../T/TESWeather.h"
#include "../T/TESWordOfPower.h"
#include "../T/TESWorldSpace.h"

namespace ConsoleRE
{
	template <class T, class>
	T* TESForm::As() noexcept
	{
		return const_cast<T*>(static_cast<const TESForm*>(this)->As<T>());
	}

	template <class T, class>
	const T* TESForm::As() const noexcept
	{
		switch (GetFormType()) 
		{
			case TESForm::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESForm*, const T*>)
				{
					return static_cast<const TESForm*>(this);
				}
			}
			break;

			case BGSKeyword::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSKeyword*, const T*>)
				{
					return static_cast<const BGSKeyword*>(this);
				}
			}
			break;

			case BGSLocationRefType::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSLocationRefType*, const T*>)
				{
					return static_cast<const BGSLocationRefType*>(this);
				}
			}
			break;

			case BGSAction::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSAction*, const T*>)
				{
					return static_cast<const BGSAction*>(this);
				}
			}
			break;

			case BGSTextureSet::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSTextureSet*, const T*>)
				{
					return static_cast<const BGSTextureSet*>(this);
				}
			}
			break;

			case BGSMenuIcon::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSMenuIcon*, const T*>)
				{
					return static_cast<const BGSMenuIcon*>(this);
				}
			}
			break;

			case TESGlobal::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESGlobal*, const T*>)
				{
					return static_cast<const TESGlobal*>(this);
				}
			}
			break;

			case TESClass::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESClass*, const T*>)
				{
					return static_cast<const TESClass*>(this);
				}
			}
			break;

			case TESFaction::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESFaction*, const T*>)
				{
					return static_cast<const TESFaction*>(this);
				}
			}
			break;

			case BGSHeadPart::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSHeadPart*, const T*>)
				{
					return static_cast<const BGSHeadPart*>(this);
				}
			}
			break;

			case TESEyes::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESEyes*, const T*>)
				{
					return static_cast<const TESEyes*>(this);
				}
			}
			break;

			case TESRace::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESRace*, const T*>)
				{
					return static_cast<const TESRace*>(this);
				}
			}
			break;

			case TESSound::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESSound*, const T*>)
				{
					return static_cast<const TESSound*>(this);
				}
			}
			break;

			case BGSAcousticSpace::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSAcousticSpace*, const T*>)
				{
					return static_cast<const BGSAcousticSpace*>(this);
				}
			}
			break;

			case EffectSetting::TypeID:
			{
				if constexpr (std::is_convertible_v<const EffectSetting*, const T*>)
				{
					return static_cast<const EffectSetting*>(this);
				}
			}
			break;

			case Script::TypeID:
			{
				if constexpr (std::is_convertible_v<const Script*, const T*>)
				{
					return static_cast<const Script*>(this);
				}
			}
			break;

			case TESLandTexture::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESLandTexture*, const T*>)
				{
					return static_cast<const TESLandTexture*>(this);
				}
			}
			break;

			case EnchantmentItem::TypeID:
			{
				if constexpr (std::is_convertible_v<const EnchantmentItem*, const T*>)
				{
					return static_cast<const EnchantmentItem*>(this);
				}
			}
			break;

			case SpellItem::TypeID:
			{
				if constexpr (std::is_convertible_v<const SpellItem*, const T*>)
				{
					return static_cast<const SpellItem*>(this);
				}
			}
			break;

			case ScrollItem::TypeID:
			{
				if constexpr (std::is_convertible_v<const ScrollItem*, const T*>)
				{
					return static_cast<const ScrollItem*>(this);
				}
			}
			break;

			case TESObjectACTI::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESObjectACTI*, const T*>)
				{
					return static_cast<const TESObjectACTI*>(this);
				}
			}
			break;

			case BGSTalkingActivator::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSTalkingActivator*, const T*>)
				{
					return static_cast<const BGSTalkingActivator*>(this);
				}
			}
			break;

			case TESObjectARMO::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESObjectARMO*, const T*>)
				{
					return static_cast<const TESObjectARMO*>(this);
				}
			}
			break;

			case TESObjectBOOK::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESObjectBOOK*, const T*>)
				{
					return static_cast<const TESObjectBOOK*>(this);
				}
			}
			break;

			case TESObjectCONT::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESObjectCONT*, const T*>)
				{
					return static_cast<const TESObjectCONT*>(this);
				}
			}
			break;

			case TESObjectDOOR::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESObjectDOOR*, const T*>)
				{
					return static_cast<const TESObjectDOOR*>(this);
				}
			}
			break;

			case IngredientItem::TypeID:
			{
				if constexpr (std::is_convertible_v<const IngredientItem*, const T*>)
				{
					return static_cast<const IngredientItem*>(this);
				}
			}
			break;

			case TESObjectLIGH::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESObjectLIGH*, const T*>)
				{
					return static_cast<const TESObjectLIGH*>(this);
				}
			}
			break;

			case TESObjectMISC::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESObjectMISC*, const T*>)
				{
					return static_cast<const TESObjectMISC*>(this);
				}
			}
			break;

			case BGSApparatus::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSApparatus*, const T*>)
				{
					return static_cast<const BGSApparatus*>(this);
				}
			}
			break;

			case TESObjectSTAT::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESObjectSTAT*, const T*>)
				{
					return static_cast<const TESObjectSTAT*>(this);
				}
			}
			break;

			case BGSStaticCollection::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSStaticCollection*, const T*>)
				{
					return static_cast<const BGSStaticCollection*>(this);
				}
			}
			break;

			case BGSMovableStatic::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSMovableStatic*, const T*>)
				{
					return static_cast<const BGSMovableStatic*>(this);
				}
			}
			break;

			case TESGrass::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESGrass*, const T*>)
				{
					return static_cast<const TESGrass*>(this);
				}
			}
			break;

			case TESObjectTREE::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESObjectTREE*, const T*>)
				{
					return static_cast<const TESObjectTREE*>(this);
				}
			}
			break;

			case TESFlora::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESFlora*, const T*>)
				{
					return static_cast<const TESFlora*>(this);
				}
			}
			break;

			case TESFurniture::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESFurniture*, const T*>)
				{
					return static_cast<const TESFurniture*>(this);
				}
			}
			break;

			case TESObjectWEAP::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESObjectWEAP*, const T*>)
				{
					return static_cast<const TESObjectWEAP*>(this);
				}
			}
			break;

			case TESAmmo::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESAmmo*, const T*>)
				{
					return static_cast<const TESAmmo*>(this);
				}
			}
			break;

			case TESNPC::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESNPC*, const T*>)
				{
					return static_cast<const TESNPC*>(this);
				}
			}
			break;

			case TESLevCharacter::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESLevCharacter*, const T*>)
				{
					return static_cast<const TESLevCharacter*>(this);
				}
			}
			break;

			case TESKey::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESKey*, const T*>)
				{
					return static_cast<const TESKey*>(this);
				}
			}
			break;

			case AlchemyItem::TypeID:
			{
				if constexpr (std::is_convertible_v<const AlchemyItem*, const T*>)
				{
					return static_cast<const AlchemyItem*>(this);
				}
			}
			break;

			case BGSIdleMarker::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSIdleMarker*, const T*>)
				{
					return static_cast<const BGSIdleMarker*>(this);
				}
			}
			break;

			case BGSNote::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSNote*, const T*>)
				{
					return static_cast<const BGSNote*>(this);
				}
			}
			break;

			case BGSConstructibleObject::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSConstructibleObject*, const T*>)
				{
					return static_cast<const BGSConstructibleObject*>(this);
				}
			}
			break;

			case BGSProjectile::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSProjectile*, const T*>)
				{
					return static_cast<const BGSProjectile*>(this);
				}
			}
			break;

			case BGSHazard::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSHazard*, const T*>)
				{
					return static_cast<const BGSHazard*>(this);
				}
			}
			break;

			case TESSoulGem::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESSoulGem*, const T*>)
				{
					return static_cast<const TESSoulGem*>(this);
				}
			}
			break;

			case TESLevItem::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESLevItem*, const T*>)
				{
					return static_cast<const TESLevItem*>(this);
				}
			}
			break;

			case TESWeather::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESWeather*, const T*>)
				{
					return static_cast<const TESWeather*>(this);
				}
			}
			break;

			case TESClimate::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESClimate*, const T*>)
				{
					return static_cast<const TESClimate*>(this);
				}
			}
			break;

			case BGSShaderParticleGeometryData::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSShaderParticleGeometryData*, const T*>)
				{
					return static_cast<const BGSShaderParticleGeometryData*>(this);
				}
			}
			break;

			case BGSReferenceEffect::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSReferenceEffect*, const T*>)
				{
					return static_cast<const BGSReferenceEffect*>(this);
				}
			}
			break;

			case TESRegion::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESRegion*, const T*>)
				{
					return static_cast<const TESRegion*>(this);
				}
			}
			break;

			case NavMeshInfoMap::TypeID:
			{
				if constexpr (std::is_convertible_v<const NavMeshInfoMap*, const T*>)
				{
					return static_cast<const NavMeshInfoMap*>(this);
				}
			}
			break;

			case TESObjectCELL::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESObjectCELL*, const T*>)
				{
					return static_cast<const TESObjectCELL*>(this);
				}
			}
			break;

			case TESObjectREFR::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESObjectREFR*, const T*>)
				{
					return static_cast<const TESObjectREFR*>(this);
				}
			}
			break;

			case Character::TypeID:
			{
				if constexpr (std::is_convertible_v<const Character*, const T*>)
				{
					return static_cast<const Character*>(this);
				}
			}
			break;

			case MissileProjectile::TypeID:
			{
				if constexpr (std::is_convertible_v<const MissileProjectile*, const T*>)
				{
					return static_cast<const MissileProjectile*>(this);
				}
			}
			break;

			case ArrowProjectile::TypeID:
			{
				if constexpr (std::is_convertible_v<const ArrowProjectile*, const T*>)
				{
					return static_cast<const ArrowProjectile*>(this);
				}
			}
			break;

			case GrenadeProjectile::TypeID:
			{
				if constexpr (std::is_convertible_v<const GrenadeProjectile*, const T*>)
				{
					return static_cast<const GrenadeProjectile*>(this);
				}
			}
			break;

			case BeamProjectile::TypeID:
			{
				if constexpr (std::is_convertible_v<const BeamProjectile*, const T*>)
				{
					return static_cast<const BeamProjectile*>(this);
				}
			}
			break;

			case FlameProjectile::TypeID:
			{
				if constexpr (std::is_convertible_v<const FlameProjectile*, const T*>)
				{
					return static_cast<const FlameProjectile*>(this);
				}
			}
			break;

			case ConeProjectile::TypeID:
			{
				if constexpr (std::is_convertible_v<const ConeProjectile*, const T*>)
				{
					return static_cast<const ConeProjectile*>(this);
				}
			}
			break;

			case BarrierProjectile::TypeID:
			{
				if constexpr (std::is_convertible_v<const BarrierProjectile*, const T*>)
				{
					return static_cast<const BarrierProjectile*>(this);
				}
			}
			break;

			case Hazard::TypeID:
			{
				if constexpr (std::is_convertible_v<const Hazard*, const T*>)
				{
					return static_cast<const Hazard*>(this);
				}
			}
			break;

			case TESWorldSpace::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESWorldSpace*, const T*>)
				{
					return static_cast<const TESWorldSpace*>(this);
				}
			}
			break;

			case TESObjectLAND::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESObjectLAND*, const T*>)
				{
					return static_cast<const TESObjectLAND*>(this);
				}
			}
			break;

			case NavMesh::TypeID:
			{
				if constexpr (std::is_convertible_v<const NavMesh*, const T*>)
				{
					return static_cast<const NavMesh*>(this);
				}
			}
			break;

			case TESTopic::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESTopic*, const T*>)
				{
					return static_cast<const TESTopic*>(this);
				}
			}
			break;

			case TESTopicInfo::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESTopicInfo*, const T*>)
				{
					return static_cast<const TESTopicInfo*>(this);
				}
			}
			break;

			case TESQuest::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESQuest*, const T*>)
				{
					return static_cast<const TESQuest*>(this);
				}
			}
			break;

			case TESIdleForm::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESIdleForm*, const T*>)
				{
					return static_cast<const TESIdleForm*>(this);
				}
			}
			break;

			case TESPackage::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESPackage*, const T*>)
				{
					return static_cast<const TESPackage*>(this);
				}
			}
			break;

			case TESCombatStyle::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESCombatStyle*, const T*>)
				{
					return static_cast<const TESCombatStyle*>(this);
				}
			}
			break;

			case TESLoadScreen::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESLoadScreen*, const T*>)
				{
					return static_cast<const TESLoadScreen*>(this);
				}
			}
			break;

			case TESLevSpell::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESLevSpell*, const T*>)
				{
					return static_cast<const TESLevSpell*>(this);
				}
			}
			break;

			case TESObjectANIO::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESObjectANIO*, const T*>)
				{
					return static_cast<const TESObjectANIO*>(this);
				}
			}
			break;

			case TESWaterForm::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESWaterForm*, const T*>)
				{
					return static_cast<const TESWaterForm*>(this);
				}
			}
			break;

			case TESEffectShader::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESEffectShader*, const T*>)
				{
					return static_cast<const TESEffectShader*>(this);
				}
			}
			break;

			case BGSExplosion::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSExplosion*, const T*>)
				{
					return static_cast<const BGSExplosion*>(this);
				}
			}
			break;

			case BGSDebris::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSDebris*, const T*>)
				{
					return static_cast<const BGSDebris*>(this);
				}
			}
			break;

			case TESImageSpace::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESImageSpace*, const T*>)
				{
					return static_cast<const TESImageSpace*>(this);
				}
			}
			break;

			case TESImageSpaceModifier::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESImageSpaceModifier*, const T*>)
				{
					return static_cast<const TESImageSpaceModifier*>(this);
				}
			}
			break;

			case BGSListForm::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSListForm*, const T*>)
				{
					return static_cast<const BGSListForm*>(this);
				}
			}
			break;

			case BGSPerk::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSPerk*, const T*>)
				{
					return static_cast<const BGSPerk*>(this);
				}
			}
			break;

			case BGSBodyPartData::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSBodyPartData*, const T*>)
				{
					return static_cast<const BGSBodyPartData*>(this);
				}
			}
			break;

			case BGSAddonNode::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSAddonNode*, const T*>)
				{
					return static_cast<const BGSAddonNode*>(this);
				}
			}
			break;

			case ActorValueInfo::TypeID:
			{
				if constexpr (std::is_convertible_v<const ActorValueInfo*, const T*>)
				{
					return static_cast<const ActorValueInfo*>(this);
				}
			}
			break;

			case BGSCameraShot::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSCameraShot*, const T*>)
				{
					return static_cast<const BGSCameraShot*>(this);
				}
			}
			break;

			case BGSCameraPath::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSCameraPath*, const T*>)
				{
					return static_cast<const BGSCameraPath*>(this);
				}
			}
			break;

			case BGSVoiceType::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSVoiceType*, const T*>)
				{
					return static_cast<const BGSVoiceType*>(this);
				}
			}
			break;

			case BGSMaterialType::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSMaterialType*, const T*>)
				{
					return static_cast<const BGSMaterialType*>(this);
				}
			}
			break;

			case BGSImpactData::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSImpactData*, const T*>)
				{
					return static_cast<const BGSImpactData*>(this);
				}
			}
			break;

			case BGSImpactDataSet::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSImpactDataSet*, const T*>)
				{
					return static_cast<const BGSImpactDataSet*>(this);
				}
			}
			break;

			case TESObjectARMA::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESObjectARMA*, const T*>)
				{
					return static_cast<const TESObjectARMA*>(this);
				}
			}
			break;

			case BGSEncounterZone::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSEncounterZone*, const T*>)
				{
					return static_cast<const BGSEncounterZone*>(this);
				}
			}
			break;

			case BGSLocation::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSLocation*, const T*>)
				{
					return static_cast<const BGSLocation*>(this);
				}
			}
			break;

			case BGSMessage::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSMessage*, const T*>)
				{
					return static_cast<const BGSMessage*>(this);
				}
			}
			break;

			case BGSRagdoll::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSRagdoll*, const T*>)
				{
					return static_cast<const BGSRagdoll*>(this);
				}
			}
			break;

			case BGSDefaultObjectManager::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSDefaultObjectManager*, const T*>)
				{
					return static_cast<const BGSDefaultObjectManager*>(this);
				}
			}
			break;

			case BGSLightingTemplate::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSLightingTemplate*, const T*>)
				{
					return static_cast<const BGSLightingTemplate*>(this);
				}
			}
			break;

			case BGSMusicType::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSMusicType*, const T*>)
				{
					return static_cast<const BGSMusicType*>(this);
				}
			}
			break;

			case BGSFootstep::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSFootstep*, const T*>)
				{
					return static_cast<const BGSFootstep*>(this);
				}
			}
			break;

			case BGSFootstepSet::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSFootstepSet*, const T*>)
				{
					return static_cast<const BGSFootstepSet*>(this);
				}
			}
			break;

			case BGSStoryManagerBranchNode::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSStoryManagerBranchNode*, const T*>)
				{
					return static_cast<const BGSStoryManagerBranchNode*>(this);
				}
			}
			break;

			case BGSStoryManagerQuestNode::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSStoryManagerQuestNode*, const T*>)
				{
					return static_cast<const BGSStoryManagerQuestNode*>(this);
				}
			}
			break;

			case BGSStoryManagerEventNode::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSStoryManagerEventNode*, const T*>)
				{
					return static_cast<const BGSStoryManagerEventNode*>(this);
				}
			}
			break;

			case BGSDialogueBranch::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSDialogueBranch*, const T*>)
				{
					return static_cast<const BGSDialogueBranch*>(this);
				}
			}
			break;

			case BGSMusicTrackFormWrapper::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSMusicTrackFormWrapper*, const T*>)
				{
					return static_cast<const BGSMusicTrackFormWrapper*>(this);
				}
			}
			break;

			case TESWordOfPower::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESWordOfPower*, const T*>)
				{
					return static_cast<const TESWordOfPower*>(this);
				}
			}
			break;

			case TESShout::TypeID:
			{
				if constexpr (std::is_convertible_v<const TESShout*, const T*>)
				{
					return static_cast<const TESShout*>(this);
				}
			}
			break;

			case BGSEquipSlot::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSEquipSlot*, const T*>)
				{
					return static_cast<const BGSEquipSlot*>(this);
				}
			}
			break;

			case BGSRelationship::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSRelationship*, const T*>)
				{
					return static_cast<const BGSRelationship*>(this);
				}
			}
			break;

			case BGSScene::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSScene*, const T*>)
				{
					return static_cast<const BGSScene*>(this);
				}
			}
			break;

			case BGSAssociationType::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSAssociationType*, const T*>)
				{
					return static_cast<const BGSAssociationType*>(this);
				}
			}
			break;

			case BGSOutfit::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSOutfit*, const T*>)
				{
					return static_cast<const BGSOutfit*>(this);
				}
			}
			break;

			case BGSArtObject::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSArtObject*, const T*>)
				{
					return static_cast<const BGSArtObject*>(this);
				}
			}
			break;

			case BGSMaterialObject::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSMaterialObject*, const T*>)
				{
					return static_cast<const BGSMaterialObject*>(this);
				}
			}
			break;

			case BGSMovementType::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSMovementType*, const T*>)
				{
					return static_cast<const BGSMovementType*>(this);
				}
			}
			break;

			case BGSSoundDescriptorForm::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSSoundDescriptorForm*, const T*>)
				{
					return static_cast<const BGSSoundDescriptorForm*>(this);
				}
			}
			break;

			case BGSDualCastData::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSDualCastData*, const T*>)
				{
					return static_cast<const BGSDualCastData*>(this);
				}
			}
			break;

			case BGSSoundCategory::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSSoundCategory*, const T*>)
				{
					return static_cast<const BGSSoundCategory*>(this);
				}
			}
			break;

			case BGSSoundOutput::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSSoundOutput*, const T*>)
				{
					return static_cast<const BGSSoundOutput*>(this);
				}
			}
			break;

			case BGSCollisionLayer::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSCollisionLayer*, const T*>)
				{
					return static_cast<const BGSCollisionLayer*>(this);
				}
			}
			break;

			case BGSColorForm::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSColorForm*, const T*>)
				{
					return static_cast<const BGSColorForm*>(this);
				}
			}
			break;

			case BGSReverbParameters::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSReverbParameters*, const T*>)
				{
					return static_cast<const BGSReverbParameters*>(this);
				}
			}
			break;

			case BGSLensFlare::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSLensFlare*, const T*>)
				{
					return static_cast<const BGSLensFlare*>(this);
				}
			}
			break;

			case BGSVolumetricLighting::TypeID:
			{
				if constexpr (std::is_convertible_v<const BGSVolumetricLighting*, const T*>)
				{
					return static_cast<const BGSVolumetricLighting*>(this);
				}
			}
			break;
		default:
			break;
		}

		return nullptr;
	}
}