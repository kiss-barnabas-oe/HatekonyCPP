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

	bool operator==(const BinaryTreeIterator& other) const;
	bool operator!=(const BinaryTreeIterator& other) const;
	BinaryTreeIterator& operator++();
	BinaryTreeIterator operator++(int);
	reference operator*();
	const reference operator*() const;

private:
	Node<K, T>* current;
};