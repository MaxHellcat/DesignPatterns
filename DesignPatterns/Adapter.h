//
//  Adapter.h
//  Exam
//
//  Created by Max Reshetey on 09/11/2016.
//  Copyright © 2016 Max Reshetey. All rights reserved.
//

#ifndef Adapter_h
#define Adapter_h

#include "iostream"

using namespace std;

// TODO: Example of pluggable adapter

// Name: Adapter (class/object structural), aka Wrapper
// Intent: Convert the interface of a class into another interface clients expect. Adapter lets classes work together that couldn't otherwise because of incompatible imterfaces.
// Key:
// Notes:

// Funny but demonstrative example of adapter pattern: the Belkin air conditioner is implemented in terms of soviet conditioner Pobeda

// Adaptee class
class PobedaAirConditioner
{
public:
	void pumpInFreon() { cout << "Pobeda: Pump in freon...\n"; }
	void pumpOutFreon() { cout << "Pobeda: Pump out freon...\n"; }
	void turnOnHeatingSpiral() { cout << "Pobeda: Turn on spiral...\n"; }
	void turnOffHeatingSpiral() { cout << "Pobeda: Turn off spiral...\n"; }
	void startEngine() { cout << "Pobeda: Start engine...\n"; }
	void stopEngine() { cout << "Pobeda: Stop engine...\n"; }

	void setTemperature(int celsius)
	{
		cout << "Pobeda: Set " << celsius << "C\n";
		_currentTemperature = celsius;
	}
	int temperature() const { return _currentTemperature; }

private:
	int _currentTemperature = 0;
};

// Target class
class BelkinHomeDevice
{
public:
	virtual void turnOn() { _isOn = true; }
	virtual void turnOff() { _isOn = false; }

private:
	bool _isOn = false;
};

// A) Example of CLASS scope of adapter pattern. Belkin conditioner inherits a) interface of Belkin device, b) implementation of Pobeda (via private inheritance)

// Adapter class
class BelkinAirConditioner: public BelkinHomeDevice, private PobedaAirConditioner
{
public:
	virtual void turnOn() override
	{
		cout << "Belkin: Turn on...\n";

		// Scope prefixing just to show methods owner
		PobedaAirConditioner::pumpInFreon();
		PobedaAirConditioner::startEngine();

		BelkinHomeDevice::turnOn();
	}

	// See how simple adapter's operation implemented in terms of a bunch of adaptee's ones
	virtual void turnOff() override
	{
		cout << "Belkin: Turn off...\n";

		PobedaAirConditioner::pumpOutFreon();
		PobedaAirConditioner::turnOffHeatingSpiral();
		PobedaAirConditioner::stopEngine();

		BelkinHomeDevice::turnOff();
	}

	void toggleCoolerMode()
	{
		cout << "Belkin: Toggle cooler mode...\n";

		PobedaAirConditioner::pumpInFreon();
		PobedaAirConditioner::turnOffHeatingSpiral();

		setTemperature(63);
	}

	void toggleHeaterMode()
	{
		cout << "Belkin: Toggle heater mode...\n";

		PobedaAirConditioner::pumpOutFreon();
		PobedaAirConditioner::turnOnHeatingSpiral();

		setTemperature(85);
	}

	void toggleFanMode()
	{
		cout << "Belkin: Toggle fan mode...\n";

		PobedaAirConditioner::pumpOutFreon();
		PobedaAirConditioner::turnOffHeatingSpiral();

		setTemperature(65);
	}

	// See how simple operations are proxied through to adaptee
	void setTemperature(int fahrenheit)
	{
		cout << "Belkin: Set " << fahrenheit << "F\n";

		PobedaAirConditioner::setTemperature(fahrenheitToCelsius(fahrenheit));
	}

	int temperature()
	{
		return celsiusToFahrenheit(PobedaAirConditioner::temperature());
	}

private:
	int fahrenheitToCelsius(int fahrenheit) { return (fahrenheit - 32) / 1.8; }
	int celsiusToFahrenheit(int celsius) { return 1.8*celsius + 32; }
};

// B) Example of OBJECT scope uses composition of Pobeda instance into Belkin, dropping private inheritance.
// Note that in this case we can support any subclass of adaptee/Pobeda (if any).

namespace Adapter
{
	void test()
	{
		cout << "=== Adapter pattern ===\n";

		cout << endl;

		BelkinAirConditioner conditioner;

		conditioner.turnOn();
		cout << endl;

		conditioner.toggleHeaterMode();
		cout << endl;

		conditioner.toggleFanMode();
		cout << endl;

		conditioner.toggleCoolerMode();
		cout << endl;

		conditioner.setTemperature(35); // Let's freeze everything here

		cout << "Current conditioner temperature: " << conditioner.temperature() << "F\n";
		cout << endl;

		conditioner.turnOff();

		cout << endl;
	}
}

#endif /* Adapter_h */
