#include "RE/B/BSPCOrbisGamepadDevice.h"

namespace RE
{

	BSPCOrbisGamepadDevice::BSPCOrbisGamepadDevice() :
		BSPCGamepadDeviceDelegate(), previousPadState(), previousLT(), previousRT(), previousLX(), previousLY(), previousRX(), previousRY(), currentPadState(), currentLT(), currentRT(), currentLX(), currentLY(), currentRX(), currentRY()
	{
	}
}