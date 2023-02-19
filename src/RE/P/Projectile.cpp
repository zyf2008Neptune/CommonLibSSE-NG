#include "RE/P/Projectile.h"
#include "RE/A/AIProcess.h"
#include "RE/B/BipedAnim.h"
#include "RE/E/Effect.h"
#include "RE/F/FixedStrings.h"
#include "RE/F/FormTraits.h"
#include "RE/M/MagicCaster.h"
#include "RE/M/MiddleHighProcessData.h"

namespace RE
{
	Projectile::Manager* Projectile::Manager::GetSingleton()
	{
		REL::Relocation<Projectile::Manager**> singleton{ RELOCATION_ID(514313, 400473) };
		return *singleton;
	}

	float Projectile::GetHeight() const
	{
		auto obj = GetObjectReference();
		auto projectile = obj ? obj->As<BGSProjectile>() : nullptr;

		return projectile ? projectile->data.collisionRadius * 2 : 0.0f;
	}

	float Projectile::GetSpeed() const
	{
		auto obj = GetObjectReference();
		auto projectile = obj ? obj->As<BGSProjectile>() : nullptr;

		if (!projectile) {
			return 0.0f;
		}

		return projectile->data.speed * GetPowerSpeedMult() * GetWeaponSpeedMult() * speedMult;
	}

	RE::ProjectileHandle* Projectile::Launch(RE::ProjectileHandle* a_result, LaunchData& a_data) noexcept
	{
		using func_t = decltype(&Projectile::Launch);
		REL::Relocation<func_t> func{ RELOCATION_ID(42928, 44108) };
		return func(a_result, a_data);
	}

	RE::ProjectileHandle* Projectile::LaunchSpell(RE::ProjectileHandle* a_result, Actor* a_shooter, SpellItem* a_spell, const RE::NiPoint3& a_origin, const ProjectileRot& a_angles) noexcept
	{
		LaunchData ldata(a_shooter, a_origin, a_angles, a_spell);
		return Launch(a_result, ldata);
	}

	RE::ProjectileHandle* Projectile::LaunchSpell(RE::ProjectileHandle* a_result, Actor* a_shooter, SpellItem* a_spell, MagicSystem::CastingSource a_source) noexcept
	{
		auto mcaster = a_shooter->GetMagicCaster(a_source);
		if (!mcaster)
			return a_result;

		NiPoint3 origin;
		if (auto mnode = mcaster->GetMagicNode()) {
			origin = mnode->world.translate;
		} else {
			origin = a_shooter->GetPosition();
			auto bound_max = a_shooter->GetBoundMax();
			auto bound_min = a_shooter->GetBoundMin();
			origin.z += (bound_max.z - bound_min.z) * 0.7f;
		}

		// SE address is 140607AB0. Probably better to find AE address and call directly
		auto get_aimed_heading = [](Actor* a) -> float {
			float aimHeadingCurrent, heading = a->GetHeading(false);
			a->GetGraphVariableFloat(FixedStrings::GetSingleton()->aimHeadingCurrent, aimHeadingCurrent);
			return heading - aimHeadingCurrent;
		};

		// SE address is 140607B10. Probably better to find AE address and call directly
		auto get_aimed_rotation_X = [](Actor* a) -> float {
			auto strings = FixedStrings::GetSingleton();
			bool aim_active;
			a->GetGraphVariableBool(strings->bAimActive, aim_active);
			if (!aim_active)
				return a->data.angle.x;

			float aimPitchCurrent;
			a->GetGraphVariableFloat(FixedStrings::GetSingleton()->aimPitchCurrent, aimPitchCurrent);
			return -aimPitchCurrent;
		};

		ProjectileRot angles{ get_aimed_rotation_X(a_shooter), get_aimed_heading(a_shooter) };

		return LaunchSpell(a_result, a_shooter, a_spell, origin, angles);
	}

	RE::ProjectileHandle* Projectile::LaunchArrow(RE::ProjectileHandle* a_result, Actor* a_shooter, TESAmmo* a_ammo, TESObjectWEAP* a_weap, const NiPoint3& a_origin, const ProjectileRot& a_angles) noexcept
	{
		LaunchData ldata(a_shooter, a_origin, a_angles, a_ammo, a_weap);
		return Launch(a_result, ldata);
	}

	RE::ProjectileHandle* Projectile::LaunchArrow(RE::ProjectileHandle* a_result, Actor* a_shooter, TESAmmo* a_ammo, TESObjectWEAP* a_weap) noexcept
	{
		NiAVObject* fire_node;

		// SE address is 140607AB0. Probably better to find AE address and call directly
		auto get_aimed_heading = [](Actor* a) -> float {
			float aimHeadingCurrent, heading = a->GetHeading(false);
			a->GetGraphVariableFloat(FixedStrings::GetSingleton()->aimHeadingCurrent, aimHeadingCurrent);
			return heading - aimHeadingCurrent;
		};

		// SE address is 140607B10. Probably better to find AE address and call directly
		auto get_aimed_rotation_X = [](Actor* a) -> float {
			auto strings = FixedStrings::GetSingleton();
			bool aim_active;
			a->GetGraphVariableBool(strings->bAimActive, aim_active);
			if (!aim_active)
				return a->data.angle.x;

			float aimPitchCurrent;
			a->GetGraphVariableFloat(FixedStrings::GetSingleton()->aimPitchCurrent, aimPitchCurrent);
			return -aimPitchCurrent;
		};

		// SE address is 14067B3B0. Probably better to find AE address and call directly
		auto get_magicnode = [](AIProcess* proc, const auto& biped) -> NiAVObject* {
			return (proc->middleHigh && biped.get()) ? biped->root->GetObjectByName(FixedStrings::GetSingleton()->npcRMagicNode) : nullptr;
		};

		// SE address is 14067B170. Probably better to find AE address and call directly
		auto get_weaponnode = [](AIProcess* proc, const auto& biped) -> NiAVObject* {
			if (auto midhigh = proc->middleHigh) {
				if (biped.get()) {
					return biped->root->GetObjectByName(FixedStrings::GetSingleton()->weapon);
				} else {
					return midhigh->unk148;
				}
			} else {
				return nullptr;
			}
		};

		if (auto proc = a_shooter->currentProcess) {
			const auto& biped = a_shooter->GetBiped2();
			fire_node = a_weap->IsCrossbow() ? get_magicnode(proc, biped) : get_weaponnode(proc, biped);
		} else {
			// SE address is 140235070. Probably better to find AE address and call directly
			auto TESObjectWEAP__get_node = [](TESObjectWEAP* weap, NiAVObject* node) -> NiAVObject* {
				NiAVObject* ans;
				if (weap->weaponData.flags.all(TESObjectWEAP::Data::Flag::kEmbeddedWeapon) && !weap->embeddedNode.empty()) {
					ans = node->GetObjectByName(weap->embeddedNode);
				} else {
					ans = node->GetObjectByName("ProjectileNode");
				}

				if (!ans)
					ans = node->GetObjectByName("##ProjectileNode");

				return ans;
			};

			fire_node = TESObjectWEAP__get_node(a_weap, a_shooter->IsPlayerRef() ? a_shooter->GetCurrent3D() : a_shooter->Get3D2());
		}

		NiPoint3      origin;
		ProjectileRot angles;

		if (fire_node) {
			origin = fire_node->world.translate;
			a_shooter->Unk_A0(fire_node, &angles.x, &angles.z, &origin);
		} else {
			origin = a_shooter->GetPosition();
			origin.z += 96.0f;
			angles.x = get_aimed_rotation_X(a_shooter);
			angles.z = get_aimed_heading(a_shooter);
		}

		return LaunchArrow(a_result, a_shooter, a_ammo, a_weap, origin, angles);
	}

	Projectile::LaunchData::LaunchData(RE::BGSProjectile* a_bproj, RE::Actor* a_shooter, const NiPoint3& a_origin, const ProjectileRot& a_angles)
	{
		this->vftable = nullptr;
		this->origin = a_origin;
		this->contactNormal = { 0.0f, 0.0f, 0.0f };
		this->projectileBase = a_bproj;
		this->shooter = a_shooter;
		this->combatController = a_shooter->combatController;
		this->weaponSource = nullptr;
		this->ammoSource = nullptr;
		this->angleZ = a_angles.z;
		this->angleX = a_angles.x;
		this->unk50 = nullptr;
		this->desiredTarget = nullptr;
		this->unk60 = 0.0f;
		this->unk64 = 0.0f;
		this->parentCell = a_shooter->GetParentCell();
		this->spell = nullptr;
		this->castingSource = RE::MagicSystem::CastingSource::kOther;
		this->pad7C = 0;
		this->enchantItem = nullptr;
		this->poison = nullptr;
		this->area = 0;
		this->power = 1.0f;
		this->scale = 1.0f;
		this->alwaysHit = false;
		this->noDamageOutsideCombat = false;
		this->autoAim = true;
		this->unk9F = false;
		this->useOrigin = false;
		this->deferInitialization = false;
		this->forceConeOfFire = false;
	}

	Projectile::LaunchData::LaunchData(Actor* a_shooter,
		const NiPoint3& a_origin, const ProjectileRot& a_angles, MagicItem* a_spell) :
		Projectile::LaunchData::LaunchData(a_spell->GetAVEffectSetting()->data.projectileBase, a_shooter, a_origin, a_angles)
	{
		auto max_eff = a_spell->GetCostliestEffectItem();

		this->spell = a_spell;
		this->area = max_eff ? max_eff->GetArea() : 0;
		this->useOrigin = true;
		this->autoAim = false;
	}

	Projectile::LaunchData::LaunchData(RE::Actor* a_shooter,
		const RE::NiPoint3& a_origin, const ProjectileRot& a_angles, RE::TESAmmo* a_ammo,
		RE::TESObjectWEAP* a_weap) :
		Projectile::LaunchData::LaunchData(a_ammo->data.projectile, a_shooter, a_origin, a_angles)
	{
		this->weaponSource = a_weap;
		this->ammoSource = a_ammo;
		this->useOrigin = true;
		this->autoAim = false;
	}
}
