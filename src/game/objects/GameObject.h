#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>

class GameObject
{
	public:
		virtual ~GameObject();
		
		virtual void update() = 0;
		
		virtual std::string getType() const = 0;
};

#endif // GAMEOBJECT_H
