//
//  Observer.h
//  Exam
//
//  Created by Max Reshetey on 30/11/2016.
//  Copyright © 2016 Max Reshetey. All rights reserved.
//

#ifndef Observer_h
#define Observer_h

#include <iostream>
#include <list>

using namespace std;

// Name: Observer (object behavioral), aka Dependents, Publish-Subscribe
// Intent: Define a one-to-many dependency between objects so that when one object changes state, all its dependents are notified and updated automatically.
// Key:
// Notes:

class Subject;

class AbstractObserver
{
public:
	virtual ~AbstractObserver() {}
	virtual void update(Subject * subject) = 0; // Sending minimal/general info (pull model)

protected:
	AbstractObserver() {}
};

class Subject
{
public:
	virtual ~Subject() {}

	virtual void attach(AbstractObserver * observer) { _observers.push_back(observer); }
	virtual void detach(AbstractObserver * observer) { _observers.remove(observer); }
	virtual void notify()
	{
		for (auto observer : _observers)
		{
			observer->update(this);
		}
	}

protected:
	Subject() {}

private:
	list<AbstractObserver *> _observers;
};

class ChartData: public Subject
{
public:
	list<int>& values() { return _values; }

	void setData(list<int> values)
	{
		cout << "ChartData: Setting new data\n";

		_values = values;

		notify();
	}

private:
	list<int> _values;
};

class AView: public AbstractObserver
{
public:
	virtual void update(Subject * subject) override
	{
		ChartData * chartData = (ChartData *)subject;

		cout << name() << ": Updating with ";

		for (int val: chartData->values()) { cout << val << ", "; }

		cout << "\n";
	}

	virtual string name() = 0;
};

class BarChart: public AView
{
public:
	virtual string name() override { return "BarChart"; }
};

class PieChart: public AView
{
public:
	virtual string name() override { return "PieChart"; }
};

namespace Observer
{
	void test()
	{
		cout << "=== Observer pattern ===\n\n";

		// Example here shows one ChartData subject and two widgets updated whenever subject changes its data

		ChartData data;

		BarChart barChart;
		PieChart pieChart;

		data.attach(&barChart);
		data.attach(&pieChart);

		data.setData({1, 2, 3});

		cout << endl;

		data.setData({5, 7, 9});

		cout << endl;
	}
}

#endif /* Observer_h */
