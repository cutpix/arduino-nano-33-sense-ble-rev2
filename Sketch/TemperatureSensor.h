#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

#include "Sensor.h"
#include <Arduino_HS300x.h>

/// <summary>
/// Class for the temperature sensor.
/// </summary>
class TemperatureSensor : public Sensor
{
public:
	/// <summary>
	/// Initializes the temperature sensor.
	/// </summary>
	void init() override;

	/// <summary>
	/// Reads data from the temperature sensor.
	/// </summary>
	void read() override;

	/// <summary>
	/// Temperature data.
	/// </summary>
	float temperature;
};

#endif // TEMPERATURESENSOR_H