# `CommonLibSSE/CommonLibVR`
[![C++20](https://img.shields.io/static/v1?label=standard&message=C%2B%2B20&color=blue&logo=c%2B%2B&&logoColor=white&style=flat)](https://en.cppreference.com/w/cpp/compiler_support)
[![Platform](https://img.shields.io/static/v1?label=platform&message=windows&color=dimgray&style=flat)](#)
[![Main CI](https://img.shields.io/github/workflow/status/Ryan-rsm-McKenzie/CommonLibSSE/Main%20CI?logo=github&logoColor=white)](https://github.com/Ryan-rsm-McKenzie/CommonLibSSE/actions/workflows/main_ci.yml)

This a version of CommonLibVR that is based off of the latest CommonLibSSE after the cmake migration. It is meant to also work in SSE.
## Build Dependencies
* [Boost](https://www.boost.org/)
	* Stl_interfaces
* [spdlog](https://github.com/gabime/spdlog)
* [Visual Studio Community 2019 16.10.0 Preview 3.0](https://visualstudio.microsoft.com/vs/preview/)
	* Desktop development with C++

## Building
```
git clone https://github.com/alandtse/CommonLibVR.git
cd CommonLibVR
git checkout vr

# Skyrim SE
cmake -B build -S .

# Skyrim VR
cmake -B buildVR -S . -DBUILD_SKYRIMVR=ON
```

## End User Dependencies SSE
* [Address Library for SKSE Plugins](https://www.nexusmods.com/skyrimspecialedition/mods/32444)
* [SKSE64](https://skse.silverlock.org/)

## End User Dependencies VR
* [VR Address Library from vr_address_tools](https://github.com/alandtse/vr_address_tools/releases)
* [SKSEVR](https://skse.silverlock.org/)

## Development
* [Address Library for SKSE Plugins](https://www.nexusmods.com/skyrimspecialedition/mods/32444)
* [clang-format 12.0.0](https://github.com/llvm/llvm-project/releases)
* [CMake](https://cmake.org/)
* [vcpkg](https://github.com/microsoft/vcpkg)

## Notes
* CommonLibSSE/VR is incompatible with SKSE/SKSEVR and is intended to replace it as a static dependency. However, you will still need the runtime component.

## Credits
* Thanks to Ryan McKenzie for original code
* Thanks to RollingRock & po3 for important contributions
* Thanks to lfrazer for commonlibvr port which is the source of Exit-9B recombination; also thanks for all the support in discord.
* Thanks to Exit-9B for recombination of [CommonLibSSE](https://github.com/Ryan-rsm-McKenzie/CommonLibSSE) and [CommonLibVR](https://github.com/lfrazer/CommonLibVR)
