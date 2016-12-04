//
//  Singleton.cpp
//  Exam
//
//  Created by Max Reshetey on 08/11/2016.
//  Copyright © 2016 Max Reshetey. All rights reserved.
//

#include "Singleton.h"

SingletonMazeFactory * SingletonMazeFactory::_instance = nullptr;

namespace Singleton
{
	extern void test()
	{
		cout << "=== Singleton pattern ===\n\n";

		// Classic implementation
		{
			SingletonMazeFactory * factory = SingletonMazeFactory::instance();
			cout << "See singleton: " << factory << "\n";
			cout << "See singleton: " << SingletonMazeFactory::instance() << "\n";

			factory->dealloc();
		}

		cout << endl;

		// Modern design, stack allocation, auto destruction
		{
			SingletonMazeFactory &factory = SingletonMazeFactory::instanceNew();
			cout << "See singleton: " << &factory << "\n";
			cout << "See singleton: " << &SingletonMazeFactory::instanceNew() << "\n";
		}

		cout << endl;
	}
}
