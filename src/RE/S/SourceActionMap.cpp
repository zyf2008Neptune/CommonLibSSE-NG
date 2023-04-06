#include "RE/S/SourceActionMap.h"

namespace RE
{
	namespace SourceActionMap
	{
		std::span<DEFAULT_OBJECT, 12> GetSingleton()
		{
			return {
				RE::DEFAULT_OBJECT::kActionLeftAttack,
				RE::DEFAULT_OBJECT::kActionLeftReady,
				RE::DEFAULT_OBJECT::kActionLeftRelease,
				RE::DEFAULT_OBJECT::kActionLeftInterrupt,
				RE::DEFAULT_OBJECT::kActionRightAttack,
				RE::DEFAULT_OBJECT::kActionRightReady,
				RE::DEFAULT_OBJECT::kActionRightRelease,
				RE::DEFAULT_OBJECT::kActionRightInterrupt,
				RE::DEFAULT_OBJECT::kActionVoice,
				RE::DEFAULT_OBJECT::kActionVoiceReady,
				RE::DEFAULT_OBJECT::kActionVoiceRelease,
				RE::DEFAULT_OBJECT::kActionVoiceInterrupt,
			};
		}

		bool DoAction(Actor* a_actor, DEFAULT_OBJECT a_action)
		{
			using func_t = decltype(&SourceActionMap::DoAction);
			REL::Relocation<func_t> func{ RELOCATION_ID(33423, 34202) };
			return func(a_actor, a_action);
		}
	}
}
