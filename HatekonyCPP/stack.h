#pragma once
#include <stdexcept>

template<typename T>
class Stack
{
public:
	Stack();
	~Stack();

	void push(const T& value);
	void pop();
	T& peek();
	const T& peek() const;

	bool empty() const;
	size_t size() const;

private:
	T* data;
	size_t capacity;
	size_t top;
	void resize() {
		capacity *= 2;
		T* newData = new T[capacity];
		for (size_t i = 0; i < top; ++i)
			newData[i] = data[i];
		delete[] data;
		data = newData;
	}
};

template<typename T>
Stack<T>::Stack()
	: data(new T[1])
	, capacity(1)
	, top(0)
{
}

template<typename T>
Stack<T>::~Stack()	{ delete[] data; }

template<typename T>
void Stack<T>::push(const T& value)
{
	if (top == capacity)
		resize();
	data[top++] = value;
}

template<typename T>
void Stack<T>::pop()
{
	if (top == 0)
		throw std::out_of_range("Stack is empty.");
	--top;
}

template<typename T>
T& Stack<T>::peek()
{
	if (top == 0)
		throw std::out_of_range("Stack is empty.");
	return data[top - 1];
}

template<typename T>
const T& Stack<T>::peek() const
{
	if (top == 0)
		throw std::out_of_range("Stack is empty.");
	return data[top - 1];
}

template<typename T>
bool Stack<T>::empty() const
{
	return top == 0; 
}

template<typename T>
size_t Stack<T>::size() const 
{
	return top; 
}