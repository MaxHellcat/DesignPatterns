//
//  ChainOfResponsibility.h
//  Exam
//
//  Created by Max Reshetey on 17/11/2016.
//  Copyright © 2016 Max Reshetey. All rights reserved.
//

#ifndef ChainOfResponsibility_h
#define ChainOfResponsibility_h

#include <iostream>
#include <list>

using namespace std;

// Name: Chain Of Responsibility (object behavioral)
// Intent: Avoid coupling the sender of a request to its receiver by giving more than one object a chance to handle the request. Chain the receiving objects and pass the request along the chain until an object handles it.
// Key:
// Notes: An example of pattern is UIResponder in UIKit (The Responder Chain)
class Responder
{
public:
	// Note how default imp just passes handling to the next object in the chain
	virtual void handleTouch()
	{
		cout << name() << ": Handling touch...\n";

		if (_next != nullptr)
		{
			_next->handleTouch();
		}
	}

	virtual string name() const { return "Responder"; }

protected:
	// Make it public to allow any Responder to be the next handler, not only parent view as done here
	void setNext(Responder * next) { _next = next; }

private:
	Responder * _next = nullptr;
};

class View: public Responder
{
public:
	virtual ~View() { for (auto view : _subviews) { delete view; } }

	virtual string name() const override { return "View"; }

	void addSubview(View * view)
	{
		_subviews.push_back(view);

		view->setNext(this);
	}

private:
	list<View *> _subviews;
};

class Button: public View
{
public:
	virtual string name() const override { return "Button"; }
};

class HandlingButton: public Button
{
public:
	virtual string name() const override { return "HandlingButton"; }

	virtual void handleTouch() override
	{
		cout << "I, the " << name() << ", will handle it by myself here\n";
	}
};

namespace ChainOfResponsibility
{
	void test()
	{
		cout << "=== Chain Of Responsibility pattern ===\n\n";

		// Example here is a view hierarchy as follows: View -> Subview -> [Button, HandlingButton], where
		// both buttons receive a touch (one passes up along the chain, another handles)
		View view;

		View * subview = new View();
		view.addSubview(subview);

		Button * button = new Button();
		subview->addSubview(button);

		// Notice how default subviews' implementation just passes the event up the responding chain
		button->handleTouch();

		cout << endl;

		HandlingButton * handlingButton = new HandlingButton();
		subview->addSubview(handlingButton);

		// Here custom button handles the event itself thereby stopping event propagation
		handlingButton->handleTouch();

		cout << endl;
	}
}

#endif /* ChainOfResponsibility_h */
