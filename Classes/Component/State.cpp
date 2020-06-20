#include"State.h"
USING_NS_CC;

 ProgressTimer * State::createBar(std::string file)
{
	auto state = Sprite::create(file);
	auto bar = ProgressTimer::create(state);
	bar->setType(ProgressTimer::Type::BAR);        //类型：条状
												   //从右到左减少血量
	bar->setMidpoint(Point(0, 0.5));     //如果是从左到右的话，改成(1,0.5)即可
	bar->setBarChangeRate(Point(1, 0));
	auto label=Label::createWithTTF(std::to_string(_state)+"\\"+std::to_string(_stateMax),"fonts/arial.ttf",20);
	label->setName("label");
	label->setPosition(bar->getContentSize()/2);
	bar->addChild(label);
	return bar;
}
