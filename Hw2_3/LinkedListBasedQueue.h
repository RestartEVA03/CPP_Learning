#pragma once

template <typename ValueType>
class LinkedListBasedQueue {
private:
	struct Node {
		ValueType value;
		Node* next = nullptr;
	};
	Node* fFront = nullptr;
	Node* fBack = nullptr;
	int fSize = 0;
public:
	LinkedListBasedQueue() = default;
	LinkedListBasedQueue(const LinkedListBasedQueue& anotherQueue) = delete;
	virtual ~LinkedListBasedQueue();
	LinkedListBasedQueue& operator=(const LinkedListBasedQueue& anotherQueue) = delete;
	bool empty() const;
	int size() const;
	const ValueType& front() const;
	ValueType& front();
	const ValueType& back() const;
	ValueType& back();
	void push(const ValueType& newItem);
	void pop();
};


template <typename ValueType>
LinkedListBasedQueue<ValueType>::~LinkedListBasedQueue() {
	Node* curNode = fFront;
	while (curNode != nullptr) {
		Node* nextNode = curNode->next;
		delete curNode;
		curNode = nextNode;
	}
}

template <typename ValueType>
bool LinkedListBasedQueue<ValueType>::empty() const {
	return fSize == 0;
}

template <typename ValueType>
int LinkedListBasedQueue<ValueType>::size() const {
	return fSize;
}

template <typename ValueType>
const ValueType& LinkedListBasedQueue<ValueType>::front() const {
	return fFront->value;
}

template <typename ValueType>
ValueType& LinkedListBasedQueue<ValueType>::front() {
	return fFront->value;
}

template <typename ValueType>
const ValueType& LinkedListBasedQueue<ValueType>::back() const {
	return fBack->value;
}

template <typename ValueType>
ValueType& LinkedListBasedQueue<ValueType>::back() {
	return fBack->value;
}

template <typename ValueType>
void LinkedListBasedQueue<ValueType>::push(const ValueType& newItem) {
	Node* newNode = new Node;
	newNode->value = newItem;

	if (fFront == nullptr) {
		fFront = newNode;
		fBack = fFront;
	}
	else {
		fBack->next = newNode;
		fBack = newNode;
	}

	++fSize;
}

template <typename ValueType>
void LinkedListBasedQueue<ValueType>::pop() {
	if (fFront != nullptr) {
		Node* newFront = fFront->next;
		delete fFront;
		fFront = newFront;

		--fSize;
	}
}

