//
//  Facade.h
//  Exam
//
//  Created by Max Reshetey on 11/11/2016.
//  Copyright © 2016 Max Reshetey. All rights reserved.
//

#ifndef Facade_h
#define Facade_h

#include <iostream>

using namespace std;

// Name: Facade (object structural)
// Intent: Provide a unified interface to a set of interfaces in a subsystem. Facade provides a higher-level interface that makes the subsystem easier to use.
// Key:
// Notes:
class Token {};
class ByteCodeStream {};

// The Scanner class takes a stream of characters and produces a stream of tokens, one token at a time.
class Scanner
{
public:
	Scanner(istream& stream) :_inputStream(stream) {}
	virtual ~Scanner() {}

//	virtual Token& scan() { return *(new Token); }

private:
	istream& _inputStream;
};

class VariableNode;
//class AssignmentNode;
//class ConditionNode;

class CodeGenerator
{
public:
	virtual void visit(VariableNode * variableNode) { cout << "CodeGenerator: Making code...\n"; }
//	virtual void visit(AssignmentNode * variableNode) { cout << "CodeGenerator: Making code...\n"; }
//	virtual void visit(ConditionNode * variableNode) { cout << "CodeGenerator: Making code...\n"; }

protected:
	CodeGenerator(ByteCodeStream& stream) {}
};

// The parse tree is made up of instances of Node subclasses such as StatementNode, ExpressionNode, and so forth
class ProgramNode
{
public:
	void position(int& line, int& index) {}

	virtual void add(ProgramNode * node) {}
	virtual void remove(ProgramNode * node) {}

	virtual void traverse(CodeGenerator * codeGenerator)
	{
		cout << "Node: Traversing...\n";
	}
};

class VariableNode: public ProgramNode
{
public:
	virtual void traverse(CodeGenerator * codeGenerator) override
	{
		ProgramNode::traverse(codeGenerator);

		codeGenerator->visit(this);
	}
};
//class AssignmentNode: public Node {};
//class ConditionNode: public Node {};

class RISCCodeGenerator: public CodeGenerator
{
public:
	RISCCodeGenerator(ByteCodeStream& stream): CodeGenerator(stream) {}
};

class ProgramNodeBuilder
{
public:
	virtual ProgramNode * variable(string varName) const { return nullptr; }
	virtual ProgramNode * assignment(ProgramNode * var, ProgramNode * expression) { return nullptr; }
	virtual ProgramNode * condition(ProgramNode * condition, ProgramNode * truePart, ProgramNode * falsePart) { return nullptr; }

	ProgramNode * rootNode() { _node = new VariableNode; return _node; }

	~ProgramNodeBuilder() { delete _node; }

private:
	ProgramNode * _node = nullptr;
};

// The class Parser uses a ProgramNodeBuilder to construct a parse tree from a Scanner’s tokens.
class Parser
{
public:
	Parser() {}
	virtual ~Parser() {}

	virtual void parse(Scanner& scanner, ProgramNodeBuilder& builder) { cout << "Parser: Parsing...\n"; }
};

// Facade
class Compiler
{
public:
	// Apart of Facade below are conglamerate of pattern examples
	virtual void compile(istream& input, ByteCodeStream& ouput)
	{
		cout << "Compiler (facade): Compiling...\n";

		Scanner scanner(input);
		ProgramNodeBuilder builder;
		Parser parser;

		parser.parse(scanner, builder); // Builder pattern

		ProgramNode * parseTree = builder.rootNode(); // Composite pattern
		RISCCodeGenerator codeGenerator(ouput);

		parseTree->traverse(&codeGenerator); // Visitor patterns

		cout << "Compiler: Done\n";
	}
};

#include <fstream>

namespace Facade
{
	void test()
	{
		cout << "=== Facade pattern ===\n";

		cout << endl;

		Compiler compiler;
		ifstream file("code.txt");
		ByteCodeStream byteCode;

		// See the compile method making calls to subsystem to perform a high-level task
		compiler.compile(file, byteCode);

		cout << endl;
	}
}

#endif /* Singleton_h */
