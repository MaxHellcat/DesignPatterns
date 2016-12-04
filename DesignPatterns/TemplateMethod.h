//
//  TemplateMethod.h
//  Exam
//
//  Created by Max Reshetey on 01/12/2016.
//  Copyright © 2016 Max Reshetey. All rights reserved.
//

#ifndef TemplateMethod_h
#define TemplateMethod_h

#include <iostream>
#include <string>

using namespace std;

// Name: Template Method (class behavioral)
// Intent: Define the skeleton of an algorithm in an operation, deferring some steps to subclasses. Template Method lets subclasses redefine certain steps of an algorithm without changing the algorithm's structure.
// Key:
// Notes: “Template methods lead to an inverted control structure that’s sometimes referred to as “the Hollywood principle,” that is, “Don’t call us, we’ll call you”

class Shape
{
public:
	virtual ~Shape() {}

	// Template method
	void printDescription()
	{
		cout << "This is a " << name() << " with square " << area() << " of " << color() << " color\n";
	}

protected:
	Shape() {}

	// Hook operations (may be overriden)
	virtual string color() const { return "white"; }

	// Primitive operations (i.e. abstract operations, must be overriden)
	virtual string name() const = 0;
	virtual float area() const = 0;
};

class ARect: public Shape
{
public:
	ARect(float width, float height): _width(width), _height(height) { }

	// Only implementing abstract operations
	virtual string name() const override { return "Rect"; }
	virtual float area() const override { return _width * _height; }

private:
	float _width = 0.0, _height = 0.0;
};

class ACircle: public Shape
{
public:
	ACircle(float radius): _radius(radius) { }

	virtual string name() const override { return "Circle"; }
	virtual float area() const override { return PI * _radius * _radius; }

	// Also overriding hook operations
	virtual string color() const override { return "red"; }

private:
	float _radius = 0.0;

	constexpr static const float PI = 3.14;
};

namespace TemplateMethod
{
	void test()
	{
		cout << "=== Template Method pattern ===\n\n";

		Shape * figure = new ARect(5.0, 7.0);
		figure->printDescription();
		delete figure;

		figure = new ACircle(3.0);
		figure->printDescription();
		delete figure;

		cout << endl;
	}
}

#endif /* TemplateMethod_h */
