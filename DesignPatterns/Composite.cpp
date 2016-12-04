//
//  Composite.cpp
//  Exam
//
//  Created by Max Reshetey on 31/10/2016.
//  Copyright © 2016 Max Reshetey. All rights reserved.
//

#include "Composite.h"
#include "Visitor.h"

#include <iostream>

using namespace std;

// MARK: - Visitor pattern related
void Fuselage::accept(AbstractVisitor& visitor) { visitor.checkFuselage(this); }
void Tail::accept(AbstractVisitor& visitor) { visitor.checkTail(this); }
void Engine::accept(AbstractVisitor& visitor) { visitor.checkEngine(this); }
void Wing::accept(AbstractVisitor& visitor)
{
	CompositeComponent::accept(visitor);
	visitor.checkWing(this);
}
void Airplane::accept(AbstractVisitor& visitor)
{
	CompositeComponent::accept(visitor);
	visitor.checkAirplane(this);
}

namespace Composite
{
	Airplane * createAirplane()
	{
		Airplane * airplane = new Airplane("Boeing 747");

		airplane->addComponent(new Fuselage("Fuselage"));
		airplane->addComponent(new Tail("Tail"));
		airplane->addComponent(new Wing("Left wing"));
		airplane->addComponent(new Wing("Right wing"));

		Component * leftWing = airplane->component("Left wing");
		leftWing->addComponent(new Engine("Engine 1"));
		leftWing->addComponent(new Engine("Engine 3"));

		Component * rightWing = airplane->component("Right wing");
		rightWing->addComponent(new Engine("Engine 2"));
		rightWing->addComponent(new Engine("Engine 4"));

		cout << "Created \"" << airplane->name() << "\"\n";

		return airplane;
	}

	void test()
	{
		cout << "=== Composite pattern ===\n";

		const Airplane * airplane = createAirplane();

		delete airplane;
	}
}
