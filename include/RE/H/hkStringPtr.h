#pragma once

namespace RE
{
	class hkStringPtr
	{
	public:
		hkStringPtr(const char* a_data);

		// member types
		using size_type = std::int32_t;

		// members access
		[[nodiscard]] const char* data() const noexcept;
		[[nodiscard]] const char* c_str() const noexcept;

		// capacity
		[[nodiscard]] bool      empty() const noexcept;
		[[nodiscard]] size_type size() const;
		[[nodiscard]] size_type length() const;

	protected:
		enum
		{
			kManaged = 1 << 0
		};

		const char* _data;  // 0
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(hkStringPtr) == 0x8);
}
