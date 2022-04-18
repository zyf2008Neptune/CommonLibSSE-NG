#include "RE/B/BSFaceGenNiNode.h"

using namespace REL;

namespace RE
{
#if !defined(ENABLE_SKYRIM_VR) || (!defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE))
	void BSFaceGenNiNode::FixSkinInstances(NiNode* a_skeleton, bool a_arg2)
	{
		RelocateVirtual<decltype(&BSFaceGenNiNode::FixSkinInstances)>(0x3E, 0x3F, this, a_skeleton, a_arg2);
	}
#endif
}
