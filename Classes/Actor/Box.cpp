#include "Box.h"

Box * Box::createWithObject(ValueMap valueMap)
{
	Box* box = new(std::nothrow)Box;
	if (box && box->initWithObject(valueMap))
	{
		box->autorelease();
		return box;
	}
	CC_SAFE_DELETE(box);
	return nullptr;
}

bool Box::initWithObject(ValueMap valueMap)
{
	return false;

}

void Box::initProp(ValueMap valueMap)
{


}

