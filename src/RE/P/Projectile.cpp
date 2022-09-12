#include "RE/P/Projectile.h"

namespace RE
{
	BSPointerHandle<Projectile>* Projectile::Launch(BSPointerHandle<Projectile>* a_result, LaunchData& a_data) noexcept
	{
		using func_t = decltype(&Projectile::Launch);
		REL::Relocation<func_t> func{ RELOCATION_ID(42928, 44108) };
		return func(a_result, a_data);
	}
}
