#pragma once

#include "NoxData/Core/Core.hpp"

namespace NoxData {

	template<typename T, size_t N>
	class Array
	{
	public:
		Array() noexcept = default;
		~Array() noexcept = default;

		constexpr size_t Size() const noexcept { return N; }

		ND_NODISCARD T* const Data() noexcept { return m_Data; }
		ND_NODISCARD const T* const Data() const noexcept { return m_Data; }

		ND_NODISCARD T& operator[](const size_t index) noexcept
		{
#ifdef ND_DEBUG
			if (index >= N)
				ND_DEBUGBREAK();
#endif
			return m_Data[index];
		}

		ND_NODISCARD const T& operator[](const size_t index) const noexcept
		{
#ifdef ND_DEBUG
			if (index >= N)
				ND_DEBUGBREAK(); 
#endif
			return m_Data[index];
		}

	private:
		T m_Data[N];
	};

}