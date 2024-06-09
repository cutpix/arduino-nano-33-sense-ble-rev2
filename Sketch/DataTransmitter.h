#ifndef DATATRANSMITTER_H
#define DATATRANSMITTER_H

/// <summary>
/// Abstract class for data transmission.
/// </summary>
class DataTransmitter
{
public:
	virtual ~DataTransmitter()
	{
	}

	/// <summary>
	/// Sends data.
	/// </summary>
	/// <param name="data">Data to send.</param>
	virtual void sendData(const String& data) = 0;
};

#endif // DATATRANSMITTER_H