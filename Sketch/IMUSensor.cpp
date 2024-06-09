#include "IMUSensor.h"
#include <Arduino.h>

void IMUSensor::init()
{
	if (!IMU.begin())
	{
		Serial.println("Failed to initialize IMU!");
		while (1);
	}
	Serial.println("IMU initialized.");
}

void IMUSensor::read()
{
	if (IMU.accelerationAvailable())
	{
		IMU.readAcceleration(ax, ay, az);
	}

	if (IMU.gyroscopeAvailable())
	{
		IMU.readGyroscope(gx, gy, gz);
	}

	if (IMU.magneticFieldAvailable())
	{
		IMU.readMagneticField(mx, my, mz);
	}
}