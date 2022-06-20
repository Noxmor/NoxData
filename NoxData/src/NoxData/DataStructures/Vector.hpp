#pragma once

#include <functional>

#include "NoxData/Core/Core.hpp"

namespace NoxData {

	template<typename Vector>
	class VectorIterator
	{
	public:
		using ValueType = typename Vector::ValueType;
		using PointerType = ValueType*;
		using ReferenceType = ValueType&;

	public:
		VectorIterator(const PointerType ptr) noexcept
			: m_Ptr(ptr)
		{
		}

		~VectorIterator() noexcept = default;

		VectorIterator& operator++() noexcept
		{
			m_Ptr++;
			return *this;
		}

		VectorIterator operator++(int) noexcept
		{
			VectorIterator it = *this;
			++(*this);
			return it;
		}

		VectorIterator& operator--() noexcept
		{
			m_Ptr--;
			return *this;
		}

		VectorIterator operator--(int) noexcept
		{
			VectorIterator it = *this;
			--(*this);
			return it;
		}

		ND_NODISCARD ReferenceType operator[](const int index) noexcept { return *(m_Ptr[index]); }

		ND_NODISCARD PointerType operator->() const noexcept { return m_Ptr; }

		ND_NODISCARD ReferenceType operator*() noexcept { return *m_Ptr; }

		ND_NODISCARD bool operator==(const VectorIterator& other) const noexcept { return m_Ptr == other.m_Ptr; }
		ND_NODISCARD bool operator!=(const VectorIterator& other) const noexcept { return !(*this == other); }

	private:
		PointerType m_Ptr;
	};

	template<typename Vector>
	class VectorConstIterator
	{
	public:
		using ValueType = typename Vector::ValueType;
		using PointerType = const ValueType*;
		using ReferenceType = const ValueType&;

	public:
		VectorConstIterator(const PointerType ptr) noexcept
			: m_Ptr(ptr)
		{
		}

		~VectorConstIterator() noexcept = default;

		VectorConstIterator& operator++() noexcept
		{
			m_Ptr++;
			return *this;
		}

		VectorConstIterator operator++(int) noexcept
		{
			VectorConstIterator it = *this;
			++(*this);
			return it;
		}

		VectorConstIterator& operator--() noexcept
		{
			m_Ptr--;
			return *this;
		}

		VectorConstIterator operator--(int) noexcept
		{
			VectorConstIterator it = *this;
			--(*this);
			return it;
		}

		ND_NODISCARD ReferenceType operator[](const int index) noexcept { return *(m_Ptr[index]); }

		ND_NODISCARD PointerType operator->() const noexcept { return m_Ptr; }

		ND_NODISCARD ReferenceType operator*() noexcept { return *m_Ptr; }

		ND_NODISCARD bool operator==(const VectorConstIterator& other) const noexcept { return m_Ptr == other.m_Ptr; }
		ND_NODISCARD bool operator!=(const VectorConstIterator& other) const noexcept { return !(*this == other); }

	private:
		PointerType m_Ptr;
	};

	template<typename T>
	class Vector
	{
	public:
		using ValueType = T;
		using Iterator = VectorIterator<Vector<T>>;
		using ConstIterator = VectorConstIterator<Vector<T>>;

	public:
		Vector() noexcept
		{
			m_GrowFunction = [](const size_t cap)
			{
				return cap + cap / 2;
			};

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
				Allocate(m_GrowFunction(m_Capacity));

			new(&m_Data[m_Size++]) T(element);
		}

		void PushBack(T&& element) noexcept
		{
			if (m_Size >= m_Capacity)
				Allocate(m_GrowFunction(m_Capacity));

			new(&m_Data[m_Size++]) T(std::move(element));
		}

		template<typename... Args>
		void EmplaceBack(Args&&... args) noexcept
		{
			if (m_Size >= m_Capacity)
				Allocate(m_GrowFunction(m_Capacity));

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

		void SetGrowFunction(const std::function<size_t(size_t)>& func) noexcept { m_GrowFunction = func; }

		Iterator begin() const noexcept { return Iterator(m_Data); }
		ConstIterator cbegin() const noexcept { return ConstIterator(m_Data); }

		Iterator end() const noexcept { return Iterator(m_Data + m_Size); }
		ConstIterator cend() const noexcept { return ConstIterator(m_Data + m_Size); }

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
		std::function<size_t(size_t)> m_GrowFunction;
	};

}