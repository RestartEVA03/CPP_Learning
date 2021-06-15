#pragma once


using namespace std;

template <typename ValueType>
class ArrayBasedQueue {
private:
	ValueType* fItems = nullptr;
	size_t fMaxSize;
	size_t fSize = 0;
	int fFirstIndex = -1;
	int fLastIndex = -1;
public:
	ArrayBasedQueue(const size_t size = 10);
	ArrayBasedQueue(const ArrayBasedQueue& anotherQueue);
	ArrayBasedQueue(ArrayBasedQueue&& anotherQueue);
	virtual ~ArrayBasedQueue() { delete[] fItems; };
	ArrayBasedQueue& operator=(const ArrayBasedQueue& anotherQueue);
	ArrayBasedQueue& operator=(ArrayBasedQueue&& anotherQueue);
	bool empty() const;
	size_t size() const;
	const ValueType& front() const;
	ValueType& front();
	const ValueType& back() const;
	ValueType& back();
	void push(const ValueType& newItem);
	void pop();
};


template <typename ValueType>
ArrayBasedQueue<ValueType>::ArrayBasedQueue(const size_t size) {
	fMaxSize = size;
	fItems = new ValueType[fMaxSize];
}

template <typename ValueType>
ArrayBasedQueue<ValueType>::ArrayBasedQueue(const ArrayBasedQueue& anotherQueue) : ArrayBasedQueue(anotherQueue.fMaxSize) {
	fSize = anotherQueue.fSize;
	fFirstIndex = anotherQueue.fFirstIndex;
	fLastIndex = anotherQueue.fLastIndex;

	for (size_t idx = 0; idx < fMaxSize; ++idx)
		fItems[idx] = anotherQueue.fItems[idx];
}


template <typename ValueType>
ArrayBasedQueue<ValueType>::ArrayBasedQueue(ArrayBasedQueue&& anotherQueue) {  // && конструктор перемещени€, ќн забирает данные у другого объекта » становитс€ их владельцем, поэтому второй объект в деструкторе не будет ничего уничтожать потому что его указатель уже nullptr
	fMaxSize = anotherQueue.fMaxSize;
	fSize = anotherQueue.fSize;
	fFirstIndex = anotherQueue.fFirstIndex;
	fLastIndex = anotherQueue.fLastIndex;
	fItems = anotherQueue.fItems;
	anotherQueue.fItems = nullptr;
}


template <typename ValueType>
ArrayBasedQueue<ValueType>& ArrayBasedQueue<ValueType>::operator=(const ArrayBasedQueue& anotherQueue) {
	fMaxSize = anotherQueue.fMaxSize;
	fSize = anotherQueue.fSize;
	fFirstIndex = anotherQueue.fFirstIndex;
	fLastIndex = anotherQueue.fLastIndex;

	delete[] fItems;
	fItems = new ValueType[fMaxSize];
	for (size_t idx = 0; idx < fMaxSize; ++idx)
		fItems[idx] = anotherQueue.fItems[idx];
}


template <typename ValueType>
ArrayBasedQueue<ValueType>& ArrayBasedQueue<ValueType>::operator=(ArrayBasedQueue&& anotherQueue) {
	fMaxSize = anotherQueue.fMaxSize;			//только дл€ переменных (передаютс€ в параметр конструктора) , которые дальше использоватьс€ не будут
	fSize = anotherQueue.fSize;
	fFirstIndex = anotherQueue.fFirstIndex;
	fLastIndex = anotherQueue.fLastIndex;
	fItems = anotherQueue.fItems;
	anotherQueue.fItems = nullptr;
}


template <typename ValueType>
bool ArrayBasedQueue<ValueType>::empty() const {
	return fSize == 0;
}


template <typename ValueType>
size_t ArrayBasedQueue<ValueType>::size() const {
	return fSize;
}


template <typename ValueType>
const ValueType& ArrayBasedQueue<ValueType>::front() const {
	return fItems[fFirstIndex];
}


template <typename ValueType>
ValueType& ArrayBasedQueue<ValueType>::front() {
	return fItems[fFirstIndex];
}


template <typename ValueType>
const ValueType& ArrayBasedQueue<ValueType>::back() const {
	return fItems[fLastIndex];
}


template <typename ValueType>
ValueType& ArrayBasedQueue<ValueType>::back() {
	return fItems[fLastIndex];
}


template <typename ValueType>
void ArrayBasedQueue<ValueType>::push(const ValueType& newItem) {
	if (fSize == fMaxSize)
		return;

	if (static_cast<size_t>(fLastIndex) < fMaxSize - 1)
		++fLastIndex;
	else
		fLastIndex = 0;

	if (fFirstIndex < 0)
		fFirstIndex = fLastIndex;

	fItems[fLastIndex] = newItem;
	++fSize;
}


template <typename ValueType>
void ArrayBasedQueue<ValueType>::pop() {
	if (fSize > 0) {
		if (static_cast<size_t>(fFirstIndex) < fMaxSize - 1)
			++fFirstIndex;
		else
			fFirstIndex = 0;

		--fSize;

		if (fSize == 0)
			fLastIndex = fFirstIndex = -1;
	}
}
