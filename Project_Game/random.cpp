#include "random.h"

int chance(int denomenator)
{
	int randomNumber = rand();
	float random = (randomNumber % denomenator);
	int intRandom = random;

	return intRandom;
}

int generateIntRandom(int range, int start)
{
	int randomNumber = rand();
	float random = (randomNumber % range) + start;
	int intRandom = random;

	return intRandom;
}

bool generateRandomBoolean()
{
	int randomNumber = rand();
	float random = (randomNumber % 2) + 1;
	int intRandom = random;
	if (intRandom == 1) return true;
	else return false;
}