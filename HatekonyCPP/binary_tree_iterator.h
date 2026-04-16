#pragma once

#include "node.h"

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
	~BinaryTreeIterator();

	void resizeStack();

	bool operator==(const BinaryTreeIterator& other) const;
	bool operator!=(const BinaryTreeIterator& other) const;
	BinaryTreeIterator& operator++();
	BinaryTreeIterator operator++(int);
	reference operator*();
	const reference operator*() const;

private:
	Node<K, T>* current;
	Node<K, T>** stack;
	size_t top;
	size_t capacity;
};

template<typename K, typename T>
void BinaryTreeIterator<K, T>::resizeStack()
{
	if (top == capacity)
	{
		capacity *= 2;
		Node<K, T>** newStack = new Node<K, T>* [capacity];
		for (size_t i = 0; i < top; ++i)
			newStack[i] = stack[i];
		delete[] stack;
		stack = newStack;
	}
}

template<typename K, typename T>
BinaryTreeIterator<K, T>::BinaryTreeIterator(Node<K, T>* const root)
	: current(nullptr)
	, capacity(1)
	, stack(new Node<K, T>* [capacity])
	, top(0)
{
	Node<K, T>* node = root;

	while (node)
	{	
		resizeStack();
		stack[top++] = node;
		node = node->left;
	}

	if (top > 0)
		current = stack[--top];
}

template<typename K, typename T>
BinaryTreeIterator<K, T>::BinaryTreeIterator(const BinaryTreeIterator& other)
{
	capacity = other.capacity;
	top = other.top;
	stack = new Node<K, T>* [capacity];
	for (size_t i = 0; i < top; ++i)
		stack[i] = other.stack[i];
	current = other.current;
}

template<typename K, typename T>
BinaryTreeIterator<K, T>& BinaryTreeIterator<K, T>::operator=(const BinaryTreeIterator& other)
{
	if (this == &other)
		return *this;

	delete[] stack;

	capacity = other.capacity;
	top = other.top;
	stack = new Node<K, T>* [capacity];
	for (size_t i = 0; i < top; ++i)
		stack[i] = other.stack[i];

	current = other.current;
	return *this;
}

template<typename K, typename T>
BinaryTreeIterator<K, T>::~BinaryTreeIterator()
{
	delete[] stack;
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
		resizeStack();
		stack[top++] = node;
		node = node->left;
	}

	if (top > 0)
		current = stack[--top];
	else
		current = nullptr;

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
typename BinaryTreeIterator<K, T>::reference BinaryTreeIterator<K, T>::operator*()
{
	return current->value;
}

template<typename K, typename T>
const typename BinaryTreeIterator<K, T>::reference BinaryTreeIterator<K, T>::operator*() const
{
	return current->value;
}