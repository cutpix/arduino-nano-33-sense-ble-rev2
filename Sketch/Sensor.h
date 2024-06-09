#ifndef SENSOR_H
#define SENSOR_H

/// <summary>
/// Abstract base class for sensors.
/// </summary>
class Sensor
{
public:
	/// <summary>
	/// Initializes the sensor.
	/// </summary>
	virtual void init() = 0;

	/// <summary>
	/// Reads data from the sensor.
	/// </summary>
	virtual void read() = 0;
};

#endif // SENSOR_H