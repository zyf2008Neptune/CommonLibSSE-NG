# Changelog

## [Unreleased]

## [2.1.0]
* Sync to upstream changes as of EOD 4/8/2022.
* Migrate build system to Ninja.
* Change to use Vcpkg's semantic versioning support.
* Documentation updates.
* Added this changelog.

## [2.0.0]
* Rewrite of RELOCATION_ID into REL::RelocationID function, which can now support variant VR IDs.
* Rewrite of RELOCATION into REL::Relocate, which can now support variant VR offsets.

## [1.0.0]
* Overhaul of upstream to handle RELOCATION_ID dynamically, to allow single DLL for all versions of Skyrim.
* Added RELOCATION macro.
* Allow running without a Skyrim module, for unit testing.
* Assign specific version in Vcpkg.
* Integrate CommonLibVR's support for VR Address Library CSV files.
* Refactor the AE support macro into separate macros for forcing single-runtime DLL builds.
* Added workarounds for common CLion issues.
* Refactor to not require forward declarations of overloads of `GetRawType`, necessary to support Fully Dynamic Game
  Engine's extensible script objects feature.
