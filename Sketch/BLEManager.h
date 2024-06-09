#ifndef BLEMANAGER_H
#define BLEMANAGER_H

#include <ArduinoBLE.h>
#include "DataTransmitter.h"

/// <summary>
/// Manages BLE initialization and data transmission.
/// </summary>
class BLEManager : public DataTransmitter {
public:
	/// <summary>
	/// Constructor for BLEManager class.
	/// </summary>
	BLEManager();

	/// <summary>
	/// Initializes the BLE module.
	/// </summary>
	void initBLE();

	/// <summary>
	/// Sends data via BLE.
	/// </summary>
	/// <param name="data">Data to send via BLE.</param>
	void sendData(const String& data) override;

	/// <summary>
	/// Sends sensor data via BLE.
	/// </summary>
	/// <param name="sensorData">Sensor data struct.</param>
	void sendData(const SensorData& sensorData) override;

private:
	BLEService sensorService;
	BLECharacteristic sensorCharacteristic;
};

#endif // BLEMANAGER_H