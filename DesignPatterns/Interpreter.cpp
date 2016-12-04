//
//  Interpreter.cpp
//  Exam
//
//  Created by Max Reshetey on 23/11/2016.
//  Copyright © 2016 Max Reshetey. All rights reserved.
//

#include "Interpreter.h"

bool Context::lookup(string name)
{
	return _map[name];
}

void Context::assign(VariableExpression* expression, bool value)
{
	_map[expression->name()] = value;
};

namespace Interpreter
{
	void test()
	{
		cout << "=== Interpreter pattern ===\n\n";

		VariableExpression * x = new VariableExpression("X");
		VariableExpression * y = new VariableExpression("Y");

		// Simple (true && false) expression
		Context context;
		context.assign(x, true);
		context.assign(y, false);

		BooleanExpression * expression = new AndExpression(x, y);

		bool result	= expression->evaluate(context);

		cout << "See interpretation result: " << result << "\n";

		// Now replace false with true
		VariableExpression * z = new VariableExpression("Z");
		context.assign(z, true);

		BooleanExpression * changedExpression = expression->replace("Y", *z);
		result = changedExpression->evaluate(context);

		cout << "See interpretation result: " << result << "\n";

		delete expression;
		delete changedExpression;

		cout << endl;
	}
}
