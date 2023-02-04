#include "RE/E/ExtraTeleport.h"

namespace RE
{
	DoorTeleportData::DoorTeleportData() :
		linkedDoor(),
		position(),
		rotation(),
		flags(0),
		pad1D(0),
		pad1E(0)
	{}

	ExtraTeleport::ExtraTeleport() :
		BSExtraData(),
		teleportData(new DoorTeleportData())
	{
		stl::emplace_vtable(this);
	}

	ExtraDataType ExtraTeleport::GetType() const
	{
		return ExtraDataType::kTeleport;
	}

	bool ExtraTeleport::IsNotEqual(const BSExtraData* a_rhs) const
	{
        const auto rhsData = static_cast<const ExtraTeleport*>(a_rhs)->teleportData;
		if (teleportData->linkedDoor == rhsData->linkedDoor && teleportData->position == rhsData->position && teleportData->rotation == rhsData->rotation) {
			return teleportData->flags != rhsData->flags;
		} else {
			return true;
		}
	}
}
