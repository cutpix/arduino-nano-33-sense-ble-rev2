#include "TemperatureSensor.h"
#include <Arduino.h>

void TemperatureSensor::init()
{
	if (!HS300x.begin())
	{
		Serial.println("Failed to initialize temperature sensor!");
		while (1);
	}
	Serial.println("Temperature sensor initialized.");
}

void TemperatureSensor::read()
{
	temperature = HS300x.readTemperature();
}