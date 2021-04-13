#pragma once
#include "Light.h"
class CounterLight
{

private:
	static int getFreeLightValue();
	static void freeValue(int valueToFree);
	static void clear();
};
