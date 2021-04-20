#pragma once
#include "Light.h"
#include "OmniLight.h"
#include <vector>

class CounterLight {

public:
	static void add(Light* light);
	static void render();
	static void clear();


private:
	static int getFreeLightValue();
	static void freeValue(int valueToFree);

};
