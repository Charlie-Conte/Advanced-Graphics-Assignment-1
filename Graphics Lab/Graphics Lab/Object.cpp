#include "Object.h"



Object::Object()
{
	_position = glm::vec3();

}
Object::Object(glm::vec3 position)
{
	_position = position;
}

void Object::PrintMatrix()
{
	std::cout << "(" << _position.x << ",\t" << _position.y << ",\t" << _position.z << ")\n";


}













