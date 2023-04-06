#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSSoundHandle.h"
#include "RE/B/bhkPickData.h"
#include "RE/M/MagicSystem.h"

namespace RE
{
	class Actor;
	class BGSSaveGameBuffer;
	class BGSLoadGameBuffer;
	class MagicItem;
	class NiNode;
	class TESObjectREFR;

	class MagicCaster
	{
	public:
		inline static constexpr auto RTTI = RTTI_MagicCaster;

		enum class State
		{
			kNone = 0,
			kUnk01,  // Start?
			kUnk02,  // StartCharge?
			kReady,
			kUnk04,  // PreStart?
			kCharging,
			kCasting,
			kUnk07,  // Unknown
			kUnk08,  // Interrupt
			kUnk09,  // Interrupt/Deselect
		};

		virtual ~MagicCaster();  // 00

		// add
		virtual void                       CastSpellImmediate(MagicItem* a_spell, bool a_noHitEffectArt, TESObjectREFR* a_target, float a_effectiveness, bool a_hostileEffectivenessOnly, float a_magnitudeOverride, Actor* a_blameActor);  // 01
		virtual void                       FindTouchTarget();                                                                                                                                                                               // 02
		virtual void                       RequestCastImpl();                                                                                                                                                                               // 03
		virtual bool                       StartChargeImpl();                                                                                                                                                                               // 04
		virtual void                       StartReadyImpl();                                                                                                                                                                                // 05
		virtual void                       StartCastImpl();                                                                                                                                                                                 // 06
		virtual void                       FinishCastImpl();                                                                                                                                                                                // 07 - { return; }
		virtual void                       InterruptCastImpl(bool a_depleteEnergy);                                                                                                                                                         // 08 - { return; }
		virtual void                       SpellCast(bool a_doCast, std::uint32_t a_arg2, MagicItem* a_spell);                                                                                                                              // 09 - { return; }
		virtual bool                       CheckCast(MagicItem* a_spell, bool a_dualCast, float* a_alchStrength, MagicSystem::CannotCastReason* a_reason, bool a_useBaseValueForCost);                                                      // 0A
		virtual TESObjectREFR*             GetCasterStatsObject() const;                                                                                                                                                                    // 0B - { return 0; }
		virtual Actor*                     GetCasterAsActor() const;                                                                                                                                                                        // 0C - { return 0; }
		virtual TESObjectREFR*             GetCasterObjectReference(Actor** a_outCaster) const;                                                                                                                                             // 0D
		virtual NiNode*                    GetMagicNode();                                                                                                                                                                                  // 0E - { return 0; }
		virtual void                       ClearMagicNode();                                                                                                                                                                                // 0F - { return; }
		virtual void                       SetCurrentSpellImpl(MagicItem* a_spell);                                                                                                                                                         // 10 - { return; }
		virtual void                       SelectSpellImpl();                                                                                                                                                                               // 11 - { return; }
		virtual void                       DeselectSpellImpl();                                                                                                                                                                             // 12 - { return; }
		virtual void                       SetSkipCheckCast();                                                                                                                                                                              // 13 - { return; }
		virtual void                       SetCastingTimerForCharge();                                                                                                                                                                      // 14
		virtual MagicSystem::CastingSource GetCastingSource() const;                                                                                                                                                                        // 15 - { return 0; }
		virtual bool                       GetIsDualCasting() const;                                                                                                                                                                        // 16 - { return 0; }
		virtual void                       SetDualCasting(bool a_set);                                                                                                                                                                      // 17 - { return; }
		virtual void                       SaveGame(BGSSaveGameBuffer* a_buf);                                                                                                                                                              // 18
		virtual void                       LoadGame(BGSLoadGameBuffer* a_buf);                                                                                                                                                              // 19
		virtual void                       FinishLoadGame(BGSLoadGameBuffer* a_buf);                                                                                                                                                        // 1A
		virtual void                       PrepareSound(MagicSystem::SoundID a_sound, MagicItem* a_spell);                                                                                                                                  // 1B
		virtual void                       AdjustActiveEffect(ActiveEffect* a_activeEffect, float a_power, bool a_arg3);                                                                                                                    // 1C

		MagicTarget* FindPickTarget(NiPoint3& a_targetLocation, TESObjectCELL** a_targetCell, bhkPickData& a_pickData)
		{
			using func_t = decltype(&MagicCaster::FindPickTarget);
			REL::Relocation<func_t> func{ RELOCATION_ID(33676, 34456) };
			return func(this, a_targetLocation, a_targetCell, a_pickData);
		}

		bool FindTargets(float a_effectivenessMult, std::uint32_t& a_targetCount, TESBoundObject* a_source, bool a_loadCast, bool a_adjustOnlyHostileEffectiveness)
		{
			using func_t = decltype(&MagicCaster::FindTargets);
			REL::Relocation<func_t> func{ RELOCATION_ID(33676, 34456) };
			return func(this, a_effectivenessMult, a_targetCount, a_source, a_loadCast, a_adjustOnlyHostileEffectiveness);
		}

		void FinishCast()
		{
			using func_t = decltype(&MagicCaster::FinishCast);
			REL::Relocation<func_t> func{ RELOCATION_ID(33657, 34435) };
			return func(this);
		}

		float GetCurrentSpellCost()
		{
			using func_t = decltype(&MagicCaster::GetCurrentSpellCost);
			REL::Relocation<func_t> func{ RELOCATION_ID(33426, 34204) };
			return func(this);
		}

		void InterruptCast(bool a_refund)
		{
			using func_t = decltype(&MagicCaster::InterruptCast);
			REL::Relocation<func_t> func{ RELOCATION_ID(33630, 34408) };
			return func(this, a_refund);
		}

		void PlayReleaseSound(MagicItem* a_item)
		{
			using func_t = decltype(&MagicCaster::PlayReleaseSound);
			REL::Relocation<func_t> func{ RELOCATION_ID(33675, 34448) };
			return func(this, a_item);
		}

		void UpdateImpl(float a_delta)
		{
			using func_t = decltype(&MagicCaster::UpdateImpl);
			REL::Relocation<func_t> func{ RELOCATION_ID(33622, 34400) };
			return func(this, a_delta);
		}

		bool TestProjectilePlacement(const Effect& a_effect, const bhkPickData& a_pickData);

		// members
		BSTArray<BSSoundHandle>                sounds;             // 08
		ObjectRefHandle                        desiredTarget;      // 20
		std::uint32_t                          pad24;              // 24
		MagicItem*                             currentSpell;       // 28
		stl::enumeration<State, std::uint32_t> state;              // 30
		float                                  castingTimer;       // 34
		float                                  currentSpellCost;   // 38
		float                                  magnitudeOverride;  // 3C
		float                                  nextTargetUpdate;   // 40
		float                                  projectileTimer;    // 44
	};
	static_assert(sizeof(MagicCaster) == 0x48);
}
