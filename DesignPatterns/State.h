//
//  State.h
//  Exam
//
//  Created by Max Reshetey on 30/11/2016.
//  Copyright © 2016 Max Reshetey. All rights reserved.
//

#ifndef State_h
#define State_h

#include <iostream>

using namespace std;

// Name: State (object behavioral), aka Objects for States
// Intent: Allow an object to alter its behavior when its internal state changes. The object will appear to change its class.
// Key:
// Notes:

class Player;

// See how state-specific behavior is localized within one class
class Environment
{
public:
	virtual void move(Player * player) {}
};

// See how easy it is to define new kind of environment
class Ground: public Environment
{
public:
	virtual void move(Player * player) override { cout << "Player " << player << " walking on ground\n"; }
};

class Water: public Environment
{
public:
	virtual void move(Player * player) override { cout << "Player " << player << " swimming in water\n"; }
};

class Sky: public Environment
{
public:
	virtual void move(Player * player) override { cout << "Player " << player << " flying in skies\n"; }
};

class Player
{
public:
	void move() { _environment->move(this); }

	void setEnvironment(Environment * env) { delete _environment; _environment = env; }

private:
	Environment * _environment = nullptr;
};

namespace State
{
	void test()
	{
		cout << "=== State pattern ===\n\n";

		// The example here shows how player's moving ability varies depending on the kind of environment.

		Player player;

		player.setEnvironment(new Water);
		player.move();

		player.setEnvironment(new Ground);
		player.move();

		player.setEnvironment(new Sky);
		player.move();

		player.setEnvironment(nullptr);

		cout << endl;
	}
}

#endif /* State_h */
