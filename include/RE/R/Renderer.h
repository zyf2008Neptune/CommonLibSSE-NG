#pragma once

#include "RE/B/BSShaderRenderTargets.h"
#include "RE/N/NiTexture.h"
#include "RE/R/RenderTargetData.h"
#include "RE/T/TextureFileFormat.h"

struct ID3D11Device;
struct ID3D11DeviceContext;
struct IDXGISwapChain;
struct ID3D11RenderTargetView1;
struct ID3D11ShaderResourceView1;

namespace RE
{
	namespace BSGraphics
	{
		struct RendererWindow
		{
		public:
			// members
			SKSE::WinAPI::HWND         hWnd;                   // 10
			std::int32_t               windowX;                // 18
			std::int32_t               windowY;                // 1C
			std::int32_t               windowWidth;            // 20
			std::int32_t               windowHeight;           // 24
			IDXGISwapChain*            swapChain;              // 28
			RENDER_TARGET              swapChainRenderTarget;  // 30
			std::uint32_t              unk24;                  // 34
			std::uint64_t              unk28;                  // 38
			ID3D11RenderTargetView1*   renderView;             // 40
			ID3D11ShaderResourceView1* resourceView;           // 48
			std::uint64_t              unk40;                  // 50
			std::uint64_t              unk48;                  // 58
		};
		static_assert(sizeof(RendererWindow) == 0x50);

		struct RendererData2
		{
		public:
#define RENDERER_DATA2_CONTENT                                                                              \
	CubemapRenderTargetData        cubemapRenderTargets[RENDER_TARGET_CUBEMAP::kTOTAL]; /* 26D8, VR 2E48 */ \
	Texture3DTargetData            texture3DRenderTargets[RENDER_TARGET_3D::kTOTAL];    /* 2718, VR 2E88*/  \
	float                          clearColor[4];                                       /* 2778, VR 2EE8*/  \
	std::uint8_t                   clearStencil;                                        /* 2788, VR 2EF8*/  \
	SKSE::WinAPI::CRITICAL_SECTION lock;                                                /* 2790, VR 2F00*/  \
	const char*                    className;                                           /* 27B8, VR 2F28*/  \
	SKSE::WinAPI::HINSTANCE        hInstance;                                           /* 27C0, VR 2F30*/
            RENDERER_DATA2_CONTENT
		};

		struct DepthStencilRuntimeData
		{
		public:
#ifndef ENABLE_SKYRIM_VR
#	define DEPTHSTENCIL_RUNTIME_DATA_CONTENT \
		DepthStencilData depthStencils[RENDER_TARGET_DEPTHSTENCIL::kTOTAL]; /* 1FB8, VR 21D0*/
//#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
#else
#	define DEPTHSTENCIL_RUNTIME_DATA_CONTENT \
		DepthStencilData depthStencils[RENDER_TARGET_DEPTHSTENCIL::kVRTOTAL]; /* 1FA8*/
#endif
			DEPTHSTENCIL_RUNTIME_DATA_CONTENT
		};

		struct RendererData
		{
		public:
			// members
#ifndef ENABLE_SKYRIM_VR
#	define RUNTIME_DATA_CONTENT                                                               \
		std::uint32_t        uiAdapter;                              /* 0018 */                \
		std::uint32_t        unk04;                                  /* 001C - refreshRate? */ \
		std::uint32_t        unk08;                                  /* 0020 */                \
		std::uint32_t        unk0C;                                  /* 0024*/                 \
		std::uint32_t        unk10;                                  /* 0028*/                 \
		std::uint32_t        unk14;                                  /* 002C*/                 \
		std::uint32_t        unk18;                                  /* 0030*/                 \
		std::uint32_t        unk1C;                                  /* 0034*/                 \
		bool                 fullScreen;                             /* 0038*/                 \
		bool                 borderlessDisplay;                      /* 0039*/                 \
		bool                 readOnlyDepth;                          /* 003A*/                 \
		bool                 unk23;                                  /* 003B*/                 \
		bool                 unk24;                                  /* 003C*/                 \
		bool                 unk25;                                  /* 003D*/                 \
		std::uint32_t        unk28;                                  /* 0038*/                 \
		std::uint32_t        unk30;                                  /* 0040*/                 \
		std::uint32_t        presentInterval;                        /* 004C*/                 \
		ID3D11Device*        forwarder;                              /* 0050*/                 \
		ID3D11DeviceContext* context;                                /* 0058*/                 \
		RendererWindow       renderWindows[32];                      /* 0060*/                 \
		RenderTargetData     renderTargets[RENDER_TARGET::kVRTOTAL]; /* 0A60*/
#else
#	define RUNTIME_DATA_CONTENT                                                             \
		std::uint32_t        uiAdapter;                            /* 0010 */                \
		std::uint32_t        unk04;                                /* 0014 - refreshRate? */ \
		std::uint32_t        unk08;                                /* 0018 */                \
		std::uint32_t        unk0C;                                /* 001C*/                 \
		std::uint32_t        unk10;                                /* 0020*/                 \
		std::uint32_t        unk14;                                /* 0024*/                 \
		std::uint32_t        unk18;                                /* 0028*/                 \
		std::uint32_t        unk1C;                                /* 002C*/                 \
		bool                 fullScreen;                           /* 0030*/                 \
		bool                 borderlessDisplay;                    /* 0031*/                 \
		bool                 readOnlyDepth;                        /* 0032*/                 \
		bool                 unk23;                                /* 0033*/                 \
		bool                 unk24;                                /* 0034*/                 \
		bool                 unk25;                                /* 0035*/                 \
		std::uint32_t        unk28;                                /* 0038*/                 \
		std::uint32_t        unk30;                                /* 0040*/                 \
		std::uint32_t        presentInterval;                      /* 0044*/                 \
		ID3D11Device*        forwarder;                            /* 0048*/                 \
		ID3D11DeviceContext* context;                              /* 0050*/                 \
		RendererWindow       renderWindows[32];                    /* 0058*/                 \
		RenderTargetData     renderTargets[RENDER_TARGET::kTOTAL]; /* 0A58*/
#endif
			RUNTIME_DATA_CONTENT;
		};
#ifndef ENABLE_SKYRIM_VR
		static_assert(sizeof(RendererData) == 0x21B8);
		static_assert(offsetof(RendererData, context) == 0x40);
		static_assert(offsetof(RendererData, renderTargets) == 0xa48);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
		static_assert(sizeof(RendererData) == 0x1fa8);
		static_assert(offsetof(RendererData, context) == 0x40);
		static_assert(offsetof(RendererData, renderTargets) == 0xa48);
#else
		static_assert(sizeof(RendererData) == 0x1fa8);
		static_assert(offsetof(RendererData, context) == 0x40);
		static_assert(offsetof(RendererData, renderTargets) == 0xa48);
#endif

		class Renderer
		{
		public:
			[[nodiscard]] inline RendererData& GetRuntimeData() noexcept
			{
				return REL::RelocateMember<RendererData>(this, 0x10, 0x18);
			}

			[[nodiscard]] inline const RendererData& GetRuntimeData() const noexcept
			{
				return REL::RelocateMember<RendererData>(this, 0x10, 0x18);
			}

			[[nodiscard]] inline DepthStencilRuntimeData& GetDepthStencilData() noexcept
			{
				return REL::RelocateMember<DepthStencilRuntimeData>(this, 0x1FB8, 0x21D0);
			}

			[[nodiscard]] inline const DepthStencilRuntimeData& GetDepthStencilData() const noexcept
			{
				return REL::RelocateMember<DepthStencilRuntimeData>(this, 0x1FB8, 0x21D0);
			}

			[[nodiscard]] inline RendererData2& GetRendererData() noexcept
			{
				return REL::RelocateMember<RendererData2>(this, 0x26D8, 0x2E48);
			}

			[[nodiscard]] inline const RendererData2& GetRendererData() const noexcept
			{
				return REL::RelocateMember<RendererData2>(this, 0x26D8, 0x2E48);
			}
			[[nodiscard]] inline SKSE::WinAPI::CRITICAL_SECTION& GetLock() noexcept
			{
				return REL::RelocateMember<SKSE::WinAPI::CRITICAL_SECTION>(this, 0x2790, 0x2F00);
			}

			[[nodiscard]] inline const SKSE::WinAPI::CRITICAL_SECTION& GetLock() const noexcept
			{
				return REL::RelocateMember<SKSE::WinAPI::CRITICAL_SECTION>(this, 0x2790, 0x2F00);
			}

			[[nodiscard]] static Renderer* GetSingleton() noexcept;

			[[nodiscard]] NiTexture::RendererData* CreateRenderTexture(std::uint32_t a_width, std::uint32_t a_height);
			void                                   SaveRenderTargetToFile(RENDER_TARGET a_renderTarget, const char* a_filePath, TextureFileFormat a_textureFileFormat);

			// members
			std::uint64_t unk000;      // 0000
			bool          drawStereo;  // 0008
#ifndef ENABLE_SKYRIM_VR
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
			std::uint64_t unk010;  // 0010
#endif
			RUNTIME_DATA_CONTENT;  // 0010, VR 18
		};
#ifndef ENABLE_SKYRIM_VR
		static_assert(sizeof(Renderer) == 0x21C0);
#elif !defined(ENABLE_SKYRIM_AE) && !defined(ENABLE_SKYRIM_SE)
		static_assert(sizeof(Renderer) == 0x1fc0);
#else
		static_assert(sizeof(Renderer) == 0x1fb0);
#endif
	}
}
#undef RUNTIME_DATA_CONTENT
#undef DEPTHSTENCIL_RUNTIME_DATA_CONTENT
#undef RENDERER_DATA2_CONTENT
