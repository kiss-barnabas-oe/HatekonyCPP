#pragma once
#include "node.h"

template<typename K, typename T>
class BinaryTree
{
public:
	BinaryTree();
	BinaryTree(const BinaryTree& other);
	~BinaryTree();
	BinaryTree& operator=(const BinaryTree& other);
	void Insert(const K& key, const T& value);
	T* Find(const K& key);

private:
	Node<K, T>* root;
};

template<typename K, typename T>
BinaryTree<K, T>::BinaryTree()
{
}

template<typename K, typename T>
BinaryTree<K, T>::BinaryTree(const BinaryTree& other)
{
}

template<typename K, typename T>
BinaryTree<K, T>::~BinaryTree()
{
}

template<typename K, typename T>
BinaryTree<K, T>& BinaryTree<K, T>::operator=(const BinaryTree& other)
{
	return *this;
}

template<typename K, typename T>
void BinaryTree<K, T>::Insert(const K& key, const T& value)
{
	auto node = root;
	if (!node)
	{
		node = new Node<K, T>(key, value);
	}
	else if (key < node->key)
	{
		insert(node->left, key, value);
	}
	else if (key > node->key)
	{
		insert(node->right, key, value);
	}
	else
	{
		node->value = value;
	}
}

template<typename K, typename T>
T* BinaryTree<K, T>::Find(const K& key)
{
	auto node = root;
	if (!node)
	{
		return nullptr;
	}
	else if (key < node->key)
	{
		return find(node->left, key);
	}
	else if (key > node->key)
	{
		return find(node->right, key);
	}
	else
	{
		return &node->value;
	}
}

