#pragma once

template<typename K, typename T>
struct Node
{
	Node(const K& key, const T& value, Node* const left = nullptr, Node* const right = nullptr);
	Node(const Node& other);
	Node(Node&& other) noexcept;
	~Node();

	Node& operator=(const Node& other);
	Node& operator=(Node&& other) noexcept;

	K key;
	T value;
	Node* left;
	Node* right;
};

template<typename K, typename T>
Node<K, T>::Node(const K& key, const T& value, Node* const left, Node* const right)
	: key(key)
	, value(value)
	, left(left)
	, right(right)
{
}

template<typename K, typename T>
Node<K, T>::Node(const Node& other)
	: key(other.key)
	, value(other.value)
	, left(other.left ? new Node(*other.left) : nullptr)
	, right(other.right ? new Node(*other.right) : nullptr)
{
}

template<typename K, typename T>
Node<K, T>::Node(Node&& other) noexcept
	: key(std::move(other.key))
	, value(std::move(other.value))
	, left(other.left)
	, right(other.right)
{
	other.left = nullptr;
	other.right = nullptr;
}

template<typename K, typename T>
Node<K, T>::~Node()
{
	delete left;
	delete right;
}

template<typename K, typename T>
Node<K, T>& Node<K, T>::operator=(const Node& other)
{
	if (this == &other)
		return *this;
	
	key = other.key;
	value = other.value;
	if(left)
		delete left;	
	left = other.left ? new Node(*other.left) : nullptr;
	if(right)
		delete right;
	right = other.right ? new Node(*other.right) : nullptr;
	
	return *this;
}

template<typename K, typename T>
Node<K, T>& Node<K, T>::operator=(Node&& other) noexcept
{
	if (this == &other)
		return *this;

	delete left;
	delete right;

	key = std::move(other.key);
	value = std::move(other.value);
	left = other.left;
	right = other.right;

	other.left = nullptr;
	other.right = nullptr;

	return *this;
}