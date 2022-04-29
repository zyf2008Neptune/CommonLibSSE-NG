#pragma once

#include "RE/A/ActiveEffect.h"
#include "RE/B/BGSRefAlias.h"
#include "RE/B/BSFixedString.h"
#include "RE/F/FunctionArguments.h"
#include "RE/I/IObjectHandlePolicy.h"
#include "RE/T/TESForm.h"
#include "RE/T/TESObjectREFR.h"
#include "RE/T/TypeTraits.h"
#include "RE/V/VirtualMachine.h"

#include "SKSE/API.h"
#include "SKSE/Impl/RegistrationTraits.h"
#include "SKSE/Interfaces.h"
#include "SKSE/Logger.h"

namespace SKSE
{
	template <class... Filter>
	class RegistrationFilter
	{
	protected:
		using FilterTuple = std::tuple<Filter...>;
		using Key = std::pair<FilterTuple, bool>;

		using FilterMatchFunc = std::function<bool(const FilterTuple&, bool)>;

		class MapUniqueBase
		{
		public:
			using UniqueHandle = std::pair<RE::FormID, RE::VMHandle>;

			MapUniqueBase() = delete;
			MapUniqueBase(const std::string_view& a_eventName);
			MapUniqueBase(const MapUniqueBase& a_rhs);
			MapUniqueBase(MapUniqueBase&& a_rhs) noexcept;
			~MapUniqueBase();

			MapUniqueBase& operator=(const MapUniqueBase& a_rhs);
			MapUniqueBase& operator=(MapUniqueBase&& a_rhs) noexcept;

			bool Register(RE::ActiveEffect* a_activeEffect, Key a_key);
			bool Register(RE::BGSRefAlias* a_alias, Key a_key);
			bool Unregister(RE::ActiveEffect* a_activeEffect, Key a_key);
			bool Unregister(RE::BGSRefAlias* a_alias, Key a_key);
			void UnregisterAll(RE::ActiveEffect* a_activeEffect);
			void UnregisterAll(RE::BGSRefAlias* a_alias);
			void UnregisterAll(RE::VMHandle a_handle);
			void Clear();
			bool Save(SerializationInterface* a_intfc, std::uint32_t a_type, std::uint32_t a_version);
			bool Save(SerializationInterface* a_intfc);
			bool Load(SerializationInterface* a_intfc);
			void Revert(SerializationInterface*);

		protected:
			using Lock = std::recursive_mutex;
			using Locker = std::lock_guard<Lock>;

			bool Register(const void* a_object, RE::FormID a_formID, Key a_key, RE::VMTypeID a_typeID);
			bool Unregister(const void* a_object, RE::FormID a_formID, Key a_key, RE::VMTypeID a_typeID);
			void UnregisterAll(const void* a_object, RE::FormID a_formID, RE::VMTypeID a_typeID);

			template <typename Function, typename Tuple>
			void for_each_filter(Function&& a_function, Tuple&& a_tuple)
			{
				std::apply([&a_function](auto&&... a_args) { (a_function(std::forward<decltype(a_args)>(a_args)), ...); }, std::forward<Tuple>(a_tuple));
			}

			template <class T>
			void LoadFilter(SerializationInterface* a_intfc, T& a_filter)
			{
				if constexpr (std::is_same_v<RE::FormID, T>) {
					RE::FormID formID;
					a_intfc->ReadRecordData(formID);
					a_intfc->ResolveFormID(formID, formID);
					a_filter = formID;
				} else {
					T value{};
					a_intfc->ReadRecordData(value);
					a_filter = value;
				}
			}

			std::map<Key, std::set<UniqueHandle>> _regs;
			std::string                           _eventName;
			mutable Lock                          _lock;
		};

	public:
		template <class Enable, class... Args>
		class MapUnique;

		template <class... Args>
		class MapUnique<
			std::enable_if_t<
				std::conjunction_v<
					RE::BSScript::is_return_convertible<Args>...>>,
			Args...> :
			public MapUniqueBase
		{
		private:
			using super = MapUniqueBase;

		public:
			MapUnique() = delete;
			MapUnique(const MapUnique&) = default;
			MapUnique(MapUnique&&) = default;

			inline MapUnique(const std::string_view& a_eventName) :
				super(a_eventName)
			{}

			~MapUnique() = default;

			MapUnique& operator=(const MapUnique&) = default;
			MapUnique& operator=(MapUnique&&) = default;

			inline void SendEvent(const RE::TESObjectREFR* a_target, FilterMatchFunc a_callback, Args... a_args)
			{
				RE::BSFixedString eventName(this->_eventName);

				if (auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton()) {
					for (auto& [key, handles] : this->_regs) {
						if (auto& [filters, match] = key; a_callback(filters, match)) {
							const auto targetFormID = a_target->GetFormID();
							for (auto& [formID, vmHandle] : handles) {
								if (formID == targetFormID) {
									auto args = RE::MakeFunctionArguments(std::forward<Args>(a_args)...);
									vm->SendEvent(vmHandle, eventName, args);
								}
							}
						}
					}
				}
			}

			inline void QueueEvent(RE::TESObjectREFR* a_target, FilterMatchFunc a_callback, Args... a_args)
			{
				std::tuple args(Impl::VMArg(std::forward<Args>(a_args))...);
				auto       task = GetTaskInterface();
				assert(task);
				if (task) {
					task->AddTask([a_target, a_callback, args, this]() mutable {
						SendEvent_Tuple(a_target, a_callback, std::move(args), Impl::index_sequence_for_tuple<decltype(args)>{});
					});
				}
			}

		private:
			template <class Tuple, std::size_t... I>
			inline void SendEvent_Tuple(RE::TESObjectREFR* a_target, FilterMatchFunc a_callback, Tuple&& a_tuple, std::index_sequence<I...>)
			{
				SendEvent(a_target, a_callback, std::get<I>(std::forward<Tuple>(a_tuple)).Unpack()...);
			}
		};

		template <>
		class MapUnique<void> : public MapUniqueBase
		{
		private:
			using super = MapUniqueBase;

		public:
			MapUnique() = delete;
			MapUnique(const MapUnique&) = default;
			MapUnique(MapUnique&&) = default;

			inline MapUnique(const std::string_view& a_eventName) :
				super(a_eventName)
			{}

			~MapUnique() = default;

			MapUnique& operator=(const MapUnique&) = default;
			MapUnique& operator=(MapUnique&&) = default;

			inline void SendEvent(const RE::TESObjectREFR* a_target, FilterMatchFunc a_callback)
			{
				RE::BSFixedString eventName(this->_eventName);

				if (auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton()) {
					for (auto& [key, handles] : this->_regs) {
						if (auto& [filters, match] = key; a_callback(filters, match)) {
							const auto targetFormID = a_target->GetFormID();
							for (auto& [formID, vmHandle] : handles) {
								if (formID == targetFormID) {
									auto args = RE::MakeFunctionArguments();
									vm->SendEvent(vmHandle, eventName, args);
								}
							}
						}
					}
				}
			}

			inline void QueueEvent(RE::TESObjectREFR* a_target, FilterMatchFunc a_callback)
			{
				auto task = GetTaskInterface();
				assert(task);
				task->AddTask([a_target, a_callback, this]() {
					SendEvent(a_target, std::move(a_callback));
				});
			}
		};
	};

	template <class... Filter>
	RegistrationFilter<Filter...>::MapUniqueBase::MapUniqueBase(const std::string_view& a_eventName) :
		_regs(),
		_eventName(a_eventName),
		_lock()
	{}

	template <class... Filter>
	RegistrationFilter<Filter...>::MapUniqueBase::MapUniqueBase(const MapUniqueBase& a_rhs) :
		_regs(),
		_eventName(a_rhs._eventName),
		_lock()
	{
		a_rhs._lock.lock();
		_regs = a_rhs._regs;
		a_rhs._lock.unlock();

		auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
		auto policy = vm ? vm->GetObjectHandlePolicy() : nullptr;
		if (policy) {
			for (auto& [key, handles] : _regs) {
				for (auto& handle : handles) {
					policy->PersistHandle(handle.second);
				}
			}
		}
	}

	template <class... Filter>
	RegistrationFilter<Filter...>::MapUniqueBase::MapUniqueBase(MapUniqueBase&& a_rhs) noexcept :
		_regs(),
		_eventName(a_rhs._eventName),
		_lock()
	{
		Locker locker(a_rhs._lock);
		_regs = std::move(a_rhs._regs);
		a_rhs._regs.clear();
	}

	template <class... Filter>
	RegistrationFilter<Filter...>::MapUniqueBase::~MapUniqueBase()
	{
		auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
		auto policy = vm ? vm->GetObjectHandlePolicy() : nullptr;
		if (policy) {
			for (auto& [key, handles] : _regs) {
				for (auto& handle : handles) {
					policy->ReleaseHandle(handle.second);
				}
			}
		}
	}

	template <class... Filter>
	typename RegistrationFilter<Filter...>::template MapUniqueBase& RegistrationFilter<Filter...>::MapUniqueBase::operator=(const MapUniqueBase& a_rhs)
	{
		if (this == &a_rhs) {
			return *this;
		}

		Locker lhsLocker(_lock);
		Clear();

		{
			Locker rhsLocker(a_rhs._lock);
			_regs = a_rhs._regs;
			_eventName = a_rhs._eventName;
		}

		auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
		auto policy = vm ? vm->GetObjectHandlePolicy() : nullptr;
		if (policy) {
			for (auto& [key, handles] : _regs) {
				for (auto& handle : handles) {
					policy->PersistHandle(handle.second);
				}
			}
		}

		return *this;
	}

	template <class... Filter>
	typename RegistrationFilter<Filter...>::template MapUniqueBase& RegistrationFilter<Filter...>::MapUniqueBase::operator=(MapUniqueBase&& a_rhs) noexcept
	{
		if (this == &a_rhs) {
			return *this;
		}

		Locker lhsLocker(_lock);
		Locker rhsLocker(a_rhs._lock);

		Clear();

		_eventName = a_rhs._eventName;

		_regs = std::move(a_rhs._regs);
		a_rhs._regs.clear();

		return *this;
	}

	template <class... Filter>
	bool RegistrationFilter<Filter...>::MapUniqueBase::Register(RE::ActiveEffect* a_activeEffect, Key a_key)
	{
		assert(a_activeEffect);

		const auto target = a_activeEffect->GetTargetActor();
		const auto formID = target ? target->GetFormID() : 0;

		if (formID != 0) {
			return Register(a_activeEffect, std::move(formID), std::move(a_key), RE::ActiveEffect::VMTYPEID);
		}

		return false;
	}

	template <class... Filter>
	bool RegistrationFilter<Filter...>::MapUniqueBase::Register(RE::BGSRefAlias* a_alias, Key a_key)
	{
		assert(a_alias);

		const auto target = a_alias->GetActorReference();
		const auto formID = target ? target->GetFormID() : 0;

		if (formID != 0) {
			return Register(a_alias, formID, std::move(a_key), RE::BGSRefAlias::VMTYPEID);
		}

		return false;
	}

	template <class... Filter>
	bool RegistrationFilter<Filter...>::MapUniqueBase::Unregister(RE::ActiveEffect* a_activeEffect, Key a_key)
	{
		assert(a_activeEffect);

		const auto target = a_activeEffect->GetTargetActor();
		const auto formID = target ? target->GetFormID() : 0;

		if (formID != 0) {
			return Unregister(a_activeEffect, formID, std::move(a_key), RE::ActiveEffect::VMTYPEID);
		}

		return false;
	}

	template <class... Filter>
	bool RegistrationFilter<Filter...>::MapUniqueBase::Unregister(RE::BGSRefAlias* a_alias, Key a_key)
	{
		assert(a_alias);

		const auto target = a_alias->GetActorReference();
		const auto formID = target ? target->GetFormID() : 0;

		if (formID != 0) {
			return Unregister(a_alias, formID, std::move(a_key), RE::BGSRefAlias::VMTYPEID);
		}

		return false;
	}

	template <class... Filter>
	void RegistrationFilter<Filter...>::MapUniqueBase::UnregisterAll(RE::ActiveEffect* a_activeEffect)
	{
		assert(a_activeEffect);

		const auto target = a_activeEffect->GetTargetActor();
		const auto formID = target ? target->GetFormID() : 0;

		if (formID != 0) {
			UnregisterAll(a_activeEffect, formID, RE::ActiveEffect::VMTYPEID);
		}
	}

	template <class... Filter>
	void RegistrationFilter<Filter...>::MapUniqueBase::UnregisterAll(RE::BGSRefAlias* a_alias)
	{
		assert(a_alias);

		const auto target = a_alias->GetActorReference();
		const auto formID = target ? target->GetFormID() : 0;

		if (formID != 0) {
			UnregisterAll(a_alias, formID, RE::BGSRefAlias::VMTYPEID);
		}
	}

	template <class... Filter>
	void RegistrationFilter<Filter...>::MapUniqueBase::UnregisterAll(RE::VMHandle a_handle)
	{
		auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
		auto policy = vm ? vm->GetObjectHandlePolicy() : nullptr;
		if (!policy) {
			log::error("Failed to get handle policy!");
			return;
		}

		Locker locker(_lock);
		for (auto i = _regs.begin(); i != _regs.end(); ++i) {
			auto result = std::erase_if(i->second, [&](const auto& handlePair) { return handlePair.second == a_handle; });
			if (result != 0) {
				policy->ReleaseHandle(a_handle);
			}
		}
	}

	template <class... Filter>
	void RegistrationFilter<Filter...>::MapUniqueBase::Clear()
	{
		auto   vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
		auto   policy = vm ? vm->GetObjectHandlePolicy() : nullptr;
		Locker locker(_lock);
		if (policy) {
			for (auto& [key, handles] : _regs) {
				for (auto& handle : handles) {
					policy->ReleaseHandle(handle.second);
				}
			}
		}
		_regs.clear();
	}

	template <class... Filter>
	bool RegistrationFilter<Filter...>::MapUniqueBase::Save(SerializationInterface* a_intfc, std::uint32_t a_type, std::uint32_t a_version)
	{
		assert(a_intfc);
		if (!a_intfc->OpenRecord(a_type, a_version)) {
			log::error("Failed to open record!");
			return false;
		}

		return Save(a_intfc);
	}

	template <class... Filter>
	bool RegistrationFilter<Filter...>::MapUniqueBase::Save(SerializationInterface* a_intfc)
	{
		assert(a_intfc);
		Locker locker(_lock);

		// Reg count
		const std::size_t numRegs = _regs.size();
		if (!a_intfc->WriteRecordData(numRegs)) {
			log::error("Failed to save reg count ({})!", numRegs);
			return false;
		}
		for (auto& reg : _regs) {
			// Key
			auto& [filters, match] = reg.first;
			for_each_filter([a_intfc](auto&& a_filter) { a_intfc->WriteRecordData(a_filter); }, filters);
			if (!a_intfc->WriteRecordData(match)) {
				log::error("Failed to save reg key as bool ({})!", match);
				return false;
			}
			// Handle count
			std::size_t numUniqueHandle = reg.second.size();
			if (!a_intfc->WriteRecordData(numUniqueHandle)) {
				log::error("Failed to save handle count ({})!", numUniqueHandle);
				return false;
			}
			// UniqueHandle
			for (auto& [formID, vmHandle] : reg.second) {
				if (!a_intfc->WriteRecordData(formID)) {
					log::error("Failed to save handle formID ({:X})", formID);
					return false;
				}
				if (!a_intfc->WriteRecordData(vmHandle)) {
					log::error("Failed to save handle ({})", vmHandle);
					return false;
				}
			}
		}

		return true;
	}

	template <class... Filter>
	bool RegistrationFilter<Filter...>::MapUniqueBase::Load(SerializationInterface* a_intfc)
	{
		assert(a_intfc);
		std::size_t numRegs;
		a_intfc->ReadRecordData(numRegs);

		Locker locker(_lock);
		_regs.clear();

		// Key
		Key  curKey;
		bool match;
		// Handle count
		std::size_t numUniqueHandle;
		// UniqueHandle
		RE::FormID   formID;
		RE::VMHandle vmHandle;

		for (std::size_t i = 0; i < numRegs; ++i) {
			FilterTuple filters{};
			for_each_filter([&](auto&& a_filter) { LoadFilter(a_intfc, a_filter); }, filters);
			a_intfc->ReadRecordData(match);
			curKey = std::pair{ filters, match };

			a_intfc->ReadRecordData(numUniqueHandle);
			for (std::size_t j = 0; j < numUniqueHandle; ++j) {
				a_intfc->ReadRecordData(formID);
				if (!a_intfc->ResolveFormID(formID, formID)) {
					log::warn("Failed to resolve target formID ({:X})", formID);
					continue;
				}
				a_intfc->ReadRecordData(vmHandle);
				if (a_intfc->ResolveHandle(vmHandle, vmHandle)) {
					_regs[curKey].insert({ formID, vmHandle });
				}
			}
		}

		return true;
	}

	template <class... Filter>
	void RegistrationFilter<Filter...>::MapUniqueBase::Revert(SerializationInterface*)
	{
		Clear();
	}

	template <class... Filter>
	bool RegistrationFilter<Filter...>::MapUniqueBase::Register(const void* a_object, RE::FormID a_formID, Key a_key, RE::VMTypeID a_typeID)
	{
		assert(a_object);
		auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
		auto policy = vm ? vm->GetObjectHandlePolicy() : nullptr;
		if (!policy) {
			log::error("Failed to get handle policy!");
			return false;
		}

		const auto invalidHandle = policy->EmptyHandle();
		auto       handle = policy->GetHandleForObject(a_typeID, a_object);
		if (handle == invalidHandle) {
			log::error("Failed to create handle!");
			return false;
		}

		_lock.lock();
		auto result = _regs[a_key].insert({ a_formID, handle });
		_lock.unlock();

		if (result.second) {
			policy->PersistHandle(handle);
		}

		return result.second;
	}

	template <class... Filter>
	bool RegistrationFilter<Filter...>::MapUniqueBase::Unregister(const void* a_object, RE::FormID a_formID, Key a_key, RE::VMTypeID a_typeID)
	{
		assert(a_object);
		auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
		auto policy = vm ? vm->GetObjectHandlePolicy() : nullptr;
		if (!policy) {
			log::error("Failed to get handle policy!");
			return false;
		}

		const auto invalidHandle = policy->EmptyHandle();
		const auto handle = policy->GetHandleForObject(a_typeID, a_object);
		if (handle == invalidHandle) {
			log::error("Failed to create handle!");
			return false;
		}

		Locker locker(_lock);
		auto   handlePair = std::pair{ a_formID, handle };
		auto   it = _regs[a_key].find(handlePair);
		if (it == _regs[a_key].end()) {
			return false;
		} else {
			policy->ReleaseHandle((*it).second);
			_regs[a_key].erase(it);
			return true;
		}
	}

	template <class... Filter>
	void RegistrationFilter<Filter...>::MapUniqueBase::UnregisterAll(const void* a_object, RE::FormID a_formID, RE::VMTypeID a_typeID)
	{
		assert(a_object);
		auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
		auto policy = vm ? vm->GetObjectHandlePolicy() : nullptr;
		if (!policy) {
			log::error("Failed to get handle policy!");
			return;
		}

		const auto invalidHandle = policy->EmptyHandle();
		const auto handle = policy->GetHandleForObject(a_typeID, a_object);
		if (handle == invalidHandle) {
			log::error("Failed to create handle!");
			return;
		}

		Locker locker(_lock);
		auto   handlePair = std::pair{ a_formID, handle };
		for (auto i = _regs.begin(); i != _regs.end(); ++i) {
			auto result = i->second.erase(handlePair);
			if (result != 0) {
				policy->ReleaseHandle(handle);
			}
		}
	}
}
