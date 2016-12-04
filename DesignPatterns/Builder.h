//
//  Builder.hpp
//  Exam
//
//  Created by Max Reshetey on 03/11/2016.
//  Copyright © 2016 Max Reshetey. All rights reserved.
//

#ifndef Builder_hpp
#define Builder_hpp

#include "iostream"
#include "Maze.h"
#include "MazeGame.h"

using namespace std;

// TODO: What is representation of a complex object?
// TODO: The Builder class depicted in Design Patterns doesn't seem to properly set
// adjacent walls/common wall when creating rooms.


// Name: Builder (object creational)
// Intent: Separate the construction of a complex object from its representation so that the same construction process can create different representations.
// Key: Builders construct their products in step-by-step fashion. Therefore the Builder class interface must be general enough to allow the construction of products for all kinds of concrete builders.
// Notes: Note that MazeBuilder does not create mazes itself; its main purpose is just to define an interface for creating mazes. It defines empty implementations primarily for convenience.
class AbstractBuilder
{
public:
	virtual void createMaze() {}
	virtual void createRoom(int roomTag) {}
	virtual void createDoor(int room1Tag, int room2Tag) {}

	virtual Maze * maze() { return nullptr; }

protected:
	AbstractBuilder() {}
};

class SimpleBuilder: public AbstractBuilder
{
public:
	virtual void createMaze() override
	{
		_maze = new Maze();
	}

	virtual void createRoom(int roomTag) override
	{
		Room * room = new Room(roomTag);

		room->setSide(North, new Wall);
		room->setSide(East, new Wall);
		room->setSide(South, new Wall);
		room->setSide(West, new Wall);

		_maze->addRoom(room);
	}

	virtual void createDoor(int room1Tag, int room2Tag) override
	{
		Room * room1 = _maze->room(room1Tag);
		Room * room2 = _maze->room(room2Tag);

		Door * door = new Door();

		room1->setSide(East, door);

		door->retain();
		room2->setSide(West, door);
	}

	virtual Maze * maze() override { return _maze; }

protected:
	Maze * _maze;
};

class MazeGameWithBuilder: public MazeGame
{
public:
	// Same maze creation as in MazeGame::createMaze(), now using pattern.
	// Notice how the builder hides the internal representation of the Maze—that is, the classes that define rooms, doors, and walls and how these parts are assembled to complete the final maze. Someone might guess that there are classes for representing rooms and doors, but there is no hint of one for walls. This makes it easier to change the way a maze is represented, since none of the clients of MazeBuilder has to be changed.
//		Excerpt From: Gamma, Erich. “Design Patterns: Elements of Reusable Object-Oriented Software.” iBooks.
	Maze * createMaze(AbstractBuilder & builder)
	{
		builder.createMaze();

		builder.createRoom(1);
		builder.createRoom(2);
		builder.createDoor(1, 2);

		return builder.maze();
	}
};

namespace Builder
{
	void test()
	{
		cout << "=== Builder pattern ===\n\n";

		{
			MazeGame game;
			Maze * maze = game.createMaze();
			cout << "Created maze with " << maze->numberOfRooms() << " rooms\n";
			delete maze;
		}

		cout << endl;
		
		{
			MazeGameWithBuilder game;
			SimpleBuilder builder;
			Maze * maze = game.createMaze(builder);
			cout << "Created (using Builder) maze with " << maze->numberOfRooms() << " rooms\n";
			delete maze;
		}

		cout << endl;
	}
}

#endif /* Builder_hpp */
