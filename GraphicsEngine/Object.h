#pragma once

// C C++
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Util.h"

enum class LIB_API ObjectType { Node, Mesh, Camera, Material,Light,List,Root, Texture,Program};
class LIB_API Object
{
private:
	int _id=0;
	ObjectType _type;
	std::string _name;
	static int _counterid;

	int idGenerator();

public:
	Object(ObjectType _type,std::string _name="");
	virtual void render();
	int getId() const;
	ObjectType getType() const;
	void setType(const ObjectType type);
	std::string getName() const;
	void setName(const std::string name);
};

