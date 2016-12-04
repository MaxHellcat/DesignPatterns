//
//  Proxy.h
//  Exam
//
//  Created by Max Reshetey on 16/11/2016.
//  Copyright © 2016 Max Reshetey. All rights reserved.
//

#ifndef Proxy_h
#define Proxy_h

#include <iostream>

using namespace std;

// Name: Proxy (object structural), aka Surrogate
// Intent: Provide a surrogate or placeholder for another object to control access to it.
// Key:
// Notes:
// a) Proxy can provide such optimization as copy-on-write, also can overload operators to give direct access to the proxied object functionality
// b) Smart pointer is another example of Proxy

// In this example we're working with remote image. Proxy image doesn't load the file data if we only want to know its size, but does load it when we're forced to work with real data.
class RemoteFile
{
public:
	RemoteFile(string url): _url(url) {}

	// Slow method loading remote file data
	void load()
	{
		cout << "RemoteFile: Load real data\n";

		_length = 1024;
		_data = new char[_length]; // Server api for loading remote file
	}

	virtual int generateHash()
	{
		cout << "RemoteFile: Generate hash\n";

		int hash = 0;

		for (size_t i = 0; i < _length; i++)
		{
			hash += _data[i] << 1;
		}

		return hash;
	}

	virtual size_t size() const
	{
		return _length;
	}

	// Relatively fast method to obtain rough file size
	virtual size_t tentativeSize() const
	{
		// Dedicated server api to return file size only
		return 999;
	}

protected:
	virtual ~RemoteFile()
	{
		delete _data;
	}

	string _url;
	char * _data = 0;
	size_t _length = 0;
};

class RemoteImage: public RemoteFile
{
public:
	RemoteImage(string url): RemoteFile(url)
	{
		load();
	}
};

class RemoteImageProxy: public RemoteFile
{
public:
	RemoteImageProxy(string url): RemoteFile(url) {}

	// Note how we don't load file if we only want to know its size
	virtual size_t size() const override
	{
		if (_file)
		{
			return _file->size();
		}

		return this->tentativeSize();
	}

	// When we're forced to have image data, do load it
	virtual int generateHash() override
	{
		return file()->generateHash();
	}

private:
	RemoteImage * file()
	{
		if (_file == nullptr)
		{
			_file = new RemoteImage(_url);
		}

		return _file;
	}

	RemoteImage * _file = nullptr;
};

namespace Proxy
{
	void test()
	{
		cout << "=== Proxy pattern ===\n";

		cout << endl;

		RemoteImageProxy image("/site/image/image.png");

		cout << "Remote file rough size: " << image.size() << "\n";

		image.generateHash();

		cout << "Remote file exact size: " << image.size() << "\n";

		cout << endl;
	}
}

#endif /* Proxy_h */
