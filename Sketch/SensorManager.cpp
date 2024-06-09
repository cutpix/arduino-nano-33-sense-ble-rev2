#include "SensorManager.h"

/// <summary>
/// Adds a sensor to the manager.
/// </summary>
/// <param name="sensor">Pointer to the sensor to add.</param>
void SensorManager::addSensor(Sensor* sensor)
{
	sensors.push_back(sensor);
}

/// <summary>
/// Initializes all sensors.
/// </summary>
void SensorManager::initSensors()
{
	for (auto sensor : sensors)
	{
		sensor->init();
	}
}

/// <summary>
/// Reads data from all sensors.
/// </summary>
void SensorManager::readSensors()
{
	for (auto sensor : sensors)
	{
		sensor->read();
	}
}