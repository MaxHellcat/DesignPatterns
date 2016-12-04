//
//  Decorator.h
//  Exam
//
//  Created by Max Reshetey on 10/10/2016.
//  Copyright © 2016 Max Reshetey. All rights reserved.
//

#ifndef Decorator_h
#define Decorator_h

#include <iostream>

using namespace std;

// TODO: Add example of statically set decorator, i.e. using templates

// Name: Decorator (object structural), aka Wrapper
// Intent: Attach additional responsibilities to an object dynamically, without changing its interface. Decorators provide a flexible alternative to subclassing for extending functionality.
// Key: The decorator must conform to the interface of the component it decorates so that its presence is transparent to the component’s clients (transparent enclosure)
// Notes: Can be replaced with Strategy, in case root class is quite heavy. A decorator lets you change the skin of an object; a strategy lets you change the guts. These are two alternative ways of changing an object.

// Interfaces
class Item
{
public:
	virtual ~Item() {}

	virtual string name() const = 0;
};

class DecoratedItem: public Item
{
public:
	DecoratedItem(Item * item) : _item(item) {}
	virtual ~DecoratedItem() override { delete _item; }

	virtual string name() const override { return _item->name(); }

private:
	Item * _item = nullptr;
};

// Concrete classes
class Book: public Item
{
public:
	virtual string name() const override { return "Book"; }
};

class BoxDecor: public DecoratedItem
{
public:
	BoxDecor(Item * item) : DecoratedItem(item) {}

	virtual string name() const override { return "Boxed " + DecoratedItem::name(); }
};

class RibbonDecor: public DecoratedItem
{
public:
	RibbonDecor(Item * item) : DecoratedItem(item) {}

	virtual string name() const override { return "Ribbon tied " + DecoratedItem::name(); }
};

namespace Decorator
{
	void test()
	{
		cout << "=== Decorator pattern ===\n\n";

		Item * box = new RibbonDecor(new BoxDecor(new BoxDecor(new BoxDecor(new Book))));

		// Now we work with a much decorated box, like it's a simple box
		cout << "This is a " << box->name() << "\n\n";

		delete box;
	}
}

#endif /* Decorator_h */
