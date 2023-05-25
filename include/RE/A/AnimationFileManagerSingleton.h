#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTSingleton.h"
#include "RE/H/hkbContext.h"
#include "RE/I/IAnimationClipLoaderSingleton.h"

namespace RE
{
	class hkbClipGenerator;

	class AnimationFileManagerSingleton :
		public IAnimationClipLoaderSingleton,
		public BSTSingletonSDM<AnimationFileManagerSingleton>
	{
	public:
		inline static auto RTTI = RTTI_AnimationFileManagerSingleton;
		inline static auto VTABLE = VTABLE_AnimationFileManagerSingleton;

		struct UnkData
		{
			uint32_t crc32Filename;   // 00
			uint32_t crc32Extension;  // 04
			uint32_t crc32Path;       // 08
		};

		struct QueuedAnimation
		{
			uint32_t unk00;  // 00
			UnkData  data;   // 04
		};
		static_assert(sizeof(QueuedAnimation) == 0x10);

		struct LoadedAnimation
		{
			void*    unk00;    // 00
			UnkData  data;     // 08
			uint16_t counter;  // 14
		};
		static_assert(sizeof(LoadedAnimation) == 0x18);

		virtual ~AnimationFileManagerSingleton() override;  // 00

		// override (IAnimationClipLoaderSingleton)
		virtual std::int32_t Unk_01(const hkbContext& a_hkbContext, hkbClipGenerator* a_clipGenerator, BSSynchronizedClipGenerator* a_synchronizedClipGenerator);  // 01 - called in hkbClipGenerator::Activate, possibly loads animation (queues it?)
		virtual bool         Unk_02(const hkbContext& a_hkbContext, hkbClipGenerator* a_clipGenerator, BSSynchronizedClipGenerator* a_synchronizedClipGenerator);  // 02 - called in hkbClipGenerator::Update, possibly loads animation
		virtual std::int32_t Unk_03(const hkbContext& a_hkbContext, hkbClipGenerator* a_clipGenerator, BSSynchronizedClipGenerator* a_synchronizedClipGenerator);  // 03 - called in hkbClipGenerator::Deactivate, possibly unloads animation
		virtual void         Unk_04(const hkbContext& a_context, std::int16_t a_animationBindingIndex);                                                            // 04
		virtual void         Unk_05(const hkbContext& a_context, std::int16_t a_animationBindingIndex);                                                            // 05

		[[nodiscard]] static AnimationFileManagerSingleton* GetSingleton()
		{
			REL::Relocation<AnimationFileManagerSingleton**> singleton{ RELOCATION_ID(520994, 407512) };
			return *singleton;
		}

	    // members
		BSSpinLock                lockA;             // 0C
		BSSpinLock                lockB;             // 14
		LoadedAnimation           currentAnimation;  // 20
		BSTArray<QueuedAnimation> queuedAnimations;  // 38
		BSTArray<LoadedAnimation> loadedAnimations;  // 50
		BSTArray<void*>           unk68;             // 68
		uint64_t                  unk80;             // 80
		BSTArray<void*>           unk88;             // 88
	};
	static_assert(sizeof(AnimationFileManagerSingleton) == 0xA0);
}
