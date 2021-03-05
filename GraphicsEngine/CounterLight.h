#pragma once
#include "Light.h"
class CounterLight
{

public:
	static int getFreeLightValue();
	static void freeValue(int valueToFree);
	static void clear();
};
