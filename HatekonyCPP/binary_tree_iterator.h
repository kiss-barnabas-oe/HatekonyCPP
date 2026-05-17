#pragma once

#include "node.h"
#include "stack.h"

template<typename K, typename T>
class BinaryTreeIterator
{
public:
	using iterator_category = std::forward_iterator_tag;
	using value_type = T;
	using difference_type = std::ptrdiff_t;
	using pointer = value_type*;
	using reference = value_type&;

	BinaryTreeIterator(Node<K, T>* const current);
	BinaryTreeIterator(const BinaryTreeIterator& other);
	BinaryTreeIterator& operator=(const BinaryTreeIterator& other);
	~BinaryTreeIterator() = default;

	bool operator==(const BinaryTreeIterator& other) const;
	bool operator!=(const BinaryTreeIterator& other) const;
	BinaryTreeIterator& operator++();
	BinaryTreeIterator operator++(int);
	T& operator*();
	const T& operator*() const;

private:
	Node<K, T>* current;
	Stack<Node<K, T>*> stack;
};

template<typename K, typename T>
BinaryTreeIterator<K, T>::BinaryTreeIterator(Node<K, T>* const root)
	: current(nullptr)	
{
	Node<K, T>* node = root;

	while (node)
	{			
		stack.push(node);
		node = node->left;
	}

	if (!stack.empty())
	{
		current = stack.peek();
		stack.pop();
	}
	else
	{
		current = nullptr;
	}
}

template<typename K, typename T>
BinaryTreeIterator<K, T>::BinaryTreeIterator(const BinaryTreeIterator& other)
	: current(other.current)
	, stack(other.stack)
{
}

template<typename K, typename T>
BinaryTreeIterator<K, T>& BinaryTreeIterator<K, T>::operator=(const BinaryTreeIterator& other)
{
	if (this == &other)
		return *this;
	
	current = other.current;
	stack = other.stack;
	
	return *this;
}

template<typename K, typename T>
bool BinaryTreeIterator<K, T>::operator==(const BinaryTreeIterator& other) const
{
	return current == other.current;
}

template<typename K, typename T>
bool BinaryTreeIterator<K, T>::operator!=(const BinaryTreeIterator& other) const
{
	return !(*this == other);
}

template<typename K, typename T>
BinaryTreeIterator<K, T>& BinaryTreeIterator<K, T>::operator++()
{
	if (!current)
		return *this;

	Node<K, T>* node = current->right;

	while (node)
	{
		stack.push(node);		
		node = node->left;
	}

	if (!stack.empty())
	{
		current = stack.peek();
		stack.pop();
	}
	else
	{		
		current = nullptr;
	}

	return *this;
}

template<typename K, typename T>
BinaryTreeIterator<K, T> BinaryTreeIterator<K, T>::operator++(int)
{
	BinaryTreeIterator temp = *this;
	++(*this);
	return temp;
}

template<typename K, typename T>
T& BinaryTreeIterator<K, T>::operator*()
{
	return current->value;
}

template<typename K, typename T>
const T& BinaryTreeIterator<K, T>::operator*() const
{
	return current->value;
}