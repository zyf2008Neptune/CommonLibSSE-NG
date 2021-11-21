#pragma once

#include "RE/B/BSFaceGenManager.h"
#include "RE/B/BSFixedString.h"
using namespace RE;

namespace RE
{
	class BSFaceGenModelExtraData : public NiExtraData
	{
	public:
		BSFaceGenModel* m_model;   // 18
		BSFixedString   bones[8];  // 20
	};
#ifndef SKYRIMVR
	static_assert(sizeof(BSFaceGenModelExtraData) == 0x60);
#endif
}
