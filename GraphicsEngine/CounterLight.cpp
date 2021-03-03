#include "CounterLight.h"



int _startValueLight = 0x4000;
int _counter = 0;
int _maxValueLight = 0x4007; //glGetIntegerv (GL_MAX_LIGHTS, maxNrOfLights );

int CounterLight::getValue()
{
	if ((_startValueLight+_counter) >= _maxValueLight) {
		// Not possible, too much light
		return 20;
	}
	
	int name = _startValueLight + _counter;
	++_counter;
	return name;

}

void CounterLight::clear()
{
	_counter = 0;
}


