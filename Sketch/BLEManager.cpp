#include "BLEManager.h"
#include <Arduino.h>

BLEService sensorService("180C");  // Custom service UUID
BLECharacteristic sensorCharacteristic("2A56", BLERead | BLEWrite, 20);  // Custom characteristic UUID, max length 20

BLEManager::BLEManager()
{
	// Initialization code if needed
}

void BLEManager::initBLE()
{
	// Initialize BLE
	Serial.println("Initializing BLE...");
	if (!BLE.begin())
	{
		Serial.println("Starting BLE failed!");
		while (1);
	}

	BLE.setLocalName("Nano33BLE");
	BLE.setAdvertisedService(sensorService);
	sensorService.addCharacteristic(sensorCharacteristic);
	BLE.addService(sensorService);
	BLE.advertise();

	Serial.println("BLE initialized.");
}

/// <summary>
/// Sends data via BLE.
/// </summary>
/// <param name="data">Data to send via BLE.</param>
void BLEManager::sendData(const String& data)
{
	BLEDevice central = BLE.central();

	// If a central is connected
	if (central)
	{
		Serial.print("Connected to central: ");
		Serial.println(central.address());

		// If the central is still connected to the peripheral
		while (central.connected())
		{
			sensorCharacteristic.writeValue(data.c_str());

			Serial.print("Sent data: ");
			Serial.println(data);

			delay(1000);
		}

		Serial.print("Disconnected from central: ");
		Serial.println(central.address());
	}
}