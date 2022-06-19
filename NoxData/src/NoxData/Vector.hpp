#pragma once

#include "NoxData/Core/Core.hpp"

namespace NoxData {

	template<typename T>
	class Vector
	{
	public:
		Vector() noexcept
		{
			Allocate(2);
		}

		~Vector() noexcept
		{
			Clear();
			::operator delete(m_Data, m_Capacity * sizeof(T));
		}

		void PushBack(const T& element) noexcept
		{
			if (m_Size >= m_Capacity)
				Allocate(2 * m_Capacity);

			new(&m_Data[m_Size++]) T(element);
		}

		void PushBack(T&& element) noexcept
		{
			if (m_Size >= m_Capacity)
				Allocate(2 * m_Capacity);

			new(&m_Data[m_Size++]) T(std::move(element));
		}

		template<typename... Args>
		void EmplaceBack(Args&&... args) noexcept
		{
			if (m_Size >= m_Capacity)
				Allocate(2 * m_Capacity);

			new(&m_Data[m_Size++]) T(std::forward<Args>(args)...);
		}

		void PopBack() noexcept
		{
			if (!m_Size)
				return;

			m_Data[--m_Size].~T();
		}

		void Clear() noexcept
		{
			for (size_t i = 0; i < m_Size; i++)
				m_Data[i].~T();

			m_Size = 0;
		}

		const T& At(const size_t index) noexcept
		{
			ND_ASSERT(index < m_Size);
			return m_Data[index];
		}

		size_t Size() const noexcept { return m_Size; }
		size_t Capacity() const noexcept { return m_Capacity; }

		T& operator[](const size_t index) noexcept
		{
			ND_ASSERT(index < m_Size);
			return m_Data[index];
		}

		const T& operator[](const size_t index) const noexcept
		{
			ND_ASSERT(index < m_Size);
			return m_Data[index];
		}

	private:
		void Allocate(const size_t newCap) noexcept
		{
			T* newData = (T*)::operator new(newCap * sizeof(T));

			if (newCap < m_Size)
				m_Size = newCap;

			for (size_t i = 0; i < m_Size; i++)
				new(&newData[i]) T(std::move(m_Data[i]));

			for (size_t i = 0; i < m_Size; i++)
				m_Data[i].~T();

			::operator delete(m_Data, m_Capacity * sizeof(T));
			m_Data = newData;
			m_Capacity = newCap;
		}

	private:
		T* m_Data = nullptr;
		size_t m_Size = 0;
		size_t m_Capacity = 0;
	};

}