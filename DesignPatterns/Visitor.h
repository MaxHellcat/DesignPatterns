//
//  Visitor.h
//  Exam
//
//  Created by Max Reshetey on 31/10/2016.
//  Copyright © 2016 Max Reshetey. All rights reserved.
//

#ifndef Visitor_h
#define Visitor_h

class Component;
class Fuselage;
class Tail;
class Wing;
class Engine;
class Airplane;

// TOO: Another type of visitor to show easy modification and switching

// Name: Visitor (object behavioral)
// Intent: Represent an operation to be performed on the elements of an object structure. Visitor lets you define a new operation without changing the classes of the elements on which it operates.
// Key: The Double-dispatch techique, where the operation that gets executed depends on both the type of Visitor and the type of Element it visits. Instead of binding operations statically into the Element interface, you can consolidate the operations in a Visitor and use Accept to do the binding at run-time.
// Notes: Extending the Element interface amounts to defining one new Visitor subclass rather than many new Element subclasses.
class AbstractVisitor
{
public:
	virtual void checkFuselage(Fuselage *) = 0;
	virtual void checkTail(Tail *) = 0;
	virtual void checkWing(Wing *) = 0;
	virtual void checkEngine(Engine *) = 0;
	virtual void checkAirplane(Airplane *) = 0;

	virtual ~AbstractVisitor() {}

protected:
	AbstractVisitor() {}
};

// See how easy it is to define new visitor, no modifying of Component interface, easy extending and reuse
class PriceCheckVisitor: public AbstractVisitor
{
public:
	virtual void checkFuselage(Fuselage *) override;
	virtual void checkTail(Tail *) override;
	virtual void checkWing(Wing *) override;
	virtual void checkEngine(Engine *) override;
	virtual void checkAirplane(Airplane *) override;

	int totalPrice() const { return _totalPrice; }

private:
	int _totalPrice = 0;
};

class ComponentCountVisitor: public AbstractVisitor
{
public:
	virtual void checkFuselage(Fuselage *) override;
	virtual void checkTail(Tail *) override;
	virtual void checkWing(Wing *) override;
	virtual void checkEngine(Engine *) override;
	virtual void checkAirplane(Airplane *) override {};

	int fuselageCount = 0, tailCount = 0, wingCount = 0, engineCount = 0;
};

namespace Visitor
{
	extern void test();
}

#endif /* Visitor_h */
