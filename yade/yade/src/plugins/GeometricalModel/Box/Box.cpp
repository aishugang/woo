#include "Box.hpp"
#include <iostream>

Box::Box (Vector3 e) : CollisionModel()
{
	extents = e;
}

Box::Box () : CollisionModel()
{	
}

Box::~Box ()
{

}

void Box::processAttributes()
{
	CollisionModel::processAttributes();
}

void Box::registerAttributes()
{
	CollisionModel::registerAttributes();
	REGISTER_ATTRIBUTE(extents);
}

bool Box::collideWith(CollisionModel* )
{
	return true;

}

bool Box::loadFromFile(char * )
{
	return false;
}

void Box::glDraw()
{
	glColor3fv(diffuseColor);
	glScalef(2*extents[0],2*extents[1],2*extents[2]);

	if (wire)
	{
		glDisable(GL_LIGHTING);
		glutWireCube(1);
	}
	else
	{
		glEnable(GL_LIGHTING);
		glutSolidCube(1);
	}
}
