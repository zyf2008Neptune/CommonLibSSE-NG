# CommonLibSSE NG
[![C++23](https://img.shields.io/static/v1?label=standard&message=C%2B%2B20&color=blue&logo=c%2B%2B&&logoColor=white&style=flat)](https://en.cppreference.com/w/cpp/compiler_support)
[![Platform](https://img.shields.io/static/v1?label=platform&message=windows&color=dimgray&style=flat)](#)
[![Main CI](https://github.com/CharmedBaryon/CommonLibSSE-NG/actions/workflows/main_ci.yml/badge.svg)](https://github.com/CharmedBaryon/CommonLibSSE-NG/actions/workflows/main_ci.yml)

CommonLibSSE NG is a fork of CommonLibSSE which tracks upstream updates but adds a number of enhancements:
* Can be compiled with Clang 13.x+ with MSVC ABI compatibility.
  [More information...](https://github.com/CharmedBaryon/CommonLibSSE-NG/wiki/Compiling-with-Clang)
* Dynamic cross-runtime support (ability to produce a single DLL that works on AE, SE, or VR), with access to all
  cross-compatible features.
  [More information...](https://github.com/CharmedBaryon/CommonLibSSE-NG/wiki/Runtime-Targeting)
* Complete support (up to modern RE standards) for Skyrim VR, including the ability to use Skyrim VR and Skyrim SE
  functionality from a single DLL build even where Skyrim VR is normally ABI-incompatible.
  [More information...](https://github.com/CharmedBaryon/CommonLibSSE-NG/wiki/Runtime-Targeting)
* Support for Address Libraries for SE, AE, and VR.
  [More information...](https://github.com/CharmedBaryon/CommonLibSSE-NG/wiki/Runtime-Targeting)
* Ability to build locked to a single runtime, where access to non-portable features is needed.
  [More information...](https://github.com/CharmedBaryon/CommonLibSSE-NG/wiki/Runtime-Targeting)
* Ability to define offsets and address IDs for objects which can exist in only a subset of runtimes, while being able
  dynamically test for feature support before using those offsets.
* Completely regenerated RTTI and vtable offsets, now with consistent naming and access across all runtimes.
* Updated GitHub Actions CI workflows to build for all likely target runtime combinations.
* Fully extensible native function binding traits (enables custom script object bindings in
  [Fully Dynamic Game Engine](https://gitlab.com/colorglass/fully-dynamic-game-engine)).
* Unit testing support (can be run without being hosted in a Skyrim executable).
* Better support for the CLion IDE.
* Uses modern Vcpkg manifest version feature and assigns semantic versions to specific CommonLibSSE NG releases.
* Upgrades the build system to Ninja for faster builds.
* Provides distribution through Vcpkg rather than requiring import as a Git submodule.

## Use
CommonLibSSE NG is available as a Vcpkg port. To add it to your project, create a `vcpkg-configuration.json` file in the
project root (next to `vcpkg.json`) with the following contents:

```json
{
    "registries": [
        {
            "kind": "git",
            "repository": "https://gitlab.com/colorglass/vcpkg-colorglass",
            // Update this baseline to the latest commit from the above repo.
            "baseline": "7abd808aa0ae8d65710f3a9f77f15937530309aa",
            "packages": [
                "commonlibsse-ng",
                "commonlibsse-ng-prebuilt",
                "commonlibsse-ng-ae",
                "commonlibsse-ng-se",
                "commonlibsse-ng-vr",
                "commonlibsse-ng-flatrim"
            ]
        }
    ]
}
```

Then add `commonlibsse-ng` as a dependency in `vcpkg.json`. There are also runtime-specific versions of the project:
* `commonlibsse-ng-ae`: Supports AE executables (1.6.x) only.
* `commonlibsse-ng-se`: Supports pre-AE executables (1.5.x) only.
* `commonlibsse-ng-vr`: Supports VR only.
* `commonlibsse-ng-flatrim`: Support for SE/AE, but not VR.
* `commonlibsse-ng-prebuilt`: A prebuilt binary for CommonLibSSE NG, avoids the overhead of compiling it. Recommended to
  be used only with `x64-windows-static-md` triplet (or equivalent custom one), but can also be used with
  `x64-windows-static` (or custom equivalent) if your project links against a compatible version of the MSVC 2022 CRT.

The runtime-specific ports will not attempt to dynamically lookup the version of Skyrim at runtime, and will enable
access to reverse engineered content that is specific to that version of Skyrim and non-portable (i.e. it does not exist
in all versions of Skyrim, or has not been reverse engineered on all versions of Skyrim).

You should have the following in `CMakeLists.txt` to compile and link successfully:
```cmake
find_package(CommonLibSSE REQUIRED)
# ...
target_link_libraries(${PROJECT_NAME} PUBLIC CommonLibSSE::CommonLibSSE)
```

For more information on how to use CommonLibSSE NG, you can look at the
[example plugin](https://gitlab.com/colorglass/commonlibsse-sample-plugin).

## Build Dependencies
* [Boost](https://www.boost.org/)
	* Stl_interfaces
* [spdlog](https://github.com/gabime/spdlog)
* [Visual Studio Community 2019 16.10.0 Preview 3.0](https://visualstudio.microsoft.com/vs/preview/)
	* Desktop development with C++

## End User Dependencies
* [Address Library for SKSE Plugins](https://www.nexusmods.com/skyrimspecialedition/mods/32444)
* [SKSE64](https://skse.silverlock.org/)

## Development
* [Address Library for SKSE Plugins](https://www.nexusmods.com/skyrimspecialedition/mods/32444)
* [clang-format 12.0.0](https://github.com/llvm/llvm-project/releases)
* [CMake](https://cmake.org/)
* [vcpkg](https://github.com/microsoft/vcpkg)

## Notes
* CommonLib is incompatible with SKSE and is intended to replace it as a static dependency. However, you will still need the runtime component.
