//
//  Singleton.h
//  Exam
//
//  Created by Max Reshetey on 08/11/2016.
//  Copyright © 2016 Max Reshetey. All rights reserved.
//

#ifndef Singleton_h
#define Singleton_h

#include <iostream>
using namespace std;

// TODO: Singleton inheritance for classic implementation (and how you handle subclasses instantiation)

// Name: Singleton (object creational)
// Intent: Ensure a class only has one instance, and provide a global point of access to it.
// Key:
// Notes:

class SingletonMazeFactory
{
public:
	// Classic implementation, heap allocation
	static SingletonMazeFactory * instance()
	{
		if (_instance == nullptr)
		{
			_instance = new SingletonMazeFactory();
		}

		return _instance;
	}

	static void dealloc() { delete _instance; }

	// Modern design, stack allocation, auto destruction
	static SingletonMazeFactory & instanceNew()
	{
		static SingletonMazeFactory instance;

		return instance;
	}

protected:
	// Ensure we don't occasionaly make copies
	SingletonMazeFactory() { std::cout << "Ctor SingletonMazeFactory\n"; }
	SingletonMazeFactory(const SingletonMazeFactory& other) { std::cout << "Copy Ctor SingletonMazeFactory\n"; }
	void operator=(const SingletonMazeFactory& other) {}

	~SingletonMazeFactory() { std::cout << "SingletonMazeFactory deleted\n"; }

private:
	static SingletonMazeFactory * _instance;
};

namespace Singleton
{
	extern void test();
}

#endif /* Singleton_h */
