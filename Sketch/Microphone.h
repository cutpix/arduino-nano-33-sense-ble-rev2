#ifndef MICROPHONE_H
#define MICROPHONE_H

#include "Sensor.h"
#include <vector>
#include <functional>
#include <PDM.h>
#include "Arduino.h"

class Microphone : public Sensor
{
public:
	using CallbackType = std::function<void(const std::vector<int16_t>&)>;

	/// <summary>
	/// Gets the singleton instance of the Microphone class.
	/// </summary>
	/// <returns>Instance of the Microphone class.</returns>
	static Microphone& getInstance()
	{
		static Microphone instance;
		return instance;
	}

	/// <summary>
	/// Initializes the microphone sensor.
	/// </summary>
	void init() override;

	/// <summary>
	/// Reads data from the microphone sensor.
	/// </summary>
	void read() override;

	/// <summary>
	/// Registers a callback to be called when new data is available.
	/// </summary>
	/// <param name="callback">Callback function.</param>
	void registerCallback(CallbackType callback);

	/// <summary>
	/// RMS (Root Mean Square) value of the audio signal.
	/// </summary>
	float rms;

private:
	/// <summary>
	/// Constructor for the Microphone class.
	/// </summary>
	Microphone() : isInitialized(false), rms(0) {}

	/// <summary>
	/// Static function for microphone data callback.
	/// </summary>
	static void handleMicrophoneData();

	/// <summary>
	/// Calculates the RMS value from the audio buffer.
	/// </summary>
	/// <param name="buffer">Vector containing audio samples.</param>
	/// <returns>RMS value of the audio samples.</returns>
	float calculateRMS(const std::vector<int16_t>& buffer);

	bool isInitialized; /// Indicates if the microphone is initialized.
	std::vector<CallbackType> callbacks; /// List of registered callbacks.
};

#endif // MICROPHONE_H