#include "Microphone.h"

/// <summary>
///  Default number of output channels.
/// </summary>
int channels = 1;

/// <summary>
/// Default PCM output frequency.
/// </summary>
int frequency = 16000;

/// <summary>
/// Default sample buffer size.
/// </summary>
size_t bufferSize = 512;

/// <summary>
/// Buffer to read samples into, each sample is 16-bits.
/// </summary>
std::vector<int16_t> sampleBuffer;

/// <summary>
/// Number of audio samples read.
/// </summary>
volatile int samplesRead;

void Microphone::init()
{
	if (!isInitialized)
	{
		// Set up the callback function to handle PDM data.
		PDM.onReceive(handleMicrophoneData);

		if (!PDM.begin(channels, frequency))
		{
			Serial.println("Failed to start PDM!");
			return;
		}

		// Resize the buffer to hold the samples.
		sampleBuffer.resize(bufferSize);

		isInitialized = true;
		Serial.println("Microphone initialized.");
	}
}

void Microphone::read()
{
	if (isInitialized && samplesRead > 0)
	{
		rms = calculateRMS(sampleBuffer);

		// Create a vector to pass to the callbacks.
		std::vector<int16_t> data(sampleBuffer.begin(), sampleBuffer.begin() + samplesRead);

		// Call each registered callback with the new data.
		for (auto& callback : callbacks)
		{
			if (callback)
			{
				callback(data);
			}
		}

		// Clear the read count.
		samplesRead = 0;
	}
}

void Microphone::registerCallback(CallbackType callback)
{
	callbacks.push_back(callback);
}

void Microphone::handleMicrophoneData()
{
	// Query the number of available bytes.
	int bytesAvailable = PDM.available();

	// Read into the sample buffer.
	PDM.read(sampleBuffer.data(), bytesAvailable);

	// 16-bit, 2 bytes per sample.
	samplesRead = bytesAvailable / 2;;
}

float Microphone::calculateRMS(const std::vector<int16_t>& buffer)
{
	float sumOfSquares = 0;
	for (int sample : buffer)
	{
		sumOfSquares += sample * sample;
	}
	return sqrt(sumOfSquares / buffer.size());
}