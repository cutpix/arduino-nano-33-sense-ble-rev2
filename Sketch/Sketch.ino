#include <PDM.h>
#include "Arduino.h"
#include <Arduino_HS300x.h>
#include <Arduino_BMI270_BMM150.h>
#include "SensorManager.h"
#include "IMUSensor.h"
#include "TemperatureSensor.h"
#include "Microphone.h"
#include "BLEManager.h"

/// <summary>
/// Instance of SensorManager class to manage sensor operations.
/// </summary>
SensorManager sensorManager;

/// <summary>
/// Instance of IMUSensor class to handle IMU sensor.
/// </summary>
IMUSensor imuSensor;

/// <summary>
/// Instance of TemperatureSensor class to handle temperature sensor.
/// </summary>
TemperatureSensor temperatureSensor;

/// <summary>
/// Instance of Microphone class to handle microphone audio.
/// </summary>
Microphone  microphone = Microphone::getInstance();

/// <summary>
/// Instance of BLEManager class to manage BLE operations.
/// </summary>
BLEManager bleManager;

/// <summary>
/// The setup function is called once when the program starts. 
/// It is used to initialize variables, pin modes, start using libraries, etc.
/// This function is called before the loop function.
/// </summary>
void setup()
{
	Serial.begin(9600);

	// Wait for serial communication to start
	while (!Serial);

	sensorManager.addSensor(&imuSensor);
	sensorManager.addSensor(&temperatureSensor);
	sensorManager.addSensor(&microphone);

	sensorManager.initSensors();

	// Register microphone callback
	microphone.registerCallback([](const std::vector<int16_t>& data)
	{
		if (!data.empty())
		{
			String micData = "Microphone Data: ";
			for (auto sample : data)
			{
				micData += String(sample) + " ";
			}
			bleManager.sendData(micData);
		}
	});

	bleManager.initBLE();
}

/// <summary>
/// The loop function is called repeatedly in an endless cycle. 
/// It is where the main logic of the program is implemented.
/// The code inside loop function will run over and over again forever.
/// </summary>
void loop()
{
	sensorManager.readSensors();

	String rmsData = "RMS: " + String(microphone.rms);
	bleManager.sendData(rmsData);
	Serial.println(rmsData);

	String tempData = "Temp: " + String(temperatureSensor.temperature) + " °C";
	bleManager.sendData(tempData);
	Serial.println(tempData);

	String imuSensorData = "IMU: ";
	imuSensorData += "Ax: " + String(imuSensor.ax) + ", Ay: " + String(imuSensor.ay) + ", Az: " + String(imuSensor.az);
	imuSensorData += ", Gx: " + String(imuSensor.gx) + ", Gy: " + String(imuSensor.gy) + ", Gz: " + String(imuSensor.gz);
	imuSensorData += ", Mx: " + String(imuSensor.mx) + ", My: " + String(imuSensor.my) + ", Mz: " + String(imuSensor.mz);
	bleManager.sendData(imuSensorData);
	Serial.println(imuSensorData);

	delay(1000);
}