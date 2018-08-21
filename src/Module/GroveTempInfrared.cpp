#include "GroveTempInfrared.h"


static long res[100] =
{
	318300,302903,288329,274533,261471,249100,237381,226276,215750,205768,
	196300,187316,178788,170691,163002,155700,148766,142183,135936,130012,
	124400,119038,113928,109059,104420,100000,95788,91775,87950,84305,
	80830,77517,74357,71342,68466,65720,63098,60595,58202,55916,
	53730,51645,49652,47746,45924,44180,42511,40912,39380,37910,
	36500,35155,33866,32631,31446,30311,29222,28177,27175,26213,
	25290,24403,23554,22738,21955,21202,20479,19783,19115,18472,
	17260,16688,16138,15608,15098,14608,14135,13680,13242,12819,
	12412,12020,11642,11278,10926,10587,10260,9945,9641,9347,
	9063,8789,8525,8270,8023,7785,7555,7333,7118,6911
};

float GroveTempInfrared::binSearch(long x)
{
	int mid;
	int low = 0;
	int high = 100;

	while (low <= high)
	{
		mid = (low + high) / 2;
		if (x < res[mid])
			low = mid + 1;
		else
			high = mid - 1;
	}

	return mid;
}

void GroveTempInfrared::Init()
{
}

void GroveTempInfrared::Read()
{
	int tempValue = _Pin1->Read();
	float thermistorVolt = tempValue * 3.3 / _Pin1->MAX_VALUE;
	float thermistorResistance = thermistorVolt * 2000000 / (2.5 - thermistorVolt);
	int thermistorTemperatureIndex = binSearch(thermistorResistance);
	ThermistorTemperature = (thermistorTemperatureIndex - 1) + (res[thermistorTemperatureIndex - 1] - thermistorResistance) / (res[thermistorTemperatureIndex - 1] - res[thermistorTemperatureIndex]);
}