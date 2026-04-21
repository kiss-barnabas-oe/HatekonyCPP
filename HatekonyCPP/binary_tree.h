#pragma once
#include "node.h"
#include "binary_tree_iterator.h"

template<typename K, typename T>
class BinaryTree
{
public:
	BinaryTree() = default;
	BinaryTree(const BinaryTree& other);
	BinaryTree(BinaryTree&& other) noexcept = default;
	~BinaryTree();

	BinaryTree& operator=(const BinaryTree& other);
	BinaryTree& operator=(BinaryTree& other) noexcept;
	T* operator[](const K& key);
	const T* operator[](const K& key) const;
	
	bool empty() const;
	void clear();
	bool insert(const K& key, const T& value);
	bool remove(const K& key);
	bool contains(const K& key) const;


	using iterator = BinaryTreeIterator<K, T>;

	iterator begin();
	iterator end();

private:
	Node<K, T>* root{ nullptr };
	Node<K, T>* InsertToSubTree(Node<K, T>* node, K key, T value);
	T* findInSubTree(Node<K, T>* node, const K& key);
	const T* findInSubTree(const Node<K, T>* node, const K& key) const;
	bool removeFromSubTree(Node<K, T>* node, const K& key);
	void twoChildrenRemove(Node<K, T>* node, Node<K, T>* r);
};

template<typename K, typename T>
BinaryTree<K, T>::BinaryTree(const BinaryTree& other)
	: root{ other.root ? new Node<K, T>(*other.root) : nullptr }
{
}

template<typename K, typename T>
BinaryTree<K, T>::~BinaryTree()
{
	if(root)
		delete root;
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
	delete other.root;

	return *this;
}

template<typename K, typename T>
bool BinaryTree<K, T>::insert(const K& key, const T& value)
{
	if(contains(key))
		throw std::invalid_argument("Key already exists in the tree.");
	root = InsertToSubTree(root, key, value);
	return contains(key);
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
T* BinaryTree<K, T>::findInSubTree(Node<K, T>* node, const K& key)
{
    if (!node)
        return nullptr;
    if (node->key == key)
        return &(node->value);
    else if (node->key > key)
        return findInSubTree(node->left, key);
    else
        return findInSubTree(node->right, key);
}

template<typename K, typename T>
const T* BinaryTree<K, T>::findInSubTree(const Node<K, T>* node, const K& key) const
{
    return const_cast<T*>(const_cast<BinaryTree*>(this)->findInSubTree(const_cast<Node<K, T>*>(node), key));
}

template<typename K, typename T>
T* BinaryTree<K, T>::operator[](const K& key)
{
	return findInSubTree(root, key);	
}

template<typename K, typename T>
const T* BinaryTree<K, T>::operator[](const K& key) const
{
	return findInSubTree(root, key);
}

template<typename K, typename T>
bool BinaryTree<K, T>::contains(const K& key) const
{
	return findInSubTree(root, key) != nullptr;
}

template<typename K, typename T>
bool BinaryTree<K, T>::empty() const {
	return root == nullptr;
}

template<typename K, typename T>
void BinaryTree<K, T>::clear() {
	if (root) {
		delete root;
		root = nullptr;
	}
}

template<typename K, typename T>
bool BinaryTree<K, T>::remove(const K& key)
{
	try
	{
		root = removeFromSubTree(root, key);
	}
	catch (const std::invalid_argument&)
	{
		return false;
	}
	return true;
}

template<typename K, typename T>
bool BinaryTree<K, T>::removeFromSubTree(Node<K, T>* node, const K& key)
{
	if(node == nullptr)
		throw std::invalid_argument("Key not found in the tree.");
	if (node->key > key)
		node->left = removeFromSubTree(node->left, key);
	else if (node->key < key)
		node->right = removeFromSubTree(node->right, key);
	else
	{
		if (node->left == nullptr)
		{
			Node<K, T>* temp = node->right;
			delete node;
			return temp;
		}
		else if (node->right == nullptr)
		{
			Node<K, T>* temp = node;
			node = node->right;
			delete temp;
		}	
		else
		{
			node->left = twoChildrenRemove(node, node->left);
		}
	}
	return node;
}

template<typename K, typename T>
void BinaryTree<K, T>::twoChildrenRemove(Node<K, T>* node, Node<K, T>* r)
{
	if (r->right != nullptr)
	{
		r->right = twoChildrenRemove(node, r->right);
		return r;
	}
	else
	{
		Node<K, T>* temp = r;
		node->key = r->key;
		node->value = r->value;
		r = r->left;
		delete temp;
		return r;
	}
}

template<typename K, typename T>
typename BinaryTree<K, T>::iterator BinaryTree<K, T>::begin()
{
	return iterator{ root };
}

template<typename K, typename T>
typename BinaryTree<K, T>::iterator BinaryTree<K, T>::end()
{
	return iterator{ nullptr };
}