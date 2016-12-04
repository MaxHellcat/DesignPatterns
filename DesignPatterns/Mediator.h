//
//  Mediator.h
//  Exam
//
//  Created by Max Reshetey on 26/11/2016.
//  Copyright © 2016 Max Reshetey. All rights reserved.
//

#ifndef Mediator_h
#define Mediator_h

#include <iostream>

using namespace std;

// Example here uses the same "one-handler-for-all-widgets" approach as GoF does, resulting in one-for-all if-else chain in viewValueChanged. A more flexible way would be to specify each widget's handler separately, using e.g. pointers to director's methods (see setHandler)

// Name: Mediator (object behavioral)
// Intent: Define an object that encapsulates how a set of objects interact. Mediator promotes loose coupling by keeping objects from referring to each other explicitly, and it lets you vary their interaction independently.
// Key:
// Notes: File Owner for UIView XIB, and subclassed UIViewController are examples of Mediator

class MyView;

// Abstract mediator
class Director
{
public:
	virtual ~Director() {}

	virtual void viewValueChanged(MyView *) = 0; // All objects interaction handled here

	virtual void storeModelData() { cout << "Director: Storing model data...\n"; }

protected:
	virtual void createViews() = 0;
};

class MyView
{
public:
	virtual void valueChanged() { _director->viewValueChanged(this); }

	void setDirector(Director * director) { _director = director; }

//	typedef void (Director::* Handler)();
//	void setHandler(Handler handler) { _handler = handler; }

private:
	Director * _director = nullptr;
//	Handler _handler;
};

class MyButton: public MyView
{
public:
	virtual void valueChanged() override
	{
		cout << "Button: Value changed, i.e. button tapped\n";

		MyView::valueChanged();
	}
};

class TextField: public MyView
{
public:
	virtual void valueChanged() override
	{
		cout << "TextField: Value changed\n";

		MyView::valueChanged();
	}

	string text() { return ""; }
	void setText(string text) { cout << "TextField: Set text\n"; }
};

class DatePicker: public MyView
{
public:
	virtual void valueChanged() override
	{
		cout << "DatePicker: Value changed, i.e. date picked\n";

		MyView::valueChanged();
	}

	string date() { return "25/01/1982"; }
	void setDate(string date) { cout << "DatePicker: Set date\n"; }
};

// Concrete mediator
class ViewDirector: public Director
{
public:
	virtual void viewValueChanged(MyView * view) override
	{
		if (view == _datePicker)
		{
			_textField->setText(_datePicker->date());
		}
		else if (view == _textField)
		{
			_datePicker->setDate(_textField->text());
		}
		else if (view == _applyButton)
		{
			storeModelData();
		}
	}

	virtual void createViews() override
	{
		cout << "ViewDirector: Create views\n";

		_datePicker = new DatePicker();
		_datePicker->setDirector(this);

		_textField = new TextField();
		_textField->setDirector(this);

		_applyButton = new MyButton();
		_applyButton->setDirector(this);
	}

	void interactWithControls()
	{
		cout << "Picking new date in date picker...\n";
		_datePicker->valueChanged();

		cout << endl;

		cout << "Typing new date in text picker...\n";
		_textField->valueChanged();

		cout << endl;

		cout << "Tapping apply button...\n";
		_applyButton->valueChanged();
	}

	virtual ~ViewDirector() override
	{
		delete _datePicker;
		delete _textField;
		delete _applyButton;
	}

private:
	DatePicker * _datePicker = nullptr;
	TextField * _textField = nullptr;
	MyButton * _applyButton = nullptr;
};

namespace Mediator
{
	void test()
	{
		cout << "=== Mediator pattern ===\n\n";

		ViewDirector director;

		director.createViews();

		cout << endl;

		director.interactWithControls();

		cout << endl;
	}
}

#endif /* Mediator_h */
