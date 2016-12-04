//
//  Command.h
//  Exam
//
//  Created by Max Reshetey on 26/10/2016.
//  Copyright © 2016 Max Reshetey. All rights reserved.
//

#ifndef Command_h
#define Command_h

#include <iostream>

using namespace std;

// TODO: Undo/redo functionality, composite command

// Name: Command (object behavioral), aka Action, Transaction
// Intent: Incapsulate a request as an object, thereby letting you parameterize clients with different requests, queue or log requests, and support undo/redo functionality.
// Key: Command pattern decouples the object that invokes the operation (VisualItem here) from the one having the knowledge to perform it (Document).
// Notes: Commands are an object-oriented replacement for callbacks.

// Model
class Document
{
public:
	Document(string name) : _name(name) {}

	void open() { cout << "Document: Opening...\n"; }
	void save() { cout << "Document: Saving...\n"; }
	void close() { cout << "Document: Closing...\n"; }

private:
	string _name;
};

class AbstractCommand
{
public:
	virtual void execute() = 0;

	virtual ~AbstractCommand() {};

protected:
	AbstractCommand() {};
};

//	Concrete Command subclasses specify a receiver-action pair by storing the receiver as an instance variable and by implementing Execute to invoke the request.
class OpenCommand: public AbstractCommand
{
public:
	OpenCommand(Document * document) : _document(document) {}

	virtual void execute()
	{
		_document->open();
	}

private:
	Document * _document = nullptr;
};

// Notice how easy it is to add new commands, no need to modify model/view code
class SaveCommand: public AbstractCommand
{
public:
	SaveCommand(Document * document) : _document(document) {}

	virtual void execute() override
	{
		_document->save();
	}

private:
	Document * _document = nullptr;
};

class CloseCommand: public AbstractCommand
{
public:
	CloseCommand(Document * document) : _document(document) {}

	virtual void execute() override
	{
		_document->close();
	}

private:
	Document * _document = nullptr;
};

// Example of a templated command that doesn't require subclassing.
// Supports any kind of receiver/action.
// For simple commands that aren’t undoable and don’t require arguments.
template <typename Receiver>
class TemplatedCommand: public AbstractCommand
{
public:
	typedef void (Receiver::* Action)();

	TemplatedCommand(Receiver * receiver, Action action): _receiver(receiver), _action(action) {}

	virtual void execute() override
	{
		(_receiver->*_action)();
	}

private:
	Receiver * _receiver = nullptr;
	Action _action;
};

// View
class VisualItem
{
public:
	VisualItem(string name, AbstractCommand * command) : _name(name), _command(command) {}
	virtual ~VisualItem() {}

	void setCommand(AbstractCommand * command) { _command = command; }

	void click()
	{
		_command->execute();
	}

private:
	string _name;
	AbstractCommand * _command = nullptr;
};

class MenuItem: public VisualItem
{
public:
	MenuItem(string title, AbstractCommand * command) : VisualItem(title, command) {}
};

class ToolbarButton: public VisualItem
{
public:
	ToolbarButton(string imagePath, AbstractCommand * command) : VisualItem(imagePath, command) {}
};

namespace Command
{
	void test()
	{
		cout << "=== Command pattern ===\n\n";

		Document document("My document");

		// Show decoupling the invoker (MenuItem) from the receiver (Document), binding in OpenCommand
		OpenCommand openCommand(&document);
		MenuItem openMenuItem("Open document...", &openCommand);
		openMenuItem.click();

		// Show different kinds of UI elements configured by the same command
		SaveCommand saveCommand(&document);

		VisualItem saveMenuItem("Save document...", &saveCommand);
		ToolbarButton saveToolbarButton("/var/app/image.png", &saveCommand);
		saveMenuItem.click();
		saveToolbarButton.click();

		// See how we can replace commands dynamically, which would be useful for context-sensitive menus
		CloseCommand closeCommand(&document);
		saveToolbarButton.setCommand(&closeCommand);
		saveToolbarButton.click();

		cout << endl;

		// Example of templated command
		TemplatedCommand<Document> command(&document, &Document::close);
		command.execute();

		cout << endl;
	}
}

#endif /* Command_h */
