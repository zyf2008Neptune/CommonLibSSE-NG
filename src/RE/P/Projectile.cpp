#include "RE/P/Projectile.h"
#include "RE/F/FormTraits.h"

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

	BSPointerHandle<Projectile>* Projectile::Launch(BSPointerHandle<Projectile>* a_result, LaunchData& a_data) noexcept
	{
		using func_t = decltype(&Projectile::Launch);
		REL::Relocation<func_t> func{ RELOCATION_ID(42928, 44108) };
		return func(a_result, a_data);
	}
}
