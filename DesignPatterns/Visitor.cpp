//
//  Visitor.cpp
//  Exam
//
//  Created by Max Reshetey on 31/10/2016.
//  Copyright © 2016 Max Reshetey. All rights reserved.
//

#include "Visitor.h"
#include "Composite.h"

#include <iostream>

using namespace std;

void PriceCheckVisitor::checkFuselage(Fuselage * component) { _totalPrice += component->price(); }
void PriceCheckVisitor::checkTail(Tail * component) { _totalPrice += component->price(); }
void PriceCheckVisitor::checkWing(Wing * component) { _totalPrice += component->price(); }
void PriceCheckVisitor::checkEngine(Engine * component) { _totalPrice += component->price(); }
void PriceCheckVisitor::checkAirplane(Airplane * component) { _totalPrice += component->price(); }

void ComponentCountVisitor::checkFuselage(Fuselage * component) { fuselageCount++; }
void ComponentCountVisitor::checkTail(Tail * component) { tailCount++; }
void ComponentCountVisitor::checkWing(Wing * component) { wingCount++; }
void ComponentCountVisitor::checkEngine(Engine * component) { engineCount++; }

namespace Visitor
{
	void test()
	{
		cout << "=== Visitor pattern ===\n\n";

		Airplane * airplane = Composite::createAirplane();

		// TODO: Here we stick to the approach: Component is responsible for traversing the object structure
		// Another approach is to use iterator, but Composite hasn't defined CompositeIterator

		PriceCheckVisitor priceChecker;
		airplane->accept(priceChecker);

		cout << "PriceCheckVisitor: total price: " << priceChecker.totalPrice() << "\n";

		ComponentCountVisitor countVisitor;
		airplane->accept(countVisitor);
		cout << "ComponentCountVisitor: Fuselages " << countVisitor.fuselageCount << ", tails " << countVisitor.tailCount << ", wings " << countVisitor.wingCount << ", engines " << countVisitor.engineCount << "\n";

		cout << endl;

		delete airplane;
	}
}
