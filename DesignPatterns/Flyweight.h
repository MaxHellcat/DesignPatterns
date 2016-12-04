//
//  Flyweight.h
//  Exam
//
//  Created by Max Reshetey on 15/11/2016.
//  Copyright © 2016 Max Reshetey. All rights reserved.
//

#ifndef Flyweight_h
#define Flyweight_h

#include <iostream>
#include <map>
#include <list>

using namespace std;

// Name: Flyweight (object structural)
// Intent: Use sharing to support large numbers of fine-grained objects efficiently.
// Key: Keep intrinsic state as light as possible, taking all extrinsic outside for calculation/sharing.
// Notes: Note that space savings come mainly from two sources: A) Flyweight objects sharing and B) Taking out extrinsic state as much as possible. Not all Flyweight subclasses need to be shared, flyweight interface enables sharing; it doesn’t enforce it.
class Font
{
public:
	Font(string fontName): _name(fontName) {}

	string name() const { return _name; }

private:
	string _name;
};

struct Range
{
	Range(int ind, int len): index(ind), length(len) {}

	int index, length;
};

// Store extrinsic information about a font for specific character ranges (SPACE SAVING B)
class CharacterContext
{
public:
	// TODO: No mechanism for handling duplicated ranges.
	void setFont(Font * font, Range * range)
	{
		_fontRanges[range] = font;
	}

	Font * font(int index)
	{
		for (auto pair : _fontRanges)
		{
			if (index >= pair.first->index && index <= pair.first->length)
			{
				return pair.second;
			}
		}

		return nullptr;
	}

private:
	map<Range *, Font *> _fontRanges;
};

// Represent a character, intrinsic info the char code only, extrinsic (font) calculated by CharacterContext
class Character
{
	friend class CharacterFactory;

public:
	char charCode() const { return _code; }

	// Can only be created by character factory, which ensures proper sharing
private:
	Character(char charCode): _code(charCode) {}

private:
	char _code;
};

// Create characters ensuring they're shared properly (pool of unique characters) (SPACE SAVING A)
class CharacterFactory
{
public:
	Character * createCharacter(char charCode)
	{
		if (_characters.find(charCode) == _characters.end())
		{
			_characters[charCode] = new Character(charCode);
		}

		return _characters[charCode];
	}

	size_t size() const { return _characters.size(); }

	~CharacterFactory()
	{
		for (auto pair : _characters)
		{
			delete pair.second;
		}
	}

private:
	map<char, Character *> _characters;
};

namespace Flyweight
{
	class Document
	{
	public:
		Document(string text)
		{
			for (char charCode: text)
			{
				Character * character = _factory.createCharacter(charCode);
				_characters.push_back(character);
			}
		}
		
		size_t size() const { return _characters.size(); }
		size_t uniqueSize() const { return _factory.size(); }
		
		void setFont(Font * font, Range * range)
		{
			_context.setFont(font, range);
		}
		
		Font * font(int index)
		{
			return _context.font(index);
		}
		
		list<Character *> characters() const { return _characters; }
		
	private:
		list<Character *> _characters;
		
		CharacterFactory _factory;
		
		CharacterContext _context;
	};

	void test()
	{
		cout << "=== Flyweight pattern ===\n";

		cout << endl;

//		Document doc("Butterfly");
		Document doc("WednesdayWede");

		for (auto character : doc.characters())
		{
			cout << character->charCode() << " ";
		}

		cout << endl;

		cout << "Document size: " << doc.size() << ", unique: " << doc.uniqueSize() << "\n";

		Font * font = new Font("Times New Roman, 14");
		Range * range = new Range(0, 8);

		doc.setFont(font, range);

		int index = 1;

		cout << "Font for character at " << index << ": " << doc.font(index)->name() << "\n";

		delete font;
		delete range;

		cout << endl;
	}
}

#endif /* Flyweight_h */
