#include "RE/M/MagicCaster.h"

#include "RE/E/Effect.h"
#include "RE/E/EffectSetting.h"
#include "RE/H/hkpCollidable.h"

namespace RE
{
	bool MagicCaster::TestProjectilePlacement(const Effect& a_effect, const bhkPickData& a_pickData)
	{
		if (auto baseEffect = a_effect.baseEffect) {
			if (baseEffect->data.delivery == RE::MagicSystem::Delivery::kTargetLocation) {
				if (baseEffect->data.projectileBase) {
					if (a_pickData.unkC0) {
						return false;
					}

					if (!a_pickData.rayOutput.rootCollidable) {
						return false;
					}

					auto broadPhaseHandle = a_pickData.rayOutput.rootCollidable->broadPhaseHandle;
					if ((broadPhaseHandle.collisionFilterInfo & 0x7F) != 0x01 &&
						(broadPhaseHandle.collisionFilterInfo & 0x7F) != 0x0D &&
						(broadPhaseHandle.collisionFilterInfo & 0x7F) != 0x11) {
						return false;
					}
				}
			}
		}

		return true;
	}
}
