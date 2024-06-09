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
Microphone microphone = Microphone::getInstance();

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
			SensorData micData("Microphone");
			for (auto sample : data)
			{
				micData.data.push_back(String(sample));
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

	SensorData rmsData("RMS");
	rmsData.data.push_back(String(microphone.rms));
	bleManager.sendData(rmsData);

	SensorData tempData("Temperature");
	tempData.data.push_back(String(temperatureSensor.temperature) + " °C");
	bleManager.sendData(tempData);

	SensorData imuData("IMU");
	imuData.data.push_back("Ax: " + String(imuSensor.ax));
	imuData.data.push_back("Ay: " + String(imuSensor.ay));
	imuData.data.push_back("Az: " + String(imuSensor.az));
	imuData.data.push_back("Gx: " + String(imuSensor.gx));
	imuData.data.push_back("Gy: " + String(imuSensor.gy));
	imuData.data.push_back("Gz: " + String(imuSensor.gz));
	imuData.data.push_back("Mx: " + String(imuSensor.mx));
	imuData.data.push_back("My: " + String(imuSensor.my));
	imuData.data.push_back("Mz: " + String(imuSensor.mz));
	bleManager.sendData(imuData);

	delay(1000);
}