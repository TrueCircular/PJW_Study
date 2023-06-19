#pragma once
#include <iostream>

#pragma region GradeList
template<typename T>
class Info
{
public:
	Info() : _prev(nullptr), _next(nullptr), _data(T()), _id(0) {}
	Info(const T& value) : _prev(nullptr), _next(nullptr), _data(value), _id(0) {}
public:
	Info*	_prev;
	Info*	_next;
	T		_data;
	int		_id;
};

template<typename T>
class GradeList
{
private:
	Info<T>* _head;
	Info<T>* _tail;
	int		 _size;
private:
	Info<T>* AddNode(Info<T>* node, const T& data);
	Info<T>* DelNode(Info<T>* node);
	Info<T>* FindNode(Info<T>* node, const T& value);
	Info<T>* FindeNodeForIndex(int idex);
	Info<T>* InsertNode(Info<T>* node, const T& data);
	void DelBack();
public:
	GradeList();
	~GradeList();

	void AddInfo(const T& value);
	void DeleteInfo(const T& value);
	void InsertInfo(const T& value1, const T& value2);
	Info<T>* SearchInfo(const T& value);
	Info<T>* SearchInfoForIndex(int idex);
	bool SortingHigh();
	bool SortingLow();
	void AllDelete();
	int size() { return _size; }
};
#pragma endregion

#pragma region G_Fun
template<typename T>
inline GradeList<T>::~GradeList()
{
	AllDelete();
}

template<typename T>
inline Info<T>* GradeList<T>::AddNode(Info<T>* node, const T& data)
{
	if (node == nullptr)
		return nullptr;

	Info<T>* tNode = new Info<T>(data);
	Info<T>* pNode = node->_prev;

	pNode->_next = tNode;
	tNode->_prev = pNode;

	tNode->_next = node;
	node->_prev = tNode;

	node->_id = _size;
	_size++;

	return tNode;
	return nullptr;
}

template<typename T>
inline Info<T>* GradeList<T>::DelNode(Info<T>* node)
{
	if (node == nullptr)
		return nullptr;

	Info<T>* pNode = node->_prev;
	Info<T>* nNode = node->_next;

	pNode->_next = nNode;
	nNode->_prev = pNode;

	delete node;

	_size--;

	return nNode;
}

template<typename T>
inline Info<T>* GradeList<T>::FindNode(Info<T>* node, const T& value)
{
	if (node == nullptr)
		return nullptr;

	Info<T>* nFind = node;

	while (nFind != NULL)
	{
		if (nFind->_data == value)
			return nFind;
		else
			nFind = nFind->_next;
	}

	return nullptr;
}

template<typename T>
inline Info<T>* GradeList<T>::FindeNodeForIndex(int idex)
{
	Info<T>* nFind = _head;

	while (nFind != NULL)
	{
		if (nFind->_id == idex)
			return nFind;
		else
			nFind = nFind->_next;
	}

	return nullptr;
}

template<typename T>
inline Info<T>* GradeList<T>::InsertNode(Info<T>* node, const T& data)
{
	if (node == nullptr)
		return nullptr;

	Info<T>* nFind = node;
	Info<T>* nNext = nFind->_next;
	Info<T>* iNode = new Info<T>(data);

	nFind->_next = iNode;
	iNode->_prev = nFind;
	iNode->_next = nNext;
	nNext->_prev = iNode;

	_size++;

	return nNext;
}

template<typename T>
inline void GradeList<T>::DelBack()
{
	DelNode(_tail->_prev);
}

template<typename T>
inline GradeList<T>::GradeList()
{
	_head = new Info<T>();
	_tail = new Info<T>();
	_size = 0;

	_head->_prev = nullptr;
	_head->_next = _tail;
	_tail->_prev = _head;
	_tail->_next = nullptr;
}

template<typename T>
inline void GradeList<T>::AddInfo(const T& value)
{
	AddNode(_tail, value);
}

template<typename T>
inline void GradeList<T>::DeleteInfo(const T& value)
{
	DelNode(FindNode(_head, value));
}

template<typename T>
inline void GradeList<T>::InsertInfo(const T& value1, const T& value2)
{
	InsertNode(FindNode(_head, value1), value2);
}

template<typename T>
inline Info<T>* GradeList<T>::SearchInfo(const T& value)
{
	if (FindNode(_head, value) != nullptr)
	{
		Info<T>* temp = FindNode(_head, value);
		return temp;
	}

	return nullptr;
}

template<typename T>
inline Info<T>* GradeList<T>::SearchInfoForIndex(int idex)
{
	if (FindeNodeForIndex(idex) != nullptr)
	{
		Info<T>* temp = FindeNodeForIndex(idex);
		return temp;
	}

	return nullptr;
}

template<typename T>
inline bool GradeList<T>::SortingHigh()
{
	Info<T>* tHead = _head->_next;
	Info<T>* tTemp = tHead->_next;
	bool isSorting = false;

	for (; tHead != _tail; tHead = tHead->_next)
	{
		for (; tTemp != _tail; tTemp = tTemp->_next)
		{
			if (tHead->_id > tTemp->_id)

			{
				T tData = tHead->_data;
				tHead->_data = tTemp->_data;
				tTemp->_data = tData;
				isSorting = true;
			}
		}
	}

	return isSorting;
}

template<typename T>
inline bool GradeList<T>::SortingLow()
{
	Info<T>* tHead = _head->_next;
	Info<T>* tTemp = tHead->_next;
	bool isSorting = false;

	for (; tHead != _tail; tHead = tHead->_next)
	{
		for (; tTemp != _tail; tTemp = tTemp->_next)
		{
			if (tHead->_id < tTemp->_id)

			{
				T tData = tHead->_data;
				tHead->_data = tTemp->_data;
				tTemp->_data = tData;
				isSorting = true;
			}
		}
	}

	return isSorting;
}

template<typename T>
inline void GradeList<T>::AllDelete()
{
	while (_size > 0)
	{
		DelBack();
	}
	delete _head;
	delete _tail;
}
#pragma endregion

