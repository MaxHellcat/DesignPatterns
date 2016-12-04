//
//  FactoryMethod.h
//  Exam
//
//  Created by Max Reshetey on 06/11/2016.
//  Copyright © 2016 Max Reshetey. All rights reserved.
//

#ifndef FactoryMethod_h
#define FactoryMethod_h

#include "MazeGame.h"
using namespace std;

// TODO: Statically set class name to instantiate w/o subclassing (via templates)

// Name: Factory Method (class creational), aka Virtual Constructor
// Intent: Define an interface for creating an object, but let subclasses decide which class to instantiate. Factory Method lets a class defer instantiation to subclasses.
// Key:
// Notes:

class MazeGameWithFactoryMethod: public MazeGame
{
public:
	virtual Maze * makeMaze() { return new Maze; }
	virtual Room * makeRoom(int roomTag) { return new Room(roomTag); }
	virtual Wall * makeWall() { return new Wall; }
	virtual Door * makeDoor() { return new Door; }

	// See how method doesn't contain any class names. The make* methods can be overriden by maze game subclasses to return specific versions of concrete objects.
	virtual Maze * createMaze() override
	{
		Maze * maze = makeMaze();

		Door * door = makeDoor();

		Room * room1 = makeRoom(1);
		room1->setSide(North, makeWall());
		room1->setSide(East, door);
		room1->setSide(South, makeWall());
		room1->setSide(West, makeWall());

		Room * room2 = makeRoom(2);
		room2->setSide(North, makeWall());
		room2->setSide(East, makeWall());
		room2->setSide(South, makeWall());
		door->retain();
		room2->setSide(West, door);

		maze->addRoom(room1);
		maze->addRoom(room2);

		return maze;
	}
};

class MazeGameWithEnemy: public MazeGameWithFactoryMethod
{
	// A game with enemy overrides makeRoom method to return specific room subclass that contains enemy.
	virtual Room * makeRoom(int roomTag) { return new RoomWithEnemy(roomTag); }
};

namespace FactoryMethod
{
	void test()
	{
		cout << "=== Factory Method pattern ===\n\n";

		{
			MazeGameWithFactoryMethod game;
			Maze * maze = game.createMaze();
			cout << "Created maze with " << maze->numberOfRooms() << " rooms\n";
			delete maze;
		}

		cout << endl;

		{
			MazeGameWithEnemy game;
			Maze * maze = game.createMaze();
			cout << "Created enemied maze with " << maze->numberOfRooms() << " rooms\n";
			delete maze;
		}

		cout << endl;
	}
}

#endif /* FactoryMethod_h */
