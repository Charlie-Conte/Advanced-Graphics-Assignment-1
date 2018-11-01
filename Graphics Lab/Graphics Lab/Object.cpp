#include "Object.h"



Object::Object()
{
	position = glm::vec3();

}
Object::Object(glm::vec3 position)
{
	Object::position = position;
}

void Object::PrintMatrix()
{
	std::cout << "(" << position.x << ",\t" << position.y << ",\t" << position.z << ")\n";


}













