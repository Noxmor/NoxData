#pragma once

#include "NoxData/Core/Core.hpp"

namespace NoxData {

	template<typename T>
	class Stack
	{
	public:
		Stack() noexcept = default;
		~Stack() noexcept
		{
			while (m_Top)
			{
				StackNode* const next = m_Top->Next;
				delete m_Top;
				m_Top = next;
			}
		}

		void Push(const T& value) noexcept
		{
			StackNode* const node = new StackNode();
			node->Data = value;
			node->Next = m_Top;
			m_Top = node;
		}

		void Push(T&& value) noexcept
		{
			StackNode* const node = new StackNode();
			node->Data = std::move(value);
			node->Next = m_Top;
			m_Top = node;
		}

		void Pop() noexcept
		{
			ND_ASSERT(m_Top);
			StackNode* const newTop = m_Top->Next;
			delete m_Top;
			m_Top = newTop;
		}

		ND_NODISCARD T& Top() noexcept
		{
			ND_ASSERT(m_Top);
			return m_Top->Data;
		}

		ND_NODISCARD const T& Top() const noexcept
		{
			ND_ASSERT(m_Top);
			return m_Top->Data;
		}

		size_t Size() const noexcept
		{
			size_t size = 0;
			const StackNode* node = m_Top;
			while (node)
			{
				size++;
				node = node->Next;
			}

			return size;
		}

	private:
		struct StackNode
		{
			T Data;
			StackNode* Next = nullptr;

			StackNode() noexcept = default;
			~StackNode() noexcept = default;
		};

		StackNode* m_Top = nullptr;
	};

}