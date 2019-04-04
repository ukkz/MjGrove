#include "HalI2CImpl.h"

void HalI2C::EnableImplement(int frequency)
{
	_Wire->begin();
	_Wire->setClock(frequency);
}

void HalI2C::WriteImplement(int slaveAddress, const uint8_t* data, int dataSize)
{
	_Wire->beginTransmission(slaveAddress);
	while (dataSize--)
	{
		_Wire->write(*data++);
	}
	_Wire->endTransmission();
}

int HalI2C::ReadImplement(int slaveAddress, uint8_t* data, int dataSize)
{
	uint8_t readSize = _Wire->requestFrom(slaveAddress, dataSize);
	dataSize = readSize;
	while (dataSize--)
	{
		*data++ = _Wire->read();
	}

	return readSize;
}
