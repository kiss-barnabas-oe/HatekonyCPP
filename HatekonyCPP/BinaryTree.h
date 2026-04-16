#pragma once
#include "node.h"

template<typename K, typename T>
class BinaryTree
{
public:
	BinaryTree() = default;
	BinaryTree(const BinaryTree& other);
	BinaryTree(BinaryTree&& other) noexcept;
	~BinaryTree();

	BinaryTree& operator=(const BinaryTree& other);
	BinaryTree& operator=(BinaryTree& other) noexcept;
	T operator[](const K& key);

	T* Find(const K& key);
	void Insert(const K& key, const T& value);
	bool Contains(const K& key);


private:
	Node<K, T>* root{ nullptr };
	Node<K, T>* InsertToSubTree(Node<K, T>* node, K key, T value);
	T* FindInSubTree(Node<K, T>* node, const K& key);
	bool ContainsInSubTree(Node<K, T>* node, const K& key);
};

template<typename K, typename T>
BinaryTree<K, T>::BinaryTree(const BinaryTree& other)
	: root{ other.root ? new Node<K, T>(*other.root) : nullptr }
{
}

template<typename K, typename T>
BinaryTree<K, T>::BinaryTree(BinaryTree&& other) noexcept
	: root(other.root)
{
}

template<typename K, typename T>
BinaryTree<K, T>::~BinaryTree()
{
	if (root->left)
		delete root->left;	
	if (root->right)
		delete root->right;
}

template<typename K, typename T>
BinaryTree<K, T>& BinaryTree<K, T>::operator=(const BinaryTree& other)
{
	if (this == &other) {
		return *this;
	}

	if (root) {
		delete root;
	}

	root = other.root ? new Node<K, T>{ *other.root } : nullptr;

	return *this;
}

template<typename K, typename T>
BinaryTree<K, T>& BinaryTree<K, T>::operator=(BinaryTree& other) noexcept
{
	if (this == &other) {
		return *this;
	}

	if (root) {
		delete root;
	}

	root = other.root ? new Node<K, T>{ *other.root } : nullptr;
	other.root = nullptr;

	return *this;
}

template<typename K, typename T>
void BinaryTree<K, T>::Insert(const K& key, const T& value)
{
	if(Contains(key))
		throw std::invalid_argument("Key already exists in the tree.");
	root = InsertToSubTree(root, key, value);
}

template<typename K, typename T>
Node<K, T>* BinaryTree<K, T>::InsertToSubTree(Node<K, T>* node, K key, T value)
{
    if (node)
    {
        if(node->key > key)		
            node->left = InsertToSubTree(node->left, key, value);		
        else if(node->key < key)
            node->right = InsertToSubTree(node->right, key, value);				
        return node;
    }
    else
    {
        return new Node<K, T>{ key, value };
    }
}

template<typename K, typename T>
T* BinaryTree<K, T>::Find(const K& key)
{
	const auto result = FindInSubTree(root, key);
	if(result == nullptr)
		throw std::invalid_argument("Key not found in the tree.");
	return result;
}

template<typename K, typename T>
T* BinaryTree<K, T>::FindInSubTree(Node<K, T>* node, const K& key)
{
    if (!node)
        return nullptr;
    if (node->key == key)
        return &(node->value);
    else if (node->key > key)
        return FindInSubTree(node->left, key);
    else
        return FindInSubTree(node->right, key);
}

template<typename K, typename T>
T BinaryTree<K, T>::operator[](const K& key) {
	return *Find(key);
}

template<typename K, typename T>
bool BinaryTree<K, T>::Contains(const K& key)
{
	return ContainsInSubTree(root, key);
}

template<typename K, typename T>
bool BinaryTree<K, T>::ContainsInSubTree(Node<K, T>* node, const K& key)
{
    if (!node)
        return false;
    if(node->key == key)
        return true;
    else if(node->key > key)
        return ContainsInSubTree(node->left, key);
    else
        return ContainsInSubTree(node->right, key);
}

