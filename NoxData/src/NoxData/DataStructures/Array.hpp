#pragma once

#include "NoxData/Core/Core.hpp"

namespace NoxData {

	template<typename Array>
	class ArrayIterator
	{
	public:
		using ValueType = typename Array::ValueType;
		using PointerType = ValueType*;
		using ReferenceType = ValueType&;

	public:
		ArrayIterator(const PointerType ptr) noexcept
			: m_Ptr(ptr)
		{
		}

		~ArrayIterator() noexcept = default;

		ArrayIterator& operator++() noexcept
		{
			m_Ptr++;
			return *this;
		}
		
		ArrayIterator operator++(int) noexcept
		{
			ArrayIterator it = *this;
			++(*this);
			return it;
		}
		
		ArrayIterator& operator--() noexcept
		{
			m_Ptr--;
			return *this;
		}
		
		ArrayIterator operator--(int) noexcept
		{
			ArrayIterator it = *this;
			--(*this);
			return it;
		}
		
		ND_NODISCARD ReferenceType operator[](const int index) noexcept { return *(m_Ptr[index]); }

		ND_NODISCARD PointerType operator->() const noexcept { return m_Ptr; }
		
		ND_NODISCARD ReferenceType operator*() noexcept { return *m_Ptr; }
		
		ND_NODISCARD bool operator==(const ArrayIterator& other) const noexcept { return m_Ptr == other.m_Ptr; }
		ND_NODISCARD bool operator!=(const ArrayIterator& other) const noexcept { return !(*this == other); }
		
	private:
		PointerType m_Ptr;
	};

	template<typename Array>
	class ArrayConstIterator
	{
	public:
		using ValueType = typename Array::ValueType;
		using PointerType = const ValueType*;
		using ReferenceType = const ValueType&;

	public:
		ArrayConstIterator(const PointerType ptr) noexcept
			: m_Ptr(ptr)
		{
		}

		~ArrayConstIterator() noexcept = default;

		ArrayConstIterator& operator++() noexcept
		{
			m_Ptr++;
			return *this;
		}

		ArrayConstIterator operator++(int) noexcept
		{
			ArrayConstIterator it = *this;
			++(*this);
			return it;
		}

		ArrayConstIterator& operator--() noexcept
		{
			m_Ptr--;
			return *this;
		}

		ArrayConstIterator operator--(int) noexcept
		{
			ArrayConstIterator it = *this;
			--(*this);
			return it;
		}

		ND_NODISCARD ReferenceType operator[](const int index) noexcept { return *(m_Ptr[index]); }

		ND_NODISCARD PointerType operator->() const noexcept { return m_Ptr; }

		ND_NODISCARD ReferenceType operator*() noexcept { return *m_Ptr; }

		ND_NODISCARD bool operator==(const ArrayConstIterator& other) const noexcept { return m_Ptr == other.m_Ptr; }
		ND_NODISCARD bool operator!=(const ArrayConstIterator& other) const noexcept { return !(*this == other); }

	private:
		PointerType m_Ptr;
	};

	template<typename T, size_t N>
	class Array
	{
	public:
		using ValueType = T;
		using Iterator = ArrayIterator<Array<T, N>>;
		using ConstIterator = ArrayConstIterator<Array<T, N>>;

	public:
		Array() noexcept = default;
		~Array() noexcept = default;

		constexpr size_t Size() const noexcept { return N; }

		ND_NODISCARD T* const Data() noexcept { return m_Data; }
		ND_NODISCARD const T* const Data() const noexcept { return m_Data; }

		ND_NODISCARD T& operator[](const size_t index) noexcept
		{
			ND_ASSERT(index < N);
			return m_Data[index];
		}

		ND_NODISCARD const T& operator[](const size_t index) const noexcept
		{
			ND_ASSERT(index < N);
			return m_Data[index];
		}

		Iterator begin() noexcept { return Iterator(&m_Data[0]); }
		ConstIterator cbegin() noexcept { return ConstIterator(&m_Data[0]); }

		Iterator end() noexcept { return Iterator(&m_Data[N]); }
		ConstIterator cend() noexcept { return ConstIterator(&m_Data[N]); }

	private:
		T m_Data[N];
	};

}