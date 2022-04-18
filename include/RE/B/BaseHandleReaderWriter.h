#pragma once

#include "RE/I/IHandleReaderWriter.h"

namespace RE::SkyrimScript
{
	class BaseHandleReaderWriter : public RE::BSScript::IHandleReaderWriter
	{
	public:
		SKYRIM_ADDR static auto RTTI = RTTI_SkyrimScript__BaseHandleReaderWriter;
		SKYRIM_ADDR static auto VTABLE = VTABLE_SkyrimScript__BaseHandleReaderWriter;

		~BaseHandleReaderWriter() override;  // 0
	};
	static_assert(sizeof(BaseHandleReaderWriter) == 0x8);
}
