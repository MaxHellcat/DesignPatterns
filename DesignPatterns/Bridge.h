//
//  Bridge.h
//  Exam
//
//  Created by Max Reshetey on 21/10/2016.
//  Copyright © 2016 Max Reshetey. All rights reserved.
//

#ifndef Bridge_h
#define Bridge_h

#include <iostream>

using namespace std;

// Name: Bridge (object structural), aka Handle/Body
// Intent: Decouple an abstraction from its implementation so that the two can vary independently.
// Key: The important thing to realize is that Window’s interface caters to the applications
//	programmer, while WindowImp caters to window systems.
// Notes:

// WindowImp is an abstract class for objects that encapsulate window system-dependent code.
// By hiding the implementations in WindowImp classes, we avoid polluting the Window classes
//	with window system dependencies, which keeps the Window class hierarchy comparatively small and stable.

class WindowImp // Goes first so Window can see the definition
{
public:
	virtual ~WindowImp() {}

	virtual void deviceDrawRect() = 0;
	virtual void deviceDrawText() = 0;

protected:
	WindowImp() {}
};

class MacWindowImp: public WindowImp
{
public:
	virtual void deviceDrawRect() override { cout << "Drawing MacOS rect, e.g. origin.(x|y)+offset...\n"; }
	virtual void deviceDrawText() override { cout << "Drawing MacOS text...\n"; }
};

class WinWindowImp: public WindowImp
{
public:
	virtual void deviceDrawRect() { cout << "Drawing Windows rect, e.g. absolute coords...\n"; }
	virtual void deviceDrawText() { cout << "Drawing Windows text...\n"; }
};

// Window is an abstract class. Concrete subclasses of Window support the different
// kinds of windows that users deal with.
class Window
{
public:
	virtual void draw()
	{
		cout << "Drawing abstract window..." << endl;

		_imp->deviceDrawRect();
	}

	virtual void drawText()
	{
		cout << "Drawing abstract text..." << endl;

		_imp->deviceDrawText();
	}

	void setImp(WindowImp *imp)
	{
		delete _imp;

		_imp = imp;
	}

	Window(WindowImp *imp) : _imp(imp) {}
	virtual ~Window() { delete _imp; }

private:
	WindowImp *_imp = nullptr;
};

class ButtonWindow: public Window
{
public:
	// Drawing button envolves rect and title
	virtual void draw() override
	{
		cout << "Drawing abstract button..." << endl;

		Window::draw();
		Window::drawText();
	}

	ButtonWindow(WindowImp *imp) : Window(imp) { }
};

namespace Bridge
{
	void test()
	{
		cout << "=== Bridge pattern ===\n";

		{
			// Show logical window tied with device specific window
			const auto window = new Window(new MacWindowImp());
			window->draw();
			delete window;
		}

		cout << endl;

		{
			// Show run-time replacement of implementation for button
			const auto button = new ButtonWindow(new MacWindowImp());
			button->draw();

			cout << endl;

			button->setImp(new WinWindowImp);
			button->draw();

			delete button;
		}

		cout << endl;
	}
}

#endif /* Bridge_h */
