#include "CounterLight.h"

#include "GL/freeglut.h"
#include <map>


std::map<int, bool> valueUsed;

bool isCounterInitialize = false;

int CounterLight::getFreeLightValue()
{
	//control if the map is initialized
	if (!isCounterInitialize) {
		for (auto i = 0; i < 8; ++i) {
			valueUsed.insert(std::pair<int, bool>(GL_LIGHT0 + i, false));
		}
		isCounterInitialize = true;
	}

	//Return the first value free
	for (auto it = valueUsed.begin(); it != valueUsed.end(); ++it) {
		if (!it->second) {
			it->second = true;
			return it->first;
		}
	}


	return 0;
}

void CounterLight::freeValue(int valueToFree)
{
	try {
		valueUsed.at(valueToFree) = false;
	}
	catch (const std::out_of_range& e) {
		std::cerr << valueToFree << " is not a valide light value" << std::endl;
	}
}

void CounterLight::clear()
{
	valueUsed.clear();
	isCounterInitialize = false;
}


