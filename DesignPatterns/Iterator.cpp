//
//  Iterator.cpp
//  Exam
//
//  Created by Max Reshetey on 27/10/2016.
//  Copyright © 2016 Max Reshetey. All rights reserved.
//

#include "List.h"
#include "Iterator.h"

#include <iostream>

using namespace std;

template <typename Item>
ListIterator<Item>::ListIterator(const List<Item> * list) : _current(list->head()) {}

template <typename Item>
bool ListIterator<Item>::isDone() const
{
	return _current == nullptr;
}

template <typename Item>
void ListIterator<Item>::next()
{
	_current = _current->next;
}

template <typename Item>
Item& ListIterator<Item>::current() const
{
	return _current->item;
}

namespace Iterator
{
	void test()
	{
		cout << "=== Iterator pattern ===\n\n";

		List<int> list;

		for (int i = 0; i < 5; i++)
		{
			list.append(new Node<int>(i+1));
		}

		cout << "List count: " << list.count() << "\n";

		// Note how we use a factory method to avoid specifying the concrete iterator class
		AbstractIterator<int> * iter = list.createIterator();

		// Note how iterator hides container's internal structure
		while (!iter->isDone())
		{
			cout << "Val: " << iter->current() << "\n";

			iter->next();
		}

		list.deleteAll();

		// TODO: See how we must delete iterator manually :)
		delete iter;
	}
}
