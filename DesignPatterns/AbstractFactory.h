//
//  AbstractFactory.h
//  Exam
//
//  Created by Max Reshetey on 12/10/2016.
//  Copyright © 2016 Max Reshetey. All rights reserved.
//

#ifndef AbstractFactory_h
#define AbstractFactory_h

#include "Maze.h"
#include "MazeGame.h"
#include "iostream"
using namespace std;

// Name: Abstract Factory (object creational), aka Kit
// Intent: Provide an interface for creating families of related or dependent objects without specifying their concrete classes.
// Key: Consistency among products
// Notes: To avoid inheriting new factory for each product family we can use a prototype-based approach. Similarly, in dynamically typed languages like Objective-C we can store product classes instead.

// A factory base class may or may not be abstract. In the former case it just defines interface, whereas in the latter it also provides default implementation, allowing sub-factories to only override methods they need.
class MazeFactory
{
public:
	// Defining methods for creating products in one class enforces products' consistency
	virtual Maze * makeMaze() { return new Maze; }
	virtual Room * makeRoom(int roomTag) { return new Room(roomTag); }
	virtual Wall * makeWall() { return new Wall; }
	virtual Door * makeDoor() { return new Door; }
};

class EnemiedMazeFactory: public MazeFactory
{
public:
	// Notice how we only override methods we need to
	virtual Room * makeRoom(int roomTag) override { return new RoomWithEnemy(roomTag); }
};

class MazeGameWithAbstractFactory: public MazeGame
{
public:
	// Notice how factory hides concrete classes, promotes consistency among products
	Maze * createMaze(MazeFactory & factory)
	{
		Maze * maze = factory.makeMaze();

		Door * door = factory.makeDoor();

		Room * room1 = factory.makeRoom(1);
		room1->setSide(North, factory.makeWall());
		room1->setSide(East, door);
		room1->setSide(South, factory.makeWall());
		room1->setSide(West, factory.makeWall());

		Room * room2 = factory.makeRoom(2);
		room2->setSide(North, factory.makeWall());
		room2->setSide(East, factory.makeWall());
		room2->setSide(South, factory.makeWall());
		door->retain();
		room2->setSide(West, door);

		maze->addRoom(room1);
		maze->addRoom(room2);

		return maze;
	}
};

namespace AbstractFactory
{
	void test()
	{
		cout << "=== Abstract Factory pattern ===\n\n";

		MazeGameWithAbstractFactory game;

		{
			MazeFactory factory;

			Maze * maze = game.createMaze(factory);
			cout << "Created maze with " << maze->numberOfRooms() << " rooms\n";
			delete maze;
		}

		cout << endl;

		{
			// Notice how pattern makes exchanging product families easy
			EnemiedMazeFactory factory;

			Maze * maze = game.createMaze(factory);
			cout << "Created enemied maze with " << maze->numberOfRooms() << " rooms\n";
			delete maze;
		}

		cout << endl;
	}
}

#endif /* AbstractFactory_h */
