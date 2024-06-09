#ifndef SENSORDATA_H
#define SENSORDATA_H

#include <Arduino.h>
#include <vector>

/// <summary>
/// Struct for holding sensor data.
/// </summary>
struct SensorData
{
	/// <summary>
	/// Constructor for SensorData struct.
	/// </summary>
	/// <param name="name">Name of the sensor.</param>
	SensorData(String name) : sensorName(name) {}

	String sensorName;
	std::vector<String> data;

	/// <summary>
	/// Formats the sensor data into a single string.
	/// </summary>
	/// <returns>Formatted sensor data string.</returns>
	String format() const
	{
		String formattedData = sensorName + ": ";
		for (const auto& value : data)
		{
			formattedData += value + " ";
		}
		formattedData.trim();
		return formattedData;
	}
};

#endif // SENSORDATA_H