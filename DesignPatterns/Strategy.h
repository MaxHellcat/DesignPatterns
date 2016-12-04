//
//  Strategy.h
//  Exam
//
//  Created by Max Reshetey on 07/10/2016.
//  Copyright © 2016 Max Reshetey. All rights reserved.
//

#ifndef Strategy_h
#define Strategy_h

#include "List.h"
#include <iostream>

using namespace std;

// TODO: Add example of statically set strategy, using templates

// Name: Strategy (object behavioral), aka Policy
// Intent: Define a family of algorithms, encapsulate each one, and make them interchangeable. Strategy lets the algorithm vary independently from clients that use it.
// Key: The key to applying the Strategy pattern is designing interfaces for the strategy and its context that are general enough to support a range of algorithms.

class ListWithStrategy;

class AbstractStrategy
{
public:
	virtual ~AbstractStrategy() {}

	// Using techique: Context passes itself as an argument (tighter coupling)
	virtual void start(ListWithStrategy * list) = 0;

protected:
	AbstractStrategy() {}
};

// See how algorithm related logic/data is localized in strategy
class ReverseStrategy: public AbstractStrategy
{
public:
	virtual void start(ListWithStrategy * list) override
	{
		cout << "ReverseStrategy: Reversing list " << list << "...\n";
	}
};

// See how easy it is to add and vary new strategies without touching context class
class SortStrategy: public AbstractStrategy
{
};

class InsertionSortStrategy: public SortStrategy
{
public:
	virtual void start(ListWithStrategy * list) override
	{
		cout << "InsertionSortStrategy: Sorting list " << list << "...\n";
	}
};

class MergeSortStrategy: public SortStrategy
{
public:
	virtual void start(ListWithStrategy * list) override
	{
		cout << "MergeSortStrategy: Sorting list " << list << "...\n";
	}
};

class ListWithStrategy: public List<int>
{
public:
	void setStrategy(AbstractStrategy * strategy) { delete _strategy; _strategy = strategy; }
	void performStrategy() { _strategy->start(this); }

private:
	AbstractStrategy * _strategy = nullptr;
};

namespace Strategy
{
	void test()
	{
		cout << "=== Strategy pattern ===\n\n";
		
		// Example here shows how a data structure can be parameterized by different strategies that can be replaced at run-time.
		// In real live containers know nothing about algorithms, but we use it here to show the pattern.

		ListWithStrategy list;

		// See how easy it is to relace strategies
		list.setStrategy(new ReverseStrategy);
		list.performStrategy();

		list.setStrategy(new InsertionSortStrategy);
		list.performStrategy();

		list.setStrategy(new MergeSortStrategy);
		list.performStrategy();

		list.setStrategy(nullptr);

		cout << endl;
	}
}

#endif /* Strategy_h */
