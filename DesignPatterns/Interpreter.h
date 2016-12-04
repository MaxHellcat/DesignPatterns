//
//  Interpreter.hpp
//  Exam
//
//  Created by Max Reshetey on 23/11/2016.
//  Copyright © 2016 Max Reshetey. All rights reserved.
//

#ifndef Interpreter_h
#define Interpreter_h

#include <iostream>
#include <map>

using namespace std;

// Name: Interpreter (class behavioral)
// Intent: Given a language, provide a representation for its grammar along with an interpreter that uses the representation to interpret sentences in the language.
// Key:
// Notes:

class VariableExpression;

class Context
{
public:
	bool lookup(string); // const
	void assign(VariableExpression* expression, bool value);

private:
	map<string, bool> _map;
};

class BooleanExpression
{
public:
	BooleanExpression() {}
	virtual ~BooleanExpression() {}

	virtual bool evaluate(Context&) = 0;
	virtual BooleanExpression* replace(string, BooleanExpression&) = 0;
	virtual BooleanExpression* copy() const = 0;
};

// Represents a named value
class VariableExpression: public BooleanExpression
{
public:
	VariableExpression(string name): _name(name) {}
	virtual ~VariableExpression() {}

	virtual bool evaluate(Context& context) override
	{
		return context.lookup(_name);
	}

	virtual BooleanExpression* replace(string name, BooleanExpression& expression) override
	{
		if (name == _name) {
			return expression.copy();
		}

		return new VariableExpression(_name);
	}

	virtual BooleanExpression* copy() const override
	{
		return new VariableExpression(_name);
	}

	string name() const { return _name; }

private:
	string _name;
};

class AndExpression: public BooleanExpression
{
public:
	AndExpression(BooleanExpression* left, BooleanExpression* right): _leftOperand(left), _rightOperand(right) {};
	virtual ~AndExpression() { delete _leftOperand; delete _rightOperand; }

	virtual bool evaluate(Context& context) override
	{
		return _leftOperand->evaluate(context) && _rightOperand->evaluate(context);
	}

	virtual BooleanExpression* replace(string name, BooleanExpression& expression) override
	{
		return new AndExpression(_leftOperand->replace(name, expression), _rightOperand->replace(name, expression));
	}

	virtual BooleanExpression* copy() const override
	{
		return new AndExpression(_leftOperand->copy(), _rightOperand->copy());
	};

private:
	BooleanExpression * _leftOperand, * _rightOperand;
};

namespace Interpreter
{
	extern void test();
}

#endif /* Interpreter_h */
