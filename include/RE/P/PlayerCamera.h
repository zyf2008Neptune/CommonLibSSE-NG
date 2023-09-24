#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTSingleton.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/N/NiPoint3.h"
#include "RE/T/TESCamera.h"

namespace RE
{
	class bhkRigidBody;
	class bhkSimpleShapePhantom;
	class NiRefObject;
	class TESCameraState;

	struct CameraStates
	{
		enum CameraState : std::uint32_t
		{
			kFirstPerson = 0,
			kAutoVanity,
			kVATS,
			kFree,
			kIronSights,
			kFurniture,
			kPCTransition,
			kTween,
			kAnimated,
			kThirdPerson, // VR VrCameraState : TESCameraState : BSIntrusiveRefCounted
			kMount, // VR kThirdPerson ThirdPersonState : TESCameraState : BSIntrusiveRefCounted : PlayerInputHandler
			kBleedout, // VR kMount HorseCameraState : ThirdPersonState : TESCameraState : BSIntrusiveRefCounted : PlayerInputHandler
			kDragon, // VR kBleedout BleedoutCameraState : ThirdPersonState : TESCameraState : BSIntrusiveRefCounted : PlayerInputHandler
			
			kTotal, // VR kDragon DragonCameraState : ThirdPersonState : TESCameraState : BSIntrusiveRefCounted : PlayerInputHandler
			kVRTotal
		};
	};
	using CameraState = CameraStates::CameraState;

	class PlayerCamera :
		public TESCamera,                     // 000
		public BSTSingletonSDM<PlayerCamera>  // 038
	{
	public:
		inline static constexpr auto RTTI = RTTI_PlayerCamera;

		struct Unk120
		{
			NiPointer<bhkSimpleShapePhantom*> unk00;  // 00
			NiPointer<bhkSimpleShapePhantom*> unk08;  // 08
		};
		static_assert(sizeof(Unk120) == 0x10);

		~PlayerCamera() override;  // 00

		// override (TESCamera)
		void SetCameraRoot(NiPointer<NiNode> a_root) override;  // 01

		static PlayerCamera* GetSingleton();

		bool ForceFirstPerson();
		bool ForceThirdPerson();
		bool IsInBleedoutMode() const;
		bool IsInFirstPerson() const;
		bool IsInFreeCameraMode() const;
		bool IsInThirdPerson() const;
		void ToggleFreeCameraMode(bool a_freezeTime);
		void UpdateThirdPerson(bool a_weaponDrawn);

		// members
		std::uint8_t                                         pad039;                              // 039
		std::uint16_t                                        pad03A;                              // 03A
		ActorHandle                                          cameraTarget;                        // 03C
		BSTSmallArray<TESCameraState*, CameraStates::kTotal> tempReturnStates;                    // 040, VR 050
		BSTSmartPointer<TESCameraState>                      cameraStates[CameraStates::kTotal];  // 0B8, VR 0C0
		Unk120*                                              unk120;                              // 120, VR 130 - ?
		NiPointer<bhkRigidBody>                              rigidBody;                           // 128, VR 138 - ?
		RefHandle                                            objectFadeHandle;                    // 130, VR 140 - ?
		mutable BSSpinLock                                   lock;                                // 134, VR 144
		float                                                worldFOV;                            // 13C, VR 158
		float                                                firstPersonFOV;                      // 140, VR 15c
		NiPoint3                                             pos;                                 // 144, VR 160 - ?
		float                                                idleTimer;                           // 150, VR 16c - ?
		float                                                yaw;                                 // 154, VR 170 - ? - in radians
		std::uint32_t                                        unk158;                              // 158 - ?
		std::uint32_t                                        unk15C;                              // 15C - ?
		bool                                                 allowAutoVanityMode;                 // 160, VR 17c
		bool                                                 bowZoomedIn;                         // 161, VR 17d
		bool                                                 isWeapSheathed;                      // 162, VR 17e - ?
		bool                                                 isProcessed;                         // 163, VR 17f - ?
		std::uint8_t                                         unk164;                              // 164
		std::uint8_t                                         unk165;                              // 165
		std::uint16_t                                        pad166;                              // 166

	private:
		bool QCameraEquals(CameraState a_cameraState) const;
	};
	static_assert(sizeof(PlayerCamera) == 0x168);
}
