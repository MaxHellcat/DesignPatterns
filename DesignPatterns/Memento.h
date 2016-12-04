//
//  Memento.h
//  Exam
//
//  Created by Max Reshetey on 28/11/2016.
//  Copyright © 2016 Max Reshetey. All rights reserved.
//

#ifndef Memento_h
#define Memento_h

#include <iostream>

using namespace std;

// Name: Memento (object behavioral), aka Token
// Intent: Without violating incapsulation, capture and externalize an object's internal state so that the object can be restored to this state later.
// Key: Only the originator can store and retrieve information from the memento — the memento is “opaque” to other objects.
// Notes:

struct Point { float x, y; };
struct Size { float width, height; };

// Closed to all except originator, to allow set/restore internal data
class FigureMemento
{
public: // Narrow public interface
	virtual ~FigureMemento() { cout << "Memento " << this << " deleted\n"; }

private: // Private members accessible only to Originator, i.e. Figure
	friend class Figure;

	FigureMemento(Point position, float angle, int shaderIndex, int textureIndex):
	position(position), angle(angle), shaderIndex(shaderIndex), textureIndex(textureIndex)
	{
		cout << "Memento " << this << " created\n";
	}

	Point position;
	float angle;
	int shaderIndex;
	int textureIndex;
};

// Originator, contains internal state captured by memento
class Figure
{
public:
	virtual void draw() = 0;

	Point position() const { return _position; }
	void setPosition(Point position) { _position = position; }

	float angle() { return _angle; }
	void setAngle(float angle) { _angle = angle; }

	FigureMemento * createMemento()
	{
		return new FigureMemento(_position, _angle, _shaderIndex, _textureIndex);
	}

	void applyMemento(FigureMemento& memento)
	{
		_position = memento.position;
		_angle = memento.angle;
		_shaderIndex = memento.shaderIndex;
		_textureIndex = memento.textureIndex;
	}

	// For simplicity (to show the pattern in action), allow modifying internal data as below. Note, however there's no any getters.
	// In general case internal data may not have any setting handles to outside (e.g. due to referencing some global state)
	void setInternalDrawingDate(int shaderIndex, int textureIndex)
	{
		_shaderIndex = shaderIndex;
		_textureIndex = textureIndex;
	}

protected:
	Point _position = {0.0, 0.0};
	float _angle = 0.0;

	// Internal data that never exposed
	int _shaderIndex = 0;
	int _textureIndex = 0;
};

class Rect: public Figure
{
public:
	virtual void draw() override { cout << "Drawing rect at (" << position().x << ", " << position().y << ") angled " << angle() << "\n"; }

	Size size() const { return _size; }

private:
	Size _size;
};

namespace Memento
{
	void test()
	{
		cout << "=== Memento pattern ===\n\n";

		Rect rect;
		rect.setPosition({25.0, 10.0});
		rect.draw();

		FigureMemento& memento = (*rect.createMemento());

		// Capture memento, modify internal data and draw
		rect.setPosition({15.0, 0.0});
		rect.setAngle(45.0);
		rect.setInternalDrawingDate(1, 5);
		rect.draw();

		cout << endl;

		cout << "Restoring state...\n";

		cout << endl;

		// Restore original figure state and draw
		rect.applyMemento(memento);
		rect.draw();

		delete &memento;

		cout << endl;
	}
}

#endif /* Memento_h */
