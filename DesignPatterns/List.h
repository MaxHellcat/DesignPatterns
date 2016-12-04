//
//  List.h
//  Exam
//
//  Created by Max Reshetey on 27/10/2016.
//  Copyright © 2016 Max Reshetey. All rights reserved.
//

#ifndef List_h
#define List_h

#include "Iterator.h" // Just for inline createIterator(), which causes link error if defined in .cpp

template <typename Item>
class AbstractIterator;

template <typename Item>
class Node
{
public:
	Node * next = nullptr;
	Item item;

	Node(Item anItem): item(anItem) {}
};

template <typename Item>
class List
{
public:
	virtual AbstractIterator<Item> * createIterator() // Factory method on guard
	{
		return new ListIterator<Item>(this);
	};

	void append(Node<Item> * node)
	{
		if (_head == nullptr)
		{
			_head = node;
		}
		else
		{
			Node<Item> * tail = _head;

			while (tail->next != nullptr)
			{
				tail = tail->next;
			}

			tail->next = node;
		}
	}

	int count() const
	{
		int count = 0;

		for (Node<Item> * node = _head; node != nullptr; node = node->next )
		{
			count++;
		}

		return count;
	}

	void deleteAll()
	{
		Node<Item> * node = _head;

		while (node)
		{
			Node<Item> * tmpNode = node;

			node = node->next;

			delete tmpNode;
		}

		_head = nullptr;
	}

	Node<Item> * head() const { return _head; }

private:
	Node<Item> * _head = nullptr;
};

#endif /* List_h */
