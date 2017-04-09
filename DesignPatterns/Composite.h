//
//  Composite.h
//  Exam
//
//  Created by Max Reshetey on 07/10/2016.
//  Copyright © 2016 Max Reshetey. All rights reserved.
//

#ifndef Composite_h
#define Composite_h

#include <iostream>
#include <list>

class AbstractStrategy;
class AbstractVisitor;

// Name: Composite (object structural)
// Intent: Compose objects (via recursive composition) into tree structures to represent part-whole hierarchies. Composite lets clients treat individual objects and compositions of objects uniformly.
// Key: The key to the Composite pattern is an abstract class that represents both primitives and their containers.

// The Component defines interface to enforce uniform handling
class Component
{
public:
	virtual ~Component() { std::cout << "Component " << name() << " deleted\n"; }

	virtual std::string name() const { return _name; }
	virtual int price() const { return 0; }

	virtual void addComponent(Component * component) {};
	virtual void removeComponent(Component * component) {};
	virtual Component * component(std::string name) { return nullptr; }

// MARK: - Visitor pattern related
	virtual void accept(AbstractVisitor& visitor) { }

protected:
	Component(std::string name): _name(name) {}

private:
	std::string _name;
};

// The complex component inherits component's interface, implementing children management, etc.
class CompositeComponent: public Component
{
public:
	virtual ~CompositeComponent()
	{
		for (auto component : _components)
		{
			delete component;
		}
	}

	virtual void addComponent(Component * component) override { _components.push_back(component); }
	virtual void removeComponent(Component * component) override { _components.remove(component); }
	virtual Component * component(std::string name) override
	{
		for (auto component : _components)
		{
			if (component->name() == name)
			{
				return component;
			}
		}

		return Component::component(name);
	}

	std::list<Component *> components() { return _components; }

// MARK: - Visitor pattern related
	virtual void accept(AbstractVisitor& visitor) override
	{
		for (auto component : _components)
		{
			component->accept(visitor);
		}
	}

protected:
	CompositeComponent(std::string name): Component(name) {}

private:
	std::list<Component *> _components;
};

// MARK: - Visitor pattern related
// These subclasses are derived in fact only to accomodate to Visitor pattern
class Fuselage: public Component
{
public:
	Fuselage(std::string name): Component(name) {}

	virtual int price() const override { return 500; }

	virtual void accept(AbstractVisitor& visitor) override;
};

class Tail: public Component
{
public:
	Tail(std::string name): Component(name) {}

	virtual int price() const override { return 100; }

	virtual void accept(AbstractVisitor& visitor) override;
};

class Engine: public Component
{
public:
	Engine(std::string name): Component(name) {}
	
	virtual int price() const override { return 500; }
	
	virtual void accept(AbstractVisitor& visitor) override;
};

class Wing: public CompositeComponent
{
public:
	Wing(std::string name): CompositeComponent(name) {}

	virtual int price() const override { return 100; }

	virtual void accept(AbstractVisitor& visitor) override;
};

class Airplane: public CompositeComponent
{
public:
	Airplane(std::string name): CompositeComponent(name) {}

	virtual void accept(AbstractVisitor& visitor) override;
};

namespace Composite
{
	extern void test();
	extern Airplane * createAirplane();
};

#endif /* Composite_h */
