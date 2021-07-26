#include "RE/I/IFormFactory.h"

namespace RE
{
	std::pair<IFormFactory**, bool> IFormFactory::GetFormFactories()
	{
		struct Factories
		{
			IFormFactory* data[stl::to_underlying(FormType::Max)];
		};

#ifndef SKYRIMVR
		REL::Relocation<Factories*> formFactories{ REL::ID(514355) };
		REL::Relocation<bool*>      formFactoriesInitialized{ REL::ID(514349) };
#else
		REL::Relocation<Factories*> formFactories{ REL::Offset(0x1f88b40) };
		REL::Relocation<bool*>      formFactoriesInitialized{ REL::Offset(0x1f88b13) };
#endif
		return std::make_pair(formFactories->data, *formFactoriesInitialized);
	}

	IFormFactory* IFormFactory::GetFormFactoryByType(FormType a_formType)
	{
		auto formFactories = GetFormFactories();
		return formFactories.second ? formFactories.first[static_cast<std::uint32_t>(a_formType)] : nullptr;
	}

	TESForm* IFormFactory::Create()
	{
		return CreateImpl();
	}
}
