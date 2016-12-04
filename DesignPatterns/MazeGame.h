//
//  MazeGame.h
//  Exam
//
//  Created by Max Reshetey on 06/11/2016.
//  Copyright © 2016 Max Reshetey. All rights reserved.
//

#ifndef MazeGame_h
#define MazeGame_h

#include "Maze.h"

class MazeGame
{
public:
	// Straight forward creation of a simplest maze, creational pattern will override it
	virtual Maze * createMaze()
	{
		Maze * maze = new Maze();

		Door * door = new Door();

		Room * room1 = new Room(1);
		room1->setSide(North, new Wall);
		room1->setSide(East, door);
		room1->setSide(South, new Wall);
		room1->setSide(West, new Wall);

		Room * room2 = new Room(2);
		room2->setSide(North, new Wall);
		room2->setSide(East, new Wall);
		room2->setSide(South, new Wall);

		door->retain();
		room2->setSide(West, door);

		maze->addRoom(room1);
		maze->addRoom(room2);

		return maze;
	}
};

#endif /* MazeGame_h */
