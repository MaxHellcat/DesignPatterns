//
//  Maze.hpp
//  Exam
//
//  Created by Max Reshetey on 03/11/2016.
//  Copyright © 2016 Max Reshetey. All rights reserved.
//

#ifndef Maze_hpp
#define Maze_hpp

#include "list"
#include "iostream"

enum WallDirection
{
	North = 0, East, South, West, kNumOfDirections
};

class MazeItem
{
public:
	virtual void release() { delete this; }

// MARK: - Prototype pattern related
	virtual MazeItem * clone() { return new MazeItem(*this); }

	// Items can be deleted using release() only, to properly handle removal of shared ones
protected:
	virtual ~MazeItem() {}
};

class Room: public MazeItem
{
public:
	Room(int tag) : _tag(tag) {}

	void setSide(WallDirection direction, MazeItem * item)
	{
		if (_sides[direction]) // In case we're replacing
		{
			_sides[direction]->release();
		}

		_sides[direction] = item;
	}

	MazeItem * side(WallDirection direction) const { return _sides[direction]; }

	int tag() const { return _tag; }
	void setTag(int tag) { _tag = tag; }

// MARK: - Prototype pattern related
	virtual Room * clone() override { std::cout << "Room cloned\n"; return new Room(*this); }

	Room(const Room& room)
	{
		// No deep copying here as prototypical instance doesn't have any side items.
	}

protected:
	virtual ~Room() override
	{
		for (auto item : _sides)
		{
			item->release();
		}

		std::cout << "Room deleted\n";
	}

private:
	int _tag;

	MazeItem * _sides[kNumOfDirections] = { nullptr };
};

class RoomWithEnemy: public Room
{
public:
	RoomWithEnemy(int roomTag, int enemyTag = 0) : Room(roomTag) {}

// MARK: - Prototype pattern related
	virtual RoomWithEnemy * clone() override { std::cout << "RoomWithEnemy cloned\n"; return new RoomWithEnemy(*this); }

	RoomWithEnemy(const RoomWithEnemy& room): Room(room) {}

protected:
	virtual ~RoomWithEnemy() override { std::cout << "RoomWithEnemy deleted\n"; }
};

class Wall: public MazeItem
{
public:
// MARK: - Prototype pattern related
	virtual Wall * clone() override { return new Wall(*this); }

protected:
	virtual ~Wall() override { std::cout << "Wall deleted\n"; }
};

// TODO: For now only doors can be shared between rooms
class Door: public MazeItem
{
public:
	void retain() { refCount++; }
	virtual void release() override
	{
		refCount--;

		if (refCount == 0)
		{
			delete this;
		}
	}

// MARK: - Prototype pattern related
	virtual Door * clone() override { return new Door(*this); }


protected:
	virtual ~Door() override { std::cout << "Door deleted\n"; }

private:
	int refCount = 1;
};

class Maze
{
public:
	void addRoom(Room * room)
	{
		_rooms.push_back(room);
	}

	Room * room(int tag)
	{
		for (auto room : _rooms)
		{
			if (room->tag() == tag) {
				return room;
			}
		}

		return nullptr;
	}

	virtual ~Maze()
	{
		for (auto room : _rooms) { room->release(); }
		
		std::cout << "Maze deleted\n";
	}

	size_t numberOfRooms() { return _rooms.size(); }

// MARK: - Prototype pattern related
	virtual Maze * clone() { return new Maze(*this); }

	// TODO: Custom copy ctor as we can be cloned

private:
	std::list<Room *> _rooms;
};

#endif /* Maze_hpp */
