#include "CounterLight.h"

#include "GL/freeglut.h"
#include <map>

/*Static variable*/
std::map<int, bool> valueUsed;
bool isCounterInitialize = false;

/**
 * @brief Control the map valueUsed and return the first free value that is free
 * 
 * @return the position of the first free value or 0 if all position are taken
 */
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

/**
 * @brief Free a value to use in the map
 * 	This method must be called before destroing a light
 * 
 * @param valueToFree value of the light that we must free
 */
void CounterLight::freeValue(int valueToFree)
{
	try {
		valueUsed.at(valueToFree) = false;
	}
	catch (const std::out_of_range& e) {
		std::cerr << valueToFree << " is not a valide light value" << std::endl;
	}
}
/**
 * @brief Reset the map by cleaning it
 * 
 */
void CounterLight::clear()
{
	valueUsed.clear();
	isCounterInitialize = false;
}


