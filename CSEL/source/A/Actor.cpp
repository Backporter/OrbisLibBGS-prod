#include "../A/Actor.h"

#include "../A/AIProcess.h"

#include "../E/ExtraFactionChanges.h"

#include "../F/FormTraits.h"
#include "../B/BSAnimationGraphManager.h"

#include "../T/TESNPC.h"
#include "../T/TESRace.h"

namespace ConsoleRE
{ 

	bool					Actor::IsAMount() 
	{ 
		return (boolFlags & BOOL_FLAGS::kIsAMount) == BOOL_FLAGS::kIsAMount; 
	}

	bool					Actor::IsEssential()
	{ 
		return (boolFlags & BOOL_FLAGS::kEssential) == BOOL_FLAGS::kEssential; 
	}

	bool					Actor::IsOnMount()
	{
		return !IsAMount() && extraList.HasType(0xA9);
	}

	TESNPC*					Actor::GetActorBase()
	{
		auto obj = GetBaseObject();
		return obj ? obj->As<TESNPC>() : nullptr;
	}

	const TESNPC*			Actor::GetActorBase() const
	{
		auto obj = GetBaseObject();
		return obj ? obj->As<TESNPC>() : nullptr;
	}

	TESRace*				Actor::GetRace()
	{
		auto* _race = race;
		if (_race)
		{
			return _race;
		}

		auto base = GetActorBase();
		return base ? base->race : nullptr;
	}

	bool					Actor::AddAnimationGraphEventSink(BSTEventSink<BSAnimationGraphEvent>* a_sink)
	{
		BSTSmartPointer<BSAnimationGraphManager> graphManager;
		GetAnimationGraphManager(graphManager);

		if (graphManager)
		{
			bool sinked = false;
			for (const auto& animationGraph : graphManager->graphs)
			{
				if (sinked)
				{
					break;
				}

				const auto eventSource = animationGraph->GetEventSource<BSAnimationGraphEvent>();
				for (const auto& sink : eventSource->sinks)
				{
					if (sink == a_sink)
					{
						sinked = true;
						break;
					}
				}
			}

			if (!sinked)
			{
				graphManager->graphs.front()->GetEventSource<BSAnimationGraphEvent>()->AddEventSink(a_sink);
				return true;
			}
		}

		return false;
	}

	TESForm*				Actor::GetEquippedObject(bool a_left)
	{
		auto* _currentProcess = currentProcess;
		if (_currentProcess)
		{
			if (a_left)
			{
				return _currentProcess->GetEquippedInLeftHand();
			}
			else
			{
				return _currentProcess->GetEquippedInRightHand();
			}
		}
		else
		{
			return nullptr;
		}
	}

	void					Actor::UpdateHairColor()
	{
		const auto* npc = GetActorBase();
		if (npc && npc->headRelatedData)
		{
			const auto haircolor = npc->headRelatedData->hairColor;
			if (haircolor)
			{
				NiColor color;

				color.m_red		= static_cast<float>(haircolor->color.r) / static_cast<float>(128.0);
				color.m_green	= static_cast<float>(haircolor->color.g) / static_cast<float>(128.0);
				color.m_blue	= static_cast<float>(haircolor->color.b) / static_cast<float>(128.0);

				auto model = Get3D2(false);
				if (model)
				{
					model->UpdateHairColor(color);
				}
			}
		}
	}

	void					Actor::UpdateSkinColor()
	{
		const auto* npc = GetActorBase();
		if (npc)
		{
			NiColor color;

			color.m_red		= static_cast<float>(npc->bodyTintColor.r / 255.0f);
			color.m_green	= static_cast<float>(npc->bodyTintColor.g / 255.0f);
			color.m_blue	= static_cast<float>(npc->bodyTintColor.b / 255.0f);

			auto thirdPerson = Get3D2(false);
			if (thirdPerson)
			{
				thirdPerson->UpdateBodyTint(color);
			}

			auto firstPerson = Get3D2(true);
			if (firstPerson)
			{
				firstPerson->UpdateBodyTint(color);
			}
		}
	}

	bool					Actor::VisitFactions(std::function<bool(TESFaction*, int8_t)> a_visitor)
	{
		auto base = GetActorBase();
		if (base)
		{
			for (auto& factionInfo : base->factions)
			{
				if (a_visitor(factionInfo.faction, factionInfo.rank))
					return true;
			}

			auto factionChanges = extraList.GetByType<ExtraFactionChanges>();
			if (factionChanges)
			{
				for (auto& change : factionChanges->factionChanges)
				{
					if (a_visitor(change.faction, change.rank))
					{
						return true;
					}
				}
			}
		}

		return false;
	}

	bhkCharacterController* Actor::GetCharController()
	{
		if (currentProcess)
		{
			return currentProcess->GetCharController();
		}

		return nullptr;
	}

	bool					Actor::IsAnimationDriven()
	{
		bool result = false;
		return GetGraphVariableBool("bAnimationDriven", result) && result;
	}

	void					Actor::InterruptCast(bool a_restoreMagicka)
	{
		using func_t = decltype(&Actor::InterruptCast);
		Relocation<func_t> func("", 0x74AE00);
		return func(this, a_restoreMagicka);
	}

	bool					Actor::IsBlocking()
	{
		using func_t = bool(Actor* const);
		Relocation<func_t*> func("", 0x6DEED0);
		return func(this);
	}

	bool					Actor::IsCasting(MagicItem* a_spell)
	{
		using func_t = bool(Actor* const, MagicItem*);
		Relocation<func_t*> func("", 0x750F10);
		return func(this, a_spell);
	}

	bool					Actor::HasPerk(BGSPerk* a_perk)
	{
		using func_t = bool(decltype(this), BGSPerk*);
		Relocation<func_t*> func("", 0x7237B0);
		return func(this, a_perk);
	}

	void					Actor::StealAlarm(TESObjectREFR* a_ref, TESForm* a_object, int32_t a_num, int32_t a_total, TESForm* a_owner, bool a_allowWarning)
	{
		using func_t = void(*)(decltype(this), TESObjectREFR* a_ref, TESForm* a_object, int32_t a_num, int32_t a_total, TESForm* a_owner, bool a_allowWarning);
		Relocation<func_t> func("", 0x6EB5A0);
		return func(this, a_ref, a_object, a_num, a_total, a_owner, a_allowWarning);
	}

	int32_t					Actor::RequestDetectionLevel(Actor* a_target, uint32_t a_priority)
	{
		using func_t = int32_t(*)(decltype(this), Actor*, uint32_t);
		Relocation<func_t> func("", 0x6F9750);
		return func(this, a_target, a_priority);
	}

	void					Actor::UpdateWeaponAbility(TESForm* a_weapon, ExtraDataList* a_extraData, bool a_leftHand)
	{
		using func_t = void(decltype(this), TESForm*, ExtraDataList*, bool);
		Relocation<func_t*> func("", 0x74BA10);
		return func(this, a_weapon, a_extraData, a_leftHand);
	}

	void					Actor::UpdateArmorAbility(TESForm* a_armor, ExtraDataList* a_extraData)
	{
		using func_t = void(decltype(this), TESForm*, ExtraDataList*);
		Relocation<func_t*> func("", 0x74B9A0);
		return func(this, a_armor, a_extraData);
	}

	void					Actor::SetRotationZ(float a_angle)
	{
		using func_t = decltype(&Actor::SetRotationZ);
		Relocation<func_t> func("", 0x6D1FA0);
		return func(this, a_angle);
	}

	void					Actor::SetRotationX(float a_angle)
	{
		using func_t = decltype(&Actor::SetRotationX);
		Relocation<func_t> func("", 0x7186B0);
		return func(this, a_angle);
	}

	bool					Actor::AddSpell(SpellItem* a_spell)
	{
		using func_t = decltype(&Actor::AddSpell);
		Relocation<func_t> func("", 0x74C810);
		return func(this, a_spell);
	}

	bool					Actor::RemoveSpell(SpellItem* a_spell)
	{
		using func_t = decltype(&Actor::RemoveSpell);
		Relocation<func_t> func("", 0x74CAE0);
		return func(this, a_spell);
	}

	bool					Actor::HasLineOfSight(TESObjectREFR* a_ref, bool& a_arg2)
	{
		using func_t = decltype(&Actor::HasLineOfSight);
		Relocation<func_t> func("", 0xAD9E20);
		return func(this, a_ref, a_arg2);
	}

	void					Actor::EvaluatePackage(bool a_immediate, bool a_resetAI)
	{
		using func_t = decltype(&Actor::EvaluatePackage);
		Relocation<func_t> func("", 0x6DA810);
		return func(this, a_immediate, a_resetAI);
	}

	void					Actor::DoReset3D(bool a_updateWeight)
	{
		using func_t = decltype(&Actor::DoReset3D);
		Relocation<func_t> func("", 0x7CE840);
		return func(this, a_updateWeight);
	}
	

	void					Actor::SwapHeadPart(BGSHeadPart* a_old, BGSHeadPart* a_new)
	{
		using func_t = void(decltype(this), BGSHeadPart*, BGSHeadPart*);
		Relocation<func_t*> func("", 0x482040);
		return func(this, a_old, a_new);
	}

	bool                    Actor::IsHostileToActor(Actor* a_actor)
	{
		using func_t = decltype(&Actor::IsHostileToActor);
		Relocation<func_t> func("", 0x706B50);
		return func(this, a_actor);
	}
}