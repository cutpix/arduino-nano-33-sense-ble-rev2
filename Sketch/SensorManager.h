#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include "Sensor.h"
#include <vector>

/// <summary>
/// Manages multiple sensors.
/// </summary>
class SensorManager
{
public:
	/// <summary>
	/// Adds a sensor to the manager.
	/// </summary>
	/// <param name="sensor">Pointer to the sensor to add.</param>
	void addSensor(Sensor* sensor);

	/// <summary>
	/// Initializes all sensors.
	/// </summary>
	void initSensors();

	/// <summary>
	/// Reads data from all sensors.
	/// </summary>
	void readSensors();

private:
	std::vector<Sensor*> sensors;
};

#endif // SENSORMANAGER_H