#ifndef IMUSENSOR_H
#define IMUSENSOR_H

#include "Sensor.h"
#include <Arduino_BMI270_BMM150.h>

/// <summary>
/// Class for the IMU sensor (accelerometer, gyroscope, and magnetometer).
/// </summary>
class IMUSensor : public Sensor
{
public:
	/// <summary>
	/// Initializes the IMU sensor.
	/// </summary>
	void init() override;

	/// <summary>
	/// Reads data from the IMU sensor.
	/// </summary>
	void read() override;

	/// <summary>
	/// Accelerometer data
	/// </summary>
	float ax, ay, az;

	/// <summary>
	/// Gyroscope data
	/// </summary>
	float gx, gy, gz;

	/// <summary>
	/// Magnetometer data
	/// </summary>
	float mx, my, mz;
};

#endif // IMUSENSOR_H