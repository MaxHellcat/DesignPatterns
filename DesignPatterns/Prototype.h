//
//  Prototype.h
//  Exam
//
//  Created by Max Reshetey on 07/11/2016.
//  Copyright © 2016 Max Reshetey. All rights reserved.
//

#ifndef Prototype_h
#define Prototype_h

#include "AbstractFactory.h"
#include "Maze.h"
#include "iostream"

using namespace std;

// TODO: Promote to use prototype manager

// Name: Prototype (object creational)
// Intent: Specify the kinds of objects to create using a prototypical instance, and create new objects by copying this prototype.
// Key: Replaces factory inheritance with changeable prototypes
// Notes:
class PrototypeMazeFactory: public MazeFactory
{
public:
	PrototypeMazeFactory(Maze * maze, Wall * wall, Room * room, Door * door) :
	_maze(maze), _wall(wall), _room(room), _door(door)
	{}

	virtual Maze * makeMaze() { return _maze->clone(); }
	virtual Room * makeRoom(int roomTag) { return _room->clone(); _room->setTag(roomTag); }
	virtual Wall * makeWall() { return _wall->clone(); }
	virtual Door * makeDoor() { return _door->clone(); }

private:
	Maze * _maze;
	Wall * _wall;
	Room * _room;
	Door * _door;
};

namespace Prototype
{
	void test()
	{
		cout << "=== Prototype pattern ===\n\n";

		MazeGameWithAbstractFactory game;

		{
			// Classic maze game
			PrototypeMazeFactory factory(new Maze, new Wall, new Room(0), new Door);

			Maze * maze = game.createMaze(factory);
			cout << "Created classic maze with " << maze->numberOfRooms() << " rooms\n";
			delete maze;
		}

		cout << endl;

		{
			// Maze game with enemy
			// See how we don't inherit new factory, just set other prototype
			PrototypeMazeFactory factory(new Maze, new Wall, new RoomWithEnemy(0), new Door);

			Maze * maze = game.createMaze(factory);
			cout << "Created enemied maze with " << maze->numberOfRooms() << " rooms\n";
			delete maze;
		}
	}
}

#endif /* Prototype_h */
