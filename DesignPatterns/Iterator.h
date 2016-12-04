//
//  Iterator.h
//  Exam
//
//  Created by Max Reshetey on 27/10/2016.
//  Copyright © 2016 Max Reshetey. All rights reserved.
//

#ifndef Iterator_h
#define Iterator_h

template <typename Item>
class List;

template <typename Item>
class Node;

// Important, the iterator implementation in the pattern's Example section in GoF appears to store _current as an integer index, thereby making list to O(n) seek on each call of iterator's current(). Which results in total O(n^2) for a regular list traversal.
// The implementation below uses a pointer to a list node instead to guarantee O(1) access, resulting in classic O(n) list traversal.

// TODO:
// - Iterator for composites, inorder, postorder, etc.
// - Other kinds of iterators (like reversed, etc.)
// - Automatic delete of created iterator, using proxy

// Name: Iterator (object behavioral), aka Cursor
// Intent: Provide a way to access the elements of an aggregate object sequentially without exposing its underlying representation.
// Key: The key idea in this pattern is to take the responsibility for access and traversal out of the list object and put it into an iterator object.
// Notes:

template <typename Item>
class AbstractIterator
{
public:
	virtual bool isDone() const = 0;
	virtual void next() = 0;
	virtual Item& current() const = 0;

	virtual ~AbstractIterator() {}

protected:
	AbstractIterator() {}
};

template <typename Item>
class ListIterator: public AbstractIterator<Item>
{
public:
	ListIterator(const List<Item> * list);

	virtual bool isDone() const override;

	virtual void next() override;

	virtual Item& current() const override;

private:
	Node<Item> * _current = nullptr;
};

namespace Iterator
{
	extern void test();
}

#endif /* Iterator_h */
